#include <iostream>
#include <cmath>
#include "CMyMatrix.h"
#include "CMyVector.h"


CMyVector f(const CMyVector& x) {
    return CMyVector {
        x[0] * x[1] * std::exp(x[2]),
        x[1] * x[2] * x[3],
        x[3]
    };
}

CMyVector g(const CMyVector& x) {
    return CMyVector {
        std::pow(x[0], 3) * std::pow(x[1], 3) - 2 * x[1],
        x[0] - 2
    };
}

int main(int, char**) {
    CMyMatrix mat;
    mat.set_values(
        { { 2, 3, -4 },
          { 11, 8, 7 },
          { 2, 5, 3  } });
    mat.debug_print();

    CMyVector vec({ 3, 7, 5 });

    std::cout << (mat * vec) << std::endl;

    std::cout << std::endl;

    jacobi(CMyVector { 1, 2, 0, 3 }, f).debug_print();
    
    std::cout << std::endl;
    
    newton(CMyVector { 1, 1 }, g);
}
