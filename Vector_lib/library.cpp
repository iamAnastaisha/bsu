#include "library.h"

#include <iostream>
Vector::Vector(Number x, Number y) {
    x_value = x;
    y_value = y;
}

Number Vector::polarRad() {
    Number help = x_value * x_value + y_value * y_value;
    return help.numSqrt();
}
Number Vector::polarCor() {
    Number help = y_value/x_value;
    return help.numAtan();
}

Vector Vector::operator+(const Vector& right) const {
    return Vector(x_value + right.x_value, y_value + right.y_value);
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
    out << "(" << vector.x_value << ", " << vector.y_value << ")\n";
    return out;
}
