/* (c) Lion Kortlepel 2020
 * Since there was no specification on what can and cannot use, I'm
 * using a lot of features of C++17.
 * If you are confused as to what something is or does, feel free to
 * consult any book on modern C++ (covering C++17 and above) or 
 * cppreference.com.
 */
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
