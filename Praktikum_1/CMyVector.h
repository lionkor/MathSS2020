// Copyright (c) Lion Kortlepel 2020
// GitHub: lionkor
// No license. Don't use.
#ifndef CMYVECTOR_H
#define CMYVECTOR_H

#include <vector>
#include <algorithm>
#include <ostream>

class CMyVector
{
    friend CMyVector     operator+(const CMyVector&, const CMyVector&);
    friend CMyVector     operator*(double, const CMyVector&);
    friend std::ostream& operator<<(std::ostream&, const CMyVector&);

private:
    std::vector<double> m_comps;
    std::size_t         m_dim; // we don't need this but it was required to save it

    // private default ctor
    CMyVector() = default;

public:
    // explicit defaults
    CMyVector(const CMyVector&) = default;
    CMyVector(CMyVector&&)      = default;
    CMyVector& operator=(const CMyVector&) = default;
    CMyVector& operator=(CMyVector&&) = default;

    CMyVector(std::initializer_list<double>&&);
    explicit CMyVector(std::size_t size);

    std::size_t dimension() const; // dimension = size = length
    void        set(std::size_t index, double value);
    void        set(std::initializer_list<double>&& values);
    double&     operator[](std::size_t index);
    double      operator[](std::size_t index) const;
    double      length() const;
};

CMyVector gradient(const CMyVector&, double (*f)(const CMyVector&));

std::ostream& operator<<(std::ostream&, const CMyVector&);

#endif // CMYVECTOR_H
