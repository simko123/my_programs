#include <iostream>
#include <cmath>

// Задача 1.

int main() {
    setlocale(LC_ALL, "Russian");
    double x, y, z, result;
    std::cout << "Введите x: "; std::cin >> x;
    std::cout << "Введите y: "; std::cin >> y;
    std::cout << "Введите z: "; std::cin >> z;
    result = ((y - x)/(z + 3*x)) * ((0.25*x + y)/(log(x) - z));
    std::cout << "Значение выражения: " << result << std::endl;
    return 0;
}