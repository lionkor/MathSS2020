#include "CMyVector.h"

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

void CMyVector::set(std::size_t index, double value) {
    m_comps.at(index) = value;
}

void CMyVector::set(std::initializer_list<double>&& values) {
    if (values.size() > m_dim) {
        throw std::runtime_error("setting with set of invalid size");
    }
    m_comps = values;
}

CMyVector CMyVector::operator+(const CMyVector& rhs) {
    if (m_dim != rhs.m_dim)
        throw std::runtime_error("rhs has wrong dimension");
    CMyVector ret = CMyVector(m_dim);
    for (std::size_t i = 0; i < m_dim; ++i) {
        ret[i] = m_comps.at(i) + rhs[i];
    }
    return ret;
}

CMyVector operator*(double lambda, const CMyVector& vec) {
    CMyVector ret = vec;
    std::for_each(ret.m_comps.begin(), ret.m_comps.end(), [&](auto& comp) {
        comp *= lambda;
    });
    return ret;
}

CMyVector CMyVector::operator*(double lambda) {
    return lambda * *this;
}
