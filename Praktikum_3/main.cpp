#include <iostream>
#include <fstream>
#include <cassert>
#include "C_DGLSolver.h"

static CMyVector dgl_fn(const CMyVector& y, double x) {
    return CMyVector {
        2 * y[1] - x * y[0],
        y[0] * y[1] - 2 * x * x * x
    };
}

static double dgl_sys_fn(const CMyVector& y, double x) {
    assert(y.dimension() == 3);
    return 2 * x * y[1] * y[2] + 2 * y[0] * y[0] * y[1];
}

int main() {
    int  selection;
    auto null = std::ofstream("/dev/null");

    for (;;) {
        std::cout << "\n1: DGL-System mit Euler\n"
                  << "2: DGL-System mit Heun\n"
                  << "3: Abweichungen bei DGL\n?> ";
        std::cin >> selection;
        std::cin.ignore();
        switch (selection) {
        case 1: {
            const C_DGLSolver solver(dgl_fn);
            auto              res = solver.euler({ 0, 1 }, 0, 2, 100, std::cout);
            static_cast<void>(res);
            break;
        }
        case 2: {
            const C_DGLSolver solver(dgl_fn);
            auto              res = solver.heun({ 0, 1 }, 0, 2, 100, std::cout);
            static_cast<void>(res);
            break;
        }
        case 3: {
            const C_DGLSolver solver(dgl_sys_fn);
            const CMyVector   y_start { 1, -1, 2 };
            for (int i = 10; i <= 10000; i *= 10) {
                std::cout << "Abweichung bei Euler mit " << i << " Schritten: " << solver.euler(y_start,1, 2, i, null)[0] - 0.5 << "\n"
                          << "Abweichung bei Heun  mit " << i << " Schritten: " << solver.heun(y_start, 1, 2, i, null)[0] - 0.5 << std::endl;
            }
            break;
        }
        default: {
            std::cout << "\ninvalid selection\n";
        }
        }
    }

    return 0;
}
