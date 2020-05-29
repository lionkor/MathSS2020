#include "CKomplex.h"
#include <cmath>

double CKomplex::abs() const {
    return std::sqrt(m_re * m_re + m_im * m_im);
}

CKomplex CKomplex::operator-() const {
    return CKomplex(-m_re, -m_im);
}

CKomplex CKomplex::operator+(const CKomplex& rhs) const {
    return CKomplex(m_re + rhs.m_re, m_im + rhs.m_im);
}

CKomplex CKomplex::operator-(const CKomplex& rhs) const {
    return *this + (-rhs); // delegate
}

CKomplex CKomplex::operator*(const CKomplex& rhs) const {
    // (a+bi)(c+di) = (ac−bd) + (ad+bc)i
    const auto& a = m_re;
    const auto& b = m_im;
    const auto& c = rhs.m_re;
    const auto& d = rhs.m_im;

    CKomplex result;
    result.m_re = a * c - b * d;
    result.m_im = a * d + b * c;
    return result;
}

CKomplex& CKomplex::operator+=(const CKomplex& rhs) {
    m_re += rhs.m_re;
    m_im += rhs.m_im;
    return *this;
}

CKomplex& CKomplex::operator-=(const CKomplex& rhs) {
    return *this += (-rhs); // delegate
}

CKomplex& CKomplex::operator*=(const CKomplex& rhs) {
    // compact version of operator*'s implementation
    auto re_copy = m_re;
    auto im_copy = m_im;
    m_re         = re_copy * rhs.m_re - im_copy * rhs.m_im;
    m_im         = re_copy * rhs.m_im + im_copy * rhs.m_re;
    return *this;
}

CKomplex operator*(double scalar, const CKomplex& comp) {
    return CKomplex(comp.m_re * scalar, comp.m_im * scalar);
}

CKomplex operator*(const CKomplex& comp, double scalar) {
    return operator*(scalar, comp); // delegate
}

bool CKomplex::operator==(const CKomplex& rhs) const {
    return std::abs(m_re - rhs.m_re) < 1e-10 && std::abs(m_im - rhs.m_im) < 1e-10;
}

bool CKomplex::operator!=(const CKomplex& rhs) const {
    return !(*this == rhs); // delegate
}
