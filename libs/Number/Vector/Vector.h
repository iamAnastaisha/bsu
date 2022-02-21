#pragma once
#include "Number.h"

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif


class Vector {
   Number x_value;
   Number y_value;

 public:
   VECTOR_API Vector(Number x, Number y);

  VECTOR_API Number polarRad();
  VECTOR_API Number polarCor();

  VECTOR_API Vector operator+(const Vector& right) const;

  VECTOR_API friend std::ostream& operator<<(std::ostream& out,
                                            const Vector& vector);
};

 const Vector ZERO_VECTOR = Vector(ZERO, ZERO);

 const Vector ONE_VECTOR = Vector(ONE, ONE);
