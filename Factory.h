//
// Created by Nikita Shirokov on 2019-05-22.
//

#ifndef OOP_FACTORY_H
#define OOP_FACTORY_H


#include "Shapes.h"

class Factory {
public:
    enum Type { POINT, CIRCLE, RECT, SQUARE, POLYLINE, POLYGON };
    virtual Shape * createShape(Type shapeType);
    virtual ~Factory() = default;
    double fRand(double fMin, double fMax);
};

#endif //OOP_FACTORY_H
