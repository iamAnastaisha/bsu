#ifndef VECTOR_LIB_LIBRARY_H
#define VECTOR_LIB_LIBRARY_H

#include"../Number_lib/library.h"

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

const Vector ZERO_VECTOR = Vector(ZERO_NUM, ZERO_NUM);

const Vector ONE_VECTOR = Vector(ONE_NUM, ONE_NUM);

#endif //VECTOR_LIB_LIBRARY_H
