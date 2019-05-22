//
// Created by Nikita Shirokov on 2019-05-22.
//
#include <ctime>
#include <random>
#include "Factory.h"

double Factory::fRand(double fMin, double fMax)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double f = dist(mt);
    return fMin + f * (fMax - fMin);
}

Shape * Factory::createShape(Type shapeType) {
    switch (shapeType) {
        case POINT: {
            std::string name = "Point_" + std::to_string(Shape::getCount() + 1);
            return new Point(name, fRand(0.0, 1.0), fRand(0.0, 1.0));
        }
        case CIRCLE: {
            std::string name = "Circle_" + std::to_string(Shape::getCount() + 1);
            return new Circle(name, fRand(0.0, 1.0), fRand(0.0, 1.0), fRand(0.0, 1.0));
        }
        case RECT: {
            std::string name = "Rect_" + std::to_string(Shape::getCount() + 1);
            return new Rect(name, fRand(0.0, 1.0), fRand(0.0, 1.0), fRand(0.0, 1.0), fRand(0.0, 1.0));
        }
        case SQUARE: {
            std::string name = "Square_" + std::to_string(Shape::getCount() + 1);
            return new Square(name, fRand(0.0, 1.0), fRand(0.0, 1.0), fRand(0.0, 1.0));
        }
        case POLYLINE: {
            std::string name = "Polyline_" + std::to_string(Shape::getCount() + 1);
            auto * pl = new Polyline(name);
            std::string t_baseName = "pl" + std::to_string(Shape::getCount() + 1) + "_";
            for (int i = 0; i < (int) (fRand(0.0, 1.0) * 10); ++i) {
                pl->addPoint(Point(t_baseName + std::to_string(i), fRand(0.0, 1.0), fRand(0.0, 1.0)));
            }
            return pl;
        }
        case POLYGON: {
            std::string name = "Polygon_" + std::to_string(Shape::getCount() + 1);
            auto * pl = new Polygon(name);
            std::string t_baseName = "pl" + std::to_string(Shape::getCount() + 1) + "_";
            for (int i = 0; i < (int) (fRand(0.0, 1.0) * 10); ++i) {
                pl->addPoint(Point(t_baseName + std::to_string(i), fRand(0.0, 1.0), fRand(0.0, 1.0)));
            }
            return pl;
        }
    }
    return nullptr;
}
