//
// Created by Nikita Shirokov on 2019-05-21.
//

#ifndef OOP_BASE_H
#define OOP_BASE_H

#include <iostream>

class Printable {
public:
    virtual void print() const = 0;
};

class Named : public Printable {
protected:
    std::string m_name;
public:
    explicit Named(std::string givenName) : m_name (std::move(givenName)) {}
};

#endif //OOP_BASE_H
