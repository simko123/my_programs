#include <SFML/Graphics.hpp>
#include "figures.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 10; // Красоты много не бывает
    sf::RenderWindow w(sf::VideoMode(1200, 900), "LAB 4", sf::Style::Default, settings);

    // Немного декора
    sf::Font font;
    font.loadFromFile("C:\\Users\\simko\\Desktop\\my_programs\\cpp\\study labs\\lab4\\Gepestev.ttf");
    sf::Text head("LAB 4", font);
    head.setCharacterSize(70);
    head.setFillColor(sf::Color::White);
    head.setPosition(-595, -455);
    sf::Text guide("1, 2, 3, 4, 5 - select figure\n"
                   "Z - rotate the figure counterclockwise\n"
                   "X - rotate the figure clockwise\n"
                   "Arrows - move figure", font);
    guide.setCharacterSize(20);
    guide.setFillColor(sf::Color::White);
    guide.setPosition(-590, -365);

    // Линии для построения других фигур и метки центра окна.
    Line line4par1(-70, -70, 50, 100, &w),
         line4par2(-70, -70, 70, 20, &w),

         line4rect1(50, 50, 200, 50, &w),
         line4rect2(50, 50, 50, 250, &w),

         line4rhmb1(120, 60, 210, 180, &w),
         line4rhmb2(120, 60, 30, 180, &w),

         line4sqr1(0, 0, 0, 100, &w),
         line4sqr2(0, 0, 100, 0, &w),

         center1(0, -5, 0, 5, &w),
         center2(-5, 0, 5, 0, &w);

    // Сильная и самостоятельная линия.
    Line line(-200, 100, 300, -150, &w);

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
    const char pxToMove = 25;
    const char degreesToRotate = 15;

    while (w.isOpen()) {
        sf::Event event;
        while (w.pollEvent(event)) {
            switch (event.type) {

                case sf::Event::Closed : {
                    w.close();
                    break;
                }

                case sf::Event::KeyPressed : {
                    switch (event.key.code) {

                        // Выбор фигуры в коробке.
                        case sf::Keyboard::Num1 : { figure = &line; head.setString("Line"); break; }
                        case sf::Keyboard::Num2 : { figure = &par;  head.setString("Parallelogram");  break; }
                        case sf::Keyboard::Num3 : { figure = &rect; head.setString("Rectangle"); break; }
                        case sf::Keyboard::Num4 : { figure = &rhmb; head.setString("Rhombus"); break; }
                        case sf::Keyboard::Num5 : { figure = &sqr;  head.setString("Square");  break; }

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
        w.draw(head);
        w.draw(guide);
        figure.draw();
        center1.draw();
        center2.draw();
        w.display();
    }

    return 0;
}