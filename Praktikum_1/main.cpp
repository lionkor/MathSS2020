#include <iostream>
#include <cassert>
#include "CMyVector.h"

int main() {
    CMyVector a { { 1, 2, 3 } };

    assert(a[0] == 1);
    assert(a[1] == 2);
    assert(a[2] == 3);
    assert(a.dimension() == 3);

    CMyVector b { { 3, 2, 1 } };

    CMyVector c = a + b;

    assert(c.dimension() == 3);

    assert(c[0] == 1 + 3);
    assert(c[1] == 2 + 2);
    assert(c[2] == 3 + 1);

    CMyVector d = 5.0 * a;

    assert(d[0] == 5 * a[0]);
    assert(d[1] == 5 * a[1]);
    assert(d[2] == 5 * a[2]);

    CMyVector e = a * 5.0;

    assert(e[0] == 5 * a[0]);
    assert(e[1] == 5 * a[1]);
    assert(e[2] == 5 * a[2]);
}
