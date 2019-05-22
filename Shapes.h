
//
// Created by Nikita Shirokov on 2019-05-21.
//

#ifndef OOP_SHAPES_H
#define OOP_SHAPES_H

#include <cmath>
#include <iostream>
#include <utility>

#include "Base.h"
#include "Container.h"

class Shape : public Printable {
public:
    Shape();
    Shape(Shape const & shape);
    virtual ~Shape();
    static int getCount();

private:
    static int shapesCount;
};

std::ostream & operator << (std::ostream & stream, Shape const & shape);

class Point : public Named, public Shape {
public:
    Point(std::string const & name, double m_x, double m_y);
    void print() const override;
    double x() const;
    double y() const;

protected:
    double m_x, m_y;
};

class Circle : public Point {
public:
    Circle(std::string const & name, double x, double y, double radius);
    double area() const;
    void print() const override;

private:
    double m_radius;
};

class Rect : public Named, public Shape {
public:
    Rect(std::string const & name, double x1, double y1, double x2, double y2);
    virtual double area() const;
    void print() const override;

protected:
    Point m_p1, m_p2;
};

class Square : public Rect {
public:
    Square(std::string const & name, double x1, double y1, double length);
    double area() const override;
    void print() const override;

private:
    double m_length{};
};

class Polyline : public Named, public Shape {
public:
    explicit Polyline(std::string const & name);
    ~Polyline() override;
    double length() const;
    void addPoint(Point const & point);
    void print() const override;

protected:
    Container<Point> * m_points;
};

class Polygon : public Polyline {
public:
    explicit Polygon(std::string const & name);
    double perimeter() const;
    void print() const override;
};

#endif //OOP_SHAPES_H
