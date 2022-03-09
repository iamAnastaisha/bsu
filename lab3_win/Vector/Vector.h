#pragma once
#include "../Number/Number.h"



class Vector {
   Number x_value;
   Number y_value;

 public:
   Vector(Number x, Number y);

  Number polarRad();
  Number polarCor();

  Vector operator+(const Vector& right) const;

  friend std::ostream& operator<<(std::ostream& out,
                                            const Vector& vector);
};

 const Vector ZERO_VECTOR = Vector(ZERO, ZERO);

 const Vector ONE_VECTOR = Vector(ONE, ONE);
