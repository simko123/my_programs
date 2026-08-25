#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <Eigen/Dense>

#include <chrono>
#include <cmath>

using namespace std::chrono_literals;

class LQGControllerNode : public rclcpp::Node
{
public:
    LQGControllerNode() : Node("lqg_controller_node")
    {
        // целевая точка
        target_x_ = 10.0;
        target_y_ = 10.0; 
        L_ = 0.1; // смещение
        dt_ = 0.1; // период управления
        
        // матрицы системы x_{k+1} = A*x_k + B*u_k
        A_ = Eigen::Matrix2d::Identity();
        B_ = Eigen::Matrix2d::Identity() * dt_;
        Eigen::Matrix2d Q = Eigen::Matrix2d::Identity() * 1.0;   // штраф за ошибку позиции
        Eigen::Matrix2d R = Eigen::Matrix2d::Identity() * 0.1;   // штраф за переусердствования
        calculate_LQR_gain(A_, B_, Q, R, K_);

        // фильтр калмана
        x_est_ = Eigen::Vector2d::Zero(); // нулевая оценка состояния
        P_est_ = Eigen::Matrix2d::Identity(); // ковариация ошибки оценки
        Q_kf_ = Eigen::Matrix2d::Identity() * 0.01; // шум процесса
        R_kf_ = Eigen::Matrix2d::Identity() * 0.05; // шум измерений
        H_ = Eigen::Matrix2d::Identity(); // матрица наблюдения

        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom", 10, std::bind(&LQGControllerNode::odom_callback, this, std::placeholders::_1));
        cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::TwistStamped>("/cmd_vel", 10);

        // Таймер цикла управления (10 Гц)
        timer_ = this->create_wall_timer(
            100ms, std::bind(&LQGControllerNode::control_loop, this));

        RCLCPP_INFO(this->get_logger(), "контроллер запущен. цель: x=%.2f, y=%.2f", target_x_, target_y_);
    }

private:
    // текущие реальные координаты бургера
    double robot_x_ = 0.0;
    double robot_y_ = 0.0;
    double robot_theta_ = 0.0;
    bool odom_received_ = false;

    // переменные для лкг
    Eigen::Matrix2d A_, B_, H_, K_;
    Eigen::Vector2d x_est_;
    Eigen::Matrix2d P_est_;
    Eigen::Matrix2d Q_kf_, R_kf_;
    
    double target_x_, target_y_;
    double L_;
    double dt_;

    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr cmd_vel_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    // считаем матрицу коэффициентов лкр через рикатти
    void calculate_LQR_gain(const Eigen::Matrix2d& A, const Eigen::Matrix2d& B, 
                            const Eigen::Matrix2d& Q, const Eigen::Matrix2d& R, Eigen::Matrix2d& K)
    {
        Eigen::Matrix2d P = Q;
        for (int i = 0; i < 100; ++i) {
            Eigen::Matrix2d B_T_P_B_plus_R = B.transpose() * P * B + R;
            P = A.transpose() * P * A - A.transpose() * P * B * B_T_P_B_plus_R.inverse() * B.transpose() * P * A + Q;
        }
        K = (B.transpose() * P * B + R).inverse() * (B.transpose() * P * A);
    }

    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
    {
        robot_x_ = msg->pose.pose.position.x;
        robot_y_ = msg->pose.pose.position.y;
        tf2::Quaternion q(
            msg->pose.pose.orientation.x,
            msg->pose.pose.orientation.y,
            msg->pose.pose.orientation.z,
            msg->pose.pose.orientation.w);
        tf2::Matrix3x3 m(q);
        double roll, pitch;
        m.getRPY(roll, pitch, robot_theta_);
        
        // печатаемся для ясности
        RCLCPP_INFO(this->get_logger(), "x=%.2f, y=%.2f, theta=%.2f", 
                    robot_x_, robot_y_, robot_theta_);

        if (!odom_received_) {
            x_est_(0) = robot_x_ + L_ * cos(robot_theta_);
            x_est_(1) = robot_y_ + L_ * sin(robot_theta_);
            odom_received_ = true;
        }
    }

    // собираем это все в цикл управления лкг
    void control_loop()
    {
        if (!odom_received_) return;

        // высчитываем точку на шажок вперед
        Eigen::Vector2d z;
        z(0) = robot_x_ + L_ * cos(robot_theta_);
        z(1) = robot_y_ + L_ * sin(robot_theta_);

        // подключаем фильтр калмана
        Eigen::Vector2d y = z - H_ * x_est_;
        Eigen::Matrix2d S = H_ * P_est_ * H_.transpose() + R_kf_;
        Eigen::Matrix2d K_f = P_est_ * H_.transpose() * S.inverse();
        
        // корректируем оценку состояния и матрицу ковариации
        x_est_ = x_est_ + K_f * y;
        P_est_ = (Eigen::Matrix2d::Identity() - K_f * H_) * P_est_;

        Eigen::Vector2d x_target(target_x_, target_y_);
        Eigen::Vector2d error = x_est_ - x_target;

        // когда подъезжаем достаточно близко, останавливаемся и радуемся
        if (error.norm() < 0.05) {
            publish_velocity(0.0, 0.0);
            RCLCPP_INFO(this->get_logger(), "ура!");
            return;
        }
        Eigen::Vector2d u_virt = -K_ * error;
        // снова калман
        x_est_ = A_ * x_est_ + B_ * u_virt;
        P_est_ = A_ * P_est_ * A_.transpose() + Q_kf_;

        // пересчитываем математику в читаемые бургером переменные линейной и угловой скорости
        double v = cos(robot_theta_) * u_virt(0) + sin(robot_theta_) * u_virt(1);
        double w = (-sin(robot_theta_) / L_) * u_virt(0) + (cos(robot_theta_) / L_) * u_virt(1);

        // ставим ограничители, чтобы не улететь
        v = std::clamp(v, -0.3, 0.3);
        w = std::clamp(w, -2.0, 2.0);

        // отдаем команды
        publish_velocity(v, w);
    }

    // просто публикатор
    void publish_velocity(double v, double w)
    {
        auto msg = geometry_msgs::msg::TwistStamped();
        msg.twist.linear.x = v;
        msg.twist.angular.z = w;
        cmd_vel_pub_->publish(msg);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LQGControllerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}