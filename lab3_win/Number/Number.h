#pragma once

#include<ostream>

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

const Number ZERO = Number(0);
const Number ONE = Number(1);

Number createNumber(double num);
