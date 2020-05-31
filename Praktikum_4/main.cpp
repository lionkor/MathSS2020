#include <cmath>
#include <iostream>
#include "CKomplex.h"
#include "hoever_io.h"
#include "FT.h"

#define TEST(x)                                                                \
    do {                                                                       \
        if (!(x))                                                              \
            std::cout << __LINE__ << " failed: \"" << #x << "\"" << std::endl; \
    } while (false)

static void run_tests();

static double max_diff(const std::vector<CKomplex>& a, const std::vector<CKomplex>& b) {
    double max_diff = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        auto diff = std::abs(a[i].abs() - b[i].abs());
        if (diff > max_diff)
            max_diff = diff;
    }
    return max_diff;
}

int main() {
    run_tests();

    auto values  = werte_einlesen("test_data.txt");
    auto results = fourier(values);
    werte_ausgeben("results_default.txt", results);
    werte_ausgeben("results_0.1.txt", results, 0.1);
    werte_ausgeben("results_1.0.txt", results, 1.0);

    auto back_default = inverse_fourier(werte_einlesen("results_default.txt"));
    auto back_0_1     = inverse_fourier(werte_einlesen("results_0.1.txt"));
    auto back_1_0     = inverse_fourier(werte_einlesen("results_1.0.txt"));

    printf("diff @ E=default: %.15f\n", max_diff(back_default, values));
    printf("diff @ E=0.1: %.15f\n", max_diff(back_0_1, values));
    printf("diff @ E=1.0: %.15f\n", max_diff(back_1_0, values));
}

static void run_tests() {
    TEST(true);
    TEST(false);

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
        auto res2 = werte_einlesen("test_data_parsed.txt");
        TEST(std::equal(res.begin(), res.end(), res2.begin(), res2.end()));
    }

    CKomplex from_phi(pi());
    std::printf("%.15f + %.15fi\n", from_phi.re(), from_phi.im());
}
