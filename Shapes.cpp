//
// Created by Nikita Shirokov on 2019-05-21.
//
#include <exception>
#include "Shapes.h"

int Shape::shapesCount = 0;

int Shape::getCount() {
    return shapesCount;
}

Shape::Shape() {
    shapesCount += 1;
}

Shape::~Shape() {
    shapesCount -= 1;
}

Shape::Shape(Shape const & shape) {
    shapesCount += 1;
}

Point::Point(std::string const & name, double x, double y) : Named(name), m_x(x), m_y(y) {}

void Point::print() const {
    std::cout << "Point named: "
              << Named::m_name
              << " ("
              << m_x
              << ", "
              << m_y
              << ")"
              << std::endl;
}

double Point::x() const {
    return m_x;
}

double Point::y() const {
    return m_y;
}

Circle::Circle(const std::string & name, double x, double y, double radius) : Point(name, x, y), m_radius(radius) {}

double Circle::area() const {
    return M_PI * m_radius * m_radius;
}

void Circle::print() const {
    std::cout << "Circle named: "
              << Named::m_name
              << " at ("
              << Point::m_x
              << ", "
              << Point::m_y
              << "), R = "
              << m_radius
              << ", Area = "
              << area()
              << std::endl;
}

Rect::Rect(std::string const &name, double x1, double y1, double x2, double y2)
    : Named(name), m_p1("p1", x1, y1), m_p2("p2", x2, y2) {
    try {
        if (!((x1 <= x2) && (y1 <= y2))) {
            throw std::exception();
        }
    } catch (std::exception & e){
        std::cout << "Rect exception: wrong origin points" << std::endl;
    }
}

double Rect::area() const {
    return abs(m_p1.x() - m_p2.x()) * abs(m_p1.y() - m_p2.y());
}

void Rect::print() const {
    std::cout << "Rectangle named: "
              << Named::m_name
              << " from ("
              << m_p1.x()
              << ", "
              << m_p1.y()
              << "), to ("
              << m_p2.x()
              << ", "
              << m_p2.y()
              << ", Area = "
              << area()
              << ")"
              << std::endl;
}

Square::Square(std::string const & name, double x1, double y1, double length)
    : Rect(name, x1, y1, x1 + length, y1 + length), m_length(length) {
    try {
        if (length <= 0) {
            throw std::exception();
        }
    } catch (std::exception & e){
        std::cout << "Square exception: length is not positive number" << std::endl;
    }
}

double Square::area() const {
    return m_length * m_length;
}

void Square::print() const {
    std::cout << "Square named: "
              << Named::m_name
              << " from ("
              << Rect::m_p1.x()
              << ", "
              << Rect::m_p1.y()
              << "), to ("
              << Rect::m_p2.x()
              << ", "
              << Rect::m_p2.y()
              << ")"
              << std::endl;
}

Polyline::Polyline(std::string const & name) : Named(name) {
    m_points = new Container<Point>();
}

Polyline::~Polyline() {
    Container<Point>::Iterator iterator = m_points->begin();
    int length = m_points->getLength();

    while (length > 0) {
        delete(iterator.iterItem());
        iterator.next();
        length -= 1;
    }
}

void Polyline::print() const {
    std::cout << "Polyline named: "
              << Named::m_name
              << " with points [";
    Container<Point>::Iterator iterator = m_points->begin();
    int t_length = m_points->getLength();

    while (t_length > 0) {
        Point * t_p = iterator.iterItem();
        std::cout << "(" << t_p->x() << ", " << t_p->y() << ")";
        iterator.next();

        t_length -= 1;

        if (t_length > 0) {
            std::cout << ", ";
        }
    }

    std::cout << "], Length = "
              << length()
              << std::endl;
}

double Polyline::length() const {
    if (m_points->getLength() < 2) {
        return 0.0;
    }
    Container<Point>::Iterator iterator = m_points->begin();
    int length = m_points->getLength();

    Point * t_p1 = iterator.iterItem();
    iterator.next();
    Point * t_p2 = iterator.iterItem();

    length -= 1;

    double polyLength = 0.0;

    while (length > 0) {
        double d1 = abs(t_p1->x() - t_p2->x());
        double d2 = abs(t_p1->y() - t_p2->y());
        polyLength += sqrt(d1 * d1 + d2 * d2);
        iterator.next();
        t_p1 = t_p2;
        t_p2 = iterator.iterItem();
        length -= 1;
    }

    return polyLength;
}

void Polyline::addPoint(Point const & point) {
    auto * t_point = new Point(point);
    m_points->push(t_point);
}

Polygon::Polygon(std::string const & name) : Polyline(name) {}

void Polygon::print() const {
    std::cout << "Polygon named: "
              << Named::m_name
              << " with points [";
    Container<Point>::Iterator iterator = Polyline::m_points->begin();
    int t_length = m_points->getLength();

    while (t_length > 0) {
        Point * t_p = iterator.iterItem();
        std::cout << "(" << t_p->x() << ", " << t_p->y() << ")";
        iterator.next();

        t_length -= 1;

        if (t_length > 0) {
            std::cout << ", ";
        }
    }

    std::cout << "], Length = "
              << perimeter()
              << std::endl;
}

double Polygon::perimeter() const {
    if (m_points->getLength() < 2) {
        return 0.0;
    }
    Container<Point>::Iterator iterator = m_points->begin();
    int length = m_points->getLength();

    Point * t_p1 = iterator.iterItem();
    iterator.next();
    Point * t_p2 = iterator.iterItem();

    length -= 1;

    double polyLength = 0.0;

    while (length > 0) {
        double lX = abs(t_p1->x() - t_p2->x());
        double lY = abs(t_p1->y() - t_p2->y());
        polyLength += sqrt(lX * lX + lY * lY);
        iterator.next();
        t_p1 = t_p2;
        t_p2 = iterator.iterItem();
        length -= 1;
    }

    if (m_points->getLength() == 2) {
        polyLength /= 2;
    } else {
        Point t_first = * m_points->getFirst();
        Point t_last = * m_points->getLast();
        double lX = abs(t_first.x() - t_last.x());
        double lY = abs(t_first.y() - t_last.y());
        polyLength += sqrt(lX * lX + lY * lY);
    }

    return polyLength;
}

std::ostream & operator << (std::ostream & stream, Shape const & shape) {
    shape.print();
    return stream;
}
