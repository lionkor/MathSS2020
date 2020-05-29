#include <iostream>
#include "CKomplex.h"
#include "hoever_io.h"

#define TEST(x)                                                                \
    do {                                                                       \
        if (!(x))                                                              \
            std::cout << __LINE__ << " failed: \"" << #x << "\"" << std::endl; \
    } while (false)

static void run_tests();

int main() {
    run_tests();
}

static void run_tests() {
    CKomplex a(1, 2);
    CKomplex b(3, 4);

    TEST(a == a);
    TEST(b == b);
    TEST(a != b);
    TEST(b != a);

    TEST(a + b == CKomplex(4, 6));
    TEST(a - b == CKomplex(-2, -2));
    TEST(a * b == CKomplex(-5, 10));

    {
        CKomplex d = a;
        d += b;
        TEST(d == a + b);
    }

    {
        CKomplex d = a;
        d *= b;
        TEST(d == a * b);
    }

    {
        CKomplex d = a;
        d -= b;
        TEST(d == a - b);
    }

    TEST(a * 2.5 == CKomplex(2.5, 5));
    TEST(2.5 * a == CKomplex(2.5, 5));

    {
        // if these fail it might be due to floating point comparisons
        CKomplex x(5, 10);
        TEST(x.re() == 5);
        TEST(x.im() == 10);
        x.set_re(-3);
        TEST(x.re() == -3);
        TEST(x.im() == 10);
        x.set_im(-5);
        TEST(x.re() == -3);
        TEST(x.im() == -5);
    }

    TEST(CKomplex(4, 3).abs() == 5); // unsafe compare

    TEST(-a == CKomplex(-a.re(), -a.im()));

    {
        auto res = werte_einlesen("test_data.txt");
        werte_ausgeben("test_data_parsed.txt", res);
    }
}
