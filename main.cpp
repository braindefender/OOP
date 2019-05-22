#include <iostream>
#include <random>
#include <ctime>

#include "Container.h"
#include "Shapes.h"
#include "Factory.h"

int main() {

    auto * shapesFactory = new Factory();
    auto * shapesContainer = new Container<Shape>();

//    Проверить throw
    shapesContainer->getFirst();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10);

    for (int i = 0; i < 25; ++i) {
        shapesContainer->push(shapesFactory->createShape(Factory::Type(dist(mt) % 6)));
    }

    std::cout << "shapesCount: " << Shape::getCount() << std::endl;

    Container<Shape>::Iterator iterator = shapesContainer->begin();
    int t_length = shapesContainer->getLength();

    while (t_length > 0) {
        iterator.iterItem()->print();
        iterator.next();
        t_length -= 1;
    }

    shapesContainer->clear();

    std::cout << "shapesCount: " << Shape::getCount() << std::endl;

    return 0;
}