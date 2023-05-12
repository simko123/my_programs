#include <SFML/Graphics.hpp>

#include "figures.h"

int main() {
    sf::RenderWindow w(sf::VideoMode(1200, 900), "SFML figures lab4");

    // Линии для построения других фигур.
    Line line4par1(0, 0, 50, 100, &w),
         line4par2(0, 0, 100, 50, &w),

         line4rect1(50, 50, 150, 50, &w),
         line4rect2(50, 50, 50, 100, &w),

         line4rhmb1(120, 60, 210, 180, &w),
         line4rhmb2(120, 60, 30, 180, &w),

         line4sqr1(0, 0, 0, 100, &w),
         line4sqr2(0, 0, 100, 0, &w);

    // Сильная и самостоятельная линия.
    Line line(200, 200, 300, 150, &w);

    // Фигуры из линий.
    Parallelogram par(line4par1, line4par2, &w);
    Rectangle rect(line4rect1, line4rect2, &w);
    Rhombus rhmb(line4rhmb1, line4rhmb2, &w);
    Square sqr(line4sqr1, line4sqr2, &w);

    Figure figure; // Коробка для фигур.

    // Точку обзора переместим на начало координат,
    // чтобы в полной мере лицезреть вращение фигур.
    sf::Vector2u size = w.getSize();
    sf::View view(sf::Vector2f(0,0), sf::Vector2f(size.x, size.y));
    w.setView(view);

    // Консты для кручения-верчения фигур.
    const char pxToMove = 20;
    const char degreesToRotate = 15;

    while (w.isOpen()) {
        sf::Event event;
        while (w.pollEvent(event)) {
            switch (event.type) {

                case sf::Event::Closed: {
                    w.close();
                    break;
                }

                case sf::Event::KeyPressed: {
                    switch (event.key.code) {

                        // Выбор фигуры в коробке.
                        case sf::Keyboard::Num1 : { figure = &line; break; }
                        case sf::Keyboard::Num2 : { figure = &par;  break; }
                        case sf::Keyboard::Num3 : { figure = &rect; break; }
                        case sf::Keyboard::Num4 : { figure = &rhmb; break; }
                        case sf::Keyboard::Num5 : { figure = &sqr;  break; }

                        // Управление фигурой.
                        case sf::Keyboard::Z : {
                            figure.rotate(-degreesToRotate);
                            break;
                        }
                        case sf::Keyboard::X : {
                            figure.rotate(degreesToRotate);
                            break;
                        }
                        case sf::Keyboard::Up : {
                            figure.move(0, -pxToMove);
                            break;
                        }
                        case sf::Keyboard::Down : {
                            figure.move(0, pxToMove);
                            break;
                        }
                        case sf::Keyboard::Left : {
                            figure.move(-pxToMove, 0);
                            break;
                        }
                        case sf::Keyboard::Right : {
                            figure.move(pxToMove, 0);
                            break;
                        }
                        default: break;
                    }
                    break;
                }
                default: break;
            }
        }
        w.clear();
        figure.draw();
        w.display();
    }

    return 0;
}