// Copyright (c) Lion Kortlepel 2020
// GitHub: lionkor
// No license. Don't use.
#include "CMyVector.h"
#include <numeric>
#include <cmath>
#include <iomanip>

CMyVector::CMyVector(std::initializer_list<double>&& elems)
    : m_comps { elems }
    , m_dim { elems.size() } {
}

CMyVector::CMyVector(std::size_t size)
    : m_comps {}
    , m_dim(size) {
    m_comps.resize(size);
}

std::size_t CMyVector::dimension() const {
    return m_dim;
}

double& CMyVector::operator[](std::size_t index) {
    return m_comps.at(index);
}

double CMyVector::operator[](std::size_t index) const {
    return m_comps.at(index);
}

double CMyVector::length() const {
    double sum_of_squares { 0.0 };
    for (auto& elem : m_comps) {
        sum_of_squares += elem * elem;
    }
    return std::sqrt(sum_of_squares);
}

double CMyVector::dot(const CMyVector& vec) const {
    if (vec.dimension() != dimension())
        throw std::runtime_error("dot product possible only between same-dimensional vectors");
    double res = 0.0;
    for (std::size_t i = 0; i < dimension(); ++i) {
        res += vec[i] * (*this)[i];
    }
    return res;
}

void CMyVector::set(std::size_t index, double value) {
    m_comps.at(index) = value;
}

void CMyVector::set(std::initializer_list<double>&& values) {
    if (values.size() > m_dim) {
        throw std::runtime_error("setting with set of invalid size");
    }
    m_comps = values;
}

CMyVector operator*(double lambda, const CMyVector& vec) {
    CMyVector ret = vec;
    std::for_each(ret.m_comps.begin(), ret.m_comps.end(), [&](auto& comp) {
        comp *= lambda;
    });
    return ret;
}

CMyVector operator+(const CMyVector& lhs, const CMyVector& rhs) {
    if (lhs.m_dim != rhs.m_dim)
        throw std::runtime_error("dimensions of rhs & lhs do not match");
    CMyVector ret = CMyVector(lhs.m_dim);
    for (std::size_t i = 0; i < lhs.m_dim; ++i) {
        ret[i] = lhs.m_comps.at(i) + rhs[i];
    }
    return ret;
}

//                                     V we should really use std::function<>
CMyVector gradient(const CMyVector& x, double (*f)(const CMyVector&)) {
    static constexpr double h = 10e-8;
    CMyVector               g(x.dimension());
    for (std::size_t i = 0; i < x.dimension(); ++i) {
        auto x_mod = x;
        x_mod[i] += h;
        g[i] = (f(x_mod) - f(x)) / h;
    }
    return g;
}

std::ostream& operator<<(std::ostream& os, const CMyVector& vec) {
    os << "( ";
    for (std::size_t i = 0; i < vec.dimension(); ++i) {
        os << std::setprecision(7) << vec[i];
        if (i + 1 < vec.dimension()) {
            os << "; ";
        }
    }
    os << " )";
    return os;
}
