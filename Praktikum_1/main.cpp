#include <iostream>
#include <cassert>
#include <cmath>
#include "CMyVector.h"

// tolerance
constexpr double EPSILON = 0.0001;

static bool d_equals(double a, double b) {
    return fabs(a - b) < EPSILON;
}

static double f(const CMyVector& vec) {
    return sin(vec[0] * vec[1]) + sin(vec[0]) + cos(vec[1]);
}

int main() {

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
}
