#include "FT.h"

std::vector<CKomplex> fourier(const std::vector<CKomplex>& values) {
    std::vector<CKomplex> results;
    const std::size_t     N = values.size();
    results.resize(N, CKomplex(0, 0));

    for (std::size_t n = 0; n < N; ++n) {
        CKomplex phi(0, 0);
        for (std::size_t k = 0; k < N; ++k) {
            phi += values[k] * CKomplex((-1.0 * (2.0 * pi() * double(k) * double(n))) / double(N));
        }
        phi           = (1.0 / sqrt(double(N))) * phi;
        results.at(n) = CKomplex(phi);
    }

    return results;
}

std::vector<CKomplex> inverse_fourier(const std::vector<CKomplex>& values) {
    std::vector<CKomplex> results;
    const std::size_t     N = values.size();
    results.resize(N, CKomplex(0, 0));

    for (std::size_t k = 0; k < N; ++k) {
        CKomplex phi(0, 0);
        for (std::size_t n = 0; n < N; ++n) {
            phi += values[n] * CKomplex(((2.0 * pi() * double(n) * double(k))) / double(N));
        }
        results.at(k) = phi * (1.0 / sqrt(double(N)));
    }

    return results;
}
