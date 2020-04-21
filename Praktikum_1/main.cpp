#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include "CMyVector.h"

// tolerance
constexpr double EPSILON = 0.0001;

static bool d_equals(double a, double b) {
    return fabs(a - b) < EPSILON;
}

static double f(const CMyVector& vec) {
    return sin(vec[0] * vec[1]) + sin(vec[0]) + cos(vec[1]);
}

static double g(const CMyVector& vec) {
    assert(vec.dimension() == 3);
    const double& x1 = vec[0];
    const double& x2 = vec[1];
    const double& x3 = vec[2];
    return -(2 * x1 * x1 - 2 * x1 * x2 + x2 * x2 + x3 * x3 - 2 * x1 - 4 * x3);
}

static double _f(const CMyVector& vec) {
    return 4.0 * vec[0] * vec[0] + 5.0 * vec[1] * vec[2] * vec[2];
}

typedef double (*fx)(const CMyVector& x);

static void gradientenverfahren(CMyVector x, fx f, double lambda = 1.0) {
    CMyVector grad_f_x = gradient(x, f);
    for (size_t i = 0; i < 25 && grad_f_x.length() >= 1e-5; ++i, grad_f_x = gradient(x, f)) {
        CMyVector x_neu = x + lambda * grad_f_x;
        std::cout << "Schritt " << i << ":" << std::endl
                  << "\tx = " << x << std::endl
                  << "\tlambda = " << lambda << std::endl
                  << "\tf(x) = " << f(x) << std::endl
                  << "\tgrad f(x) = " << grad_f_x << std::endl
                  << "\t||grad f(x)|| = " << grad_f_x.length() << std::endl
                  << std::endl
                  << "\tx_neu = " << x_neu << std::endl
                  << "\tf(x_neu) = " << f(x_neu) << std::endl
                  << std::endl;
        if (f(x_neu) > f(x)) {
            // Teste eine doppelte Schrittweite.
            CMyVector x_test = x + 2 * lambda * grad_f_x;
            std::cout << "\tTest mit doppelter Schrittweite (lambda = " << lambda * 2 << ")" << std::endl
                      << "\tx_test = " << x_test << std::endl
                      << "\tf(x_test) = " << f(x_test) << std::endl;
            if (f(x_test) > f(x_neu)) {
                std::cout << "\tverdopple Schrittweite!" << std::endl
                          << std::endl;
                // Nimm x_test als neues x und verdopple die Schrittweite λ
                x = x_test;
                lambda *= 2;
            } else {
                std::cout << "\tbehalte alte Schrittweite!" << std::endl
                          << std::endl;
                // x_neu wird als neues x genommen und die Schrittweite beibehalten.
                x = x_neu;
            }
        } else { // f(x_neu) <= f(x)
            // Halbiere die Schrittweite solange bis f(x_neu) > f(x)
            while (f(x_neu) <= f(x)) {
                lambda /= 2.0;
                x_neu = x + lambda * grad_f_x;
                std::cout << "\tHalbiere Schrittweite (lambda = " << lambda << std::endl
                          << "\tx_neu = " << x_neu << std::endl
                          << "\tf(x_neu) = " << f(x_neu) << std::endl
                          << std::endl;
            }
            x = x_neu;
        }
    }
    if (grad_f_x.length() < 10e-5) {
        std::cout << "Ende wegen ||grad f(x)|| < 10e-5 bei" << std::endl;
    } else {
        std::cout << "Ende wegen Schrittzahl = 25 bei" << std::endl;
    }
    std::cout << "\tx = " << x << std::endl
              << "\tlambda = " << lambda << std::endl
              << "\tf(x) = " << f(x) << std::endl
              << "\tgrad f(x) = " << grad_f_x << std::endl
              << "\t||grad f(x)|| = " << grad_f_x.length() << std::endl;
}

int main() {
    std::cout << "testing..." << std::endl;
    // inside of tolerance
    assert(d_equals(0.00002, 0.00001) == true);
    // outside of tolerance
    assert(d_equals(0.0002, 0.0001) == false);

    assert(d_equals(0, 0));
    assert(d_equals(1000.0, 1000.0));

    CMyVector a { { 1, 2, 3 } };

    assert(d_equals(a[0], 1));
    assert(d_equals(a[1], 2));
    assert(d_equals(a[2], 3));
    assert(d_equals(a.dimension(), 3));

    CMyVector b { { 3, 2, 1 } };

    CMyVector c = a + b;

    assert(c.dimension() == 3);

    assert(d_equals(c[0], 1 + 3));
    assert(d_equals(c[1], 2 + 2));
    assert(d_equals(c[2], 3 + 1));

    CMyVector d = 5.0 * a;

    assert(d_equals(d[0], 5 * a[0]));
    assert(d_equals(d[1], 5 * a[1]));
    assert(d_equals(d[2], 5 * a[2]));

    CMyVector e = 5.0 * a;

    assert(d_equals(e[0], 5 * a[0]));
    assert(d_equals(e[1], 5 * a[1]));
    assert(d_equals(e[2], 5 * a[2]));

    // these a and b are equal length
    a = { 1, 2, 3 };
    b = { 3, 2, 1 };

    assert(d_equals(a.length(), 3.7416));
    assert(d_equals(b.length(), 3.7416));

    assert(d_equals(a.length(), b.length()));

    CMyVector x { { 0.2, -2.1 } };

    auto g_x = gradient(x, f);

    assert(d_equals(g_x[0], -0.937420));
    assert(d_equals(g_x[1], 1.045827));

    std::cout << "success!" << std::endl;

    CMyVector test_vec_1 { 0.2, -2.1 };
    gradientenverfahren(test_vec_1, f);

    std::cout << std::setw(15) << std::setfill('=') << std::endl;

    CMyVector test_vec_2 { 0, 0, 0 };
    gradientenverfahren(test_vec_2, g, 0.1);
}
