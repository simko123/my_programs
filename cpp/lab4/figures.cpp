#include <cassert>
#include <cmath>
#include "figures.h"

Line::Line(float x0, float y0,
           float x1, float y1,
           sf::RenderWindow *w)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->window = w;
    this->line[0] = sf::Vector2f(x0, y0);
    this->line[1] = sf::Vector2f(x1, y1);
}

void Line::draw() {
    window->draw(line, 2, sf::Lines);
}

void Line::rotate(long double angle) {
    angle *= PI/180;

    line[0].position.x = x0 * cos(angle) - y0 * sin(angle); //  {x'} = ({cos(a) , -sin(a)} {1, 0} {x})
    line[0].position.y = x0 * sin(angle) + y0 * cos(angle); //  {y'} = ({sin(a) ,  cos(a)} {0, 1} {y})
    line[1].position.x = x1 * cos(angle) - y1 * sin(angle); //
    line[1].position.y = x1 * sin(angle) + y1 * cos(angle); //

    y0 = line[0].position.y;
    x0 = line[0].position.x;
    x1 = line[1].position.x;
    y1 = line[1].position.y;

}

void Line::move(float x, float y) {
    line[0].position.x += x; x0 += x;
    line[0].position.y += y; y0 += y;
    line[1].position.x += x; x1 += x;
    line[1].position.y += y; y1 += y;
}

float Line::len() const {
    return sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
}

float Line::angleTo(const Line& l) const {
    float vx0 = this->x1 - this->x0,
          vx1 = l.x1 - l.x0,
          vy0 = this->y1 - this->y0,
          vy1 = l.y1 - l.y0;
    return acos(
             (vx0*vx1 + vy0*vy1) /
             (sqrt(vx0*vx0 + vy0*vy0) * sqrt(vx1*vx1 + vy1*vy1))
           ) * (180/PI);
}

/////////////////////////////////////////////////////////////

Parallelogram::Parallelogram(const Line& l1, const Line& l2,
                             sf::RenderWindow *w)
{
    assert(l1.x0 == l2.x0 && l1.y0 == l2.y0);
    this->side1 = l1;
    this->side2 = l2;
    this->side3 = Line(l2.x1, l2.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->side4 = Line(l1.x1, l1.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->window = w;
}

void Parallelogram::draw() {
    side1.draw();
    side2.draw();
    side3.draw();
    side4.draw();
}

void Parallelogram::rotate(long double angle) {
    side1.rotate(angle);
    side2.rotate(angle);
    side3.rotate(angle);
    side4.rotate(angle);
}

void Parallelogram::move(int dx, int dy) {
    side1.move(dx, dy);
    side2.move(dx, dy);
    side3.move(dx, dy);
    side4.move(dx, dy);
}

/////////////////////////////////////////////////////////////

Rhombus::Rhombus(const Line& l1, const Line& l2,
                 sf::RenderWindow *w)
{
    assert(l1.len() == l2.len() && l1.x0 == l2.x0);
    this->side1 = l1;
    this->side2 = l2;
    this->side3 = Line(l2.x1, l2.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->side4 = Line(l1.x1, l1.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->window = w;
}

/////////////////////////////////////////////////////////////

Rectangle::Rectangle(const Line& l1, const Line& l2,
                     sf::RenderWindow *w)
{
    assert(l1.x0 == l2.x0 && l1.y0 == l2.y0 &&
           l1.angleTo(l2) == 90);
    this->side1 = l1;
    this->side2 = l2;
    this->side3 = Line(l2.x1, l2.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->side4 = Line(l1.x1, l1.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->window = w;
}

/////////////////////////////////////////////////////////////

Square::Square(const Line& l1, const Line& l2,
               sf::RenderWindow *w)
{
    assert(l1.x0 == l2.x0 && l1.y0 == l2.y0 &&
           l1.angleTo(l2) == 90 &&
           l1.len() == l2.len());
    this->side1 = l1;
    this->side2 = l2;
    this->side3 = Line(l2.x1, l2.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->side4 = Line(l1.x1, l1.y1, l2.x1 + (l1.x1 - l2.x0), l2.y1 + (l1.y1 - l2.y0), w);
    this->window = w;
}

/////////////////////////////////////////////////////////////

void Figure::move(int dx, int dy) {
    switch (type) {
        case 1: {line->move(dx, dy); break;}
        case 2: {square->move(dx, dy); break;}
        case 3: {rectangle->move(dx, dy); break;}
        case 4: {parallelogram->move(dx, dy); break;}
        case 5: {rhombus->move(dx, dy); break;}
    }
}

void Figure::rotate(long double angle) {
    switch (type) {
        case 1: {line->rotate(angle); break;}
        case 2: {square->rotate(angle); break;}
        case 3: {rectangle->rotate(angle); break;}
        case 4: {parallelogram->rotate(angle); break;}
        case 5: {rhombus->rotate(angle); break;}
    }
}

void Figure::draw() {
    switch (type) {
        case 1: {line->draw(); break;}
        case 2: {square->draw(); break;}
        case 3: {rectangle->draw(); break;}
        case 4: {parallelogram->draw(); break;}
        case 5: {rhombus->draw(); break;}
    }
}

Figure Figure::operator= (Line* line) {
    this->line = line;
    this->type = 1;
    return *this;
}

Figure Figure::operator= (Square* square) {
    this->square = square;
    this->type = 2;
    return *this;
}

Figure Figure::operator= (Rectangle* rectangle) {
    this->rectangle = rectangle;
    this->type = 3;
    return *this;
}

Figure Figure::operator= (Parallelogram* parallelogram) {
    this->parallelogram = parallelogram;
    this->type = 4;
    return *this;
}

Figure Figure::operator= (Rhombus* rhombus) {
    this->rhombus = rhombus;
    this->type = 5;
    return *this;
}
