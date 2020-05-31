#ifndef FT_H
#define FT_H

#include <cmath>
#include <vector>
#include "CKomplex.h"

static constexpr double pi() {
    return std::acos(-1);
}

std::vector<CKomplex> fourier(const std::vector<CKomplex>& values);
std::vector<CKomplex> inverse_fourier(const std::vector<CKomplex>& values);

#endif // FT_H
