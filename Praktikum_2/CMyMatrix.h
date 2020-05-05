#ifndef CMYMATRIX_H
#define CMYMATRIX_H

#include "CMyVector.h"
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <tuple>
#include <iostream>

template<class T>
struct ColRowTuple {
    T rows;
    T columns;
};

class CMyMatrix
{
private:
    std::vector<double>      m_values;
    ColRowTuple<std::size_t> m_dim { 0, 0 };

public:
    CMyMatrix() = default;

    void set_values(std::initializer_list<std::initializer_list<double>> values);
    void set_dimensions(std::size_t, std::size_t);

    inline void debug_print() const {
        for (std::size_t y = 0; y < m_dim.rows; ++y) {
            for (std::size_t x = 0; x < m_dim.columns; ++x) {
                std::cout << at(x, y) << " ";
            }
            std::cout << std::endl;
        }
    }

    double& at(std::size_t x, std::size_t y);
    double  at(std::size_t x, std::size_t y) const;

    inline void set(std::size_t x, std::size_t y, double value) { at(x, y) = value; }

    CMyMatrix inverted() const;
    double    det() const;

    CMyVector column_as_vector(std::size_t col) const;
    CMyVector row_as_vector(std::size_t row) const;

    std::vector<double*> get_column_ref(std::size_t col);
    std::vector<double*> get_row_ref(std::size_t row_i);

    friend CMyMatrix operator*(double, const CMyMatrix&);
    friend CMyVector operator*(const CMyMatrix&, const CMyVector&);
    friend std::ostream& operator<<(std::ostream& os, const CMyMatrix&);
};

typedef CMyVector (*FnPtr)(const CMyVector&);
CMyMatrix jacobi(const CMyVector& x, FnPtr fn, double h = 1e-4);
void      newton(const CMyVector& x, FnPtr fn);

#endif // CMYMATRIX_H
