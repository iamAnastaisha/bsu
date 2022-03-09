#include <iostream>
#include"../Number/Number.h"
#include"../Vector/Vector.h"


int main() {

  Vector v1 = Vector(3, 5);
  Number n1 = Number(-5.1);
  Number n2 = createNumber(10.3);
  Vector v2 = Vector(n1, n2);
  Vector v3 = ONE_VECTOR;

  std::cout << v1 + v2 << "\n";
  std::cout << v3 << "\n";
  std::cout << v1.polarRad() << ", " << v1.polarCor() << "\n";

}
