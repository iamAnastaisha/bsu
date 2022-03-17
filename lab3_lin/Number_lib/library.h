#ifndef NUMBER_LIB_LIBRARY_H
#define NUMBER_LIB_LIBRARY_H

#include<iostream>

class Number {
    double data;

public:
    Number(){};

    Number(double data_);

    Number operator+(const Number& right) const;
    Number operator-(const Number& right) const;
    Number operator*(const Number& right) const;
    Number operator/(const Number& right) const;

    Number numSqrt();
    Number numAtan();

    friend std::ostream& operator<<(std::ostream& out, const Number& number);
};

const Number ZERO_NUM = Number(0);
const Number ONE_NUM = Number(1);

Number createNumber(double num);

#endif //NUMBER_LIB_LIBRARY_H
