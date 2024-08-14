#include <cmath>
#include "util.hpp"
#include "translation.hpp"

Vector::Vector() : x(0), y(0) {}

Vector::Vector(double x, double y) : x(x), y(y) {} 

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(double scalar) const {
    return Vector(x * scalar, y * scalar);
};

Vector& Vector::operator+=(const Vector& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector& Vector::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;    
};

Vector Vector::rotate_by(double angle) {
    return Vector{
        -x * std::sin(angle) + y * std::cos(angle),
        x * std::cos(angle) + y * std::sin(angle),
    };
}