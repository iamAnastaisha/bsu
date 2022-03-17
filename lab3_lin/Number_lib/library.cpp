#include "library.h"

#include<cmath>

Number::Number(double data_) { this->data = data_; }

Number Number::operator+(const Number& right) const {
    return data + right.data;
}
Number Number::operator-(const Number& right) const {
    return data - right.data;
}
Number Number::operator*(const Number& right) const {
    return data * right.data;
}
Number Number::operator/(const Number& right) const {
    return data / right.data;
}

Number Number::numSqrt() {
    return sqrt(data);
}
Number Number::numAtan() {
    return atan(data);
}

std::ostream& operator<<(std::ostream& out, const Number& number) {
    out << number.data;
    return out;
}

Number createNumber(double num) { return num; }
