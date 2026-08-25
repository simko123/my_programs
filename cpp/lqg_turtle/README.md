
## Описание

Перед вами незамысловатая программа, выполняющая всего одну задачу - переместить робота Turtlebot3 в симуляции Gazebo, используя технологию ROS2 и формулы LQG, в интересующую вас точку. Выбор точки - 19 и 20 строки .cpp файла. 

## Сборка

```bash
# Переносим файл в рабочую среду ros2, у меня это папка ros2_ws
cd ~/ros2_ws
source install/local_setup.bash
colcon build --packages-select trialpack1
# готово
```

## Запуск

```bash
# 1. запускаем симуляцию gazebo из отдельного терминала
ros2 launch turtlebot3_gazebo empty_world.launch.py
# 2. запускаем программу
ros2 run trialpack1 trialnode1
# 3. наслаждаемся зрелищем
```



