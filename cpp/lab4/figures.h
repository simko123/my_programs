#ifndef FIGURES_H
#define FIGURES_H

#include <SFML/Graphics.hpp>

const long double PI = 3.14159265358979323846;

class Point {

public:

    Point(){ }
   ~Point(){ }

    virtual void draw()=0;
    virtual void move(float dx, float dy)=0;

protected:

    float x0, y0;
    sf::RenderWindow *window;

};

class Line : public Point {

public:

    Line(){};
    Line(float x0, float y0,
         float x1, float y1,
         sf::RenderWindow *w);
   ~Line(){ };

   virtual void rotate(long double angle);
   void move(float x, float y);
   void draw();

   float len() const;
   float angleTo(const Line& line) const;

   friend class Parallelogram;
   friend class Rectangle;
   friend class Rhombus;
   friend class Square;

protected:

    float x1, y1;

private:

    sf::Vertex line[2];
    sf::Color color;

};

class Parallelogram : public Line {

public:

    Parallelogram(const Line& l1, const Line& l2,
                  sf::RenderWindow *w);

    Parallelogram(){ }
   ~Parallelogram(){ }

    void draw();
    void rotate(long double angle);
    void move(int dx, int dy);

protected:

    Line side1, side2, side3, side4;

};

class Rectangle : public Parallelogram {

public:

    Rectangle(const Line& l1, const Line& l2,
              sf::RenderWindow *w);

    Rectangle(){ }
    ~Rectangle(){ }

};

class Rhombus : public Parallelogram {

public:

    Rhombus(const Line& l1, const Line& l2,
            sf::RenderWindow *w);

    Rhombus() {}
    ~Rhombus(){ };

};

class Square : public Rectangle {

public:

    Square(const Line& l1, const Line& l2,
           sf::RenderWindow *w);

    Square() { }
    ~Square(){ }

};

class Figure {

public:

    Figure() {}
    ~Figure(){}

    void move(int dx, int dy);
    void rotate(long double angle);
    void draw();

    Figure operator= (Line* line);
    Figure operator= (Square* square);
    Figure operator= (Rectangle* rectangle);
    Figure operator= (Parallelogram* parallelogram);
    Figure operator= (Rhombus* rhombus);

private:

    char type;
    Line* line; // 1
    Square* square; // 2
    Rectangle* rectangle; // 3
    Parallelogram* parallelogram; // 4
    Rhombus* rhombus; // 5

};

#endif //FIGURES_H