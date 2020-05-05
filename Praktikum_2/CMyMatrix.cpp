#include "CMyMatrix.h"
#include <cassert>
#include <cstdlib>
#include <iomanip>

void CMyMatrix::set_values(std::initializer_list<std::initializer_list<double>> values) {
    m_dim.rows = values.size();
    // assume all have the same dimension
    m_dim.columns = values.begin()->size();
    m_values.resize(m_dim.rows * m_dim.columns);
    // sanity check
    std::size_t y = 0;
    for (auto& row : values) {
        assert(row.size() == m_dim.columns);
        std::size_t x = 0;
        for (auto& value : row) {
            at(x, y) = value;
            ++x;
        }
        ++y;
    }
}

void CMyMatrix::set_dimensions(std::size_t r, std::size_t c) {
    m_dim = { r, c };
    m_values.resize(r * c);
}

double& CMyMatrix::at(std::size_t x, std::size_t y) {
    return m_values.at(x + m_dim.columns * y);
}

double CMyMatrix::at(std::size_t x, std::size_t y) const {
    return m_values.at(x + m_dim.columns * y);
}

CMyMatrix CMyMatrix::inverted() const {
    if (m_dim.rows == 2 && m_dim.columns == 2 && det() != 0.0) {
        CMyMatrix res;
        res.set_dimensions(2, 2);
        res.set(0, 0, at(1, 1));
        res.set(0, 1, -at(0, 1));
        res.set(1, 0, -at(1, 0));
        res.set(1, 1, at(0, 0));
        return (1.0 / det()) * res;
    } else {
        std::cout << "Fatal error: " << __FUNCTION__ << " only supports 2x2 matrices with det != 0!" << std::endl;
        throw std::runtime_error("dimension error");
    }
}

double CMyMatrix::det() const {
    return at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
}

CMyVector CMyMatrix::column_as_vector(std::size_t col_i) const {
    CMyVector vec(m_dim.rows);
    for (std::size_t row_i = 0; row_i < m_dim.rows; ++row_i) {
        vec.set(row_i, at(col_i, row_i));
    }
    return vec;
}

CMyVector CMyMatrix::row_as_vector(std::size_t row_i) const {
    CMyVector vec(m_dim.columns);
    for (std::size_t col_i = 0; col_i < m_dim.columns; ++col_i) {
        vec.set(col_i, at(col_i, row_i));
    }
    return vec;
}

std::vector<double*> CMyMatrix::get_column_ref(std::size_t col_i) {
    std::vector<double*> vec;
    for (std::size_t row_i = 0; row_i < m_dim.rows; ++row_i) {
        vec.push_back(&at(col_i, row_i));
    }
    return vec;
}

std::vector<double*> CMyMatrix::get_row_ref(std::size_t row_i) {
    std::vector<double*> vec;
    for (std::size_t col_i = 0; col_i < m_dim.columns; ++col_i) {
        vec.push_back(&at(col_i, row_i));
    }
    return vec;
}

CMyMatrix operator*(double d, const CMyMatrix& old_mat) {
    CMyMatrix mat = old_mat;
    std::for_each(mat.m_values.begin(), mat.m_values.end(), [&](double& n) {
        n *= d;
    });
    return mat;
}

CMyVector operator*(const CMyMatrix& mat, const CMyVector& vec) {
    CMyVector res(mat.m_dim.rows);
    for (std::size_t i = 0; i < mat.m_dim.rows; ++i) {
        res.set(i, vec.dot(mat.row_as_vector(i)));
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const CMyMatrix& mat) {
    std::cout << "( ";
    for (std::size_t y = 0; y < mat.m_dim.rows; ++y) {
        for (std::size_t x = 0; x < mat.m_dim.columns; ++x) {
            std::cout << std::setprecision(5) << mat.at(x, y) << "; ";
        }
        if (y + 1 >= mat.m_dim.rows) {
            std::cout << " )";
        } else {
            std::cout << std::endl
                      << "  ";
        }
    }
    return os;
}

CMyMatrix jacobi(const CMyVector& x, FnPtr fn) {
    static constexpr double h = 1e-4;

    CMyMatrix res;
    res.set_dimensions(fn(x).dimension(), x.dimension());

    for (std::size_t n = 0; n < fn(x).dimension(); ++n) {
        auto vec = res.get_row_ref(n);
        for (std::size_t i = 0; i < x.dimension(); ++i) {
            auto x_mod = x;
            x_mod[i] += h;
            *vec.at(i) = (fn(x_mod)[n] - fn(x)[n]) / h;
        }
    }

    return res;
}

#define report(x) std::cout << x << std::endl
#define ind "\t"

void newton(const CMyVector& x, FnPtr f) {
    if (x.dimension() != 2 || f(x).dimension() != 2)
        throw std::runtime_error("dimension error");
    std::size_t i;
    CMyVector   dx(2);
    CMyVector   res(2);
    res = x;
    CMyMatrix jac;
    CMyMatrix jac_inv;

    auto f_x = f(x);

    for (i = 0; i < 50; ++i) {
        if (f_x.length() < 1e-5) {
            report("Ende wegen ||f(x)||<1e-5 bei");
            break;
        }
        jac     = jacobi(res, f);
        jac_inv = jac.inverted();
        report("Schritt " << i);
        report(ind "x = " << res);
        report(ind "f(x) = " << f_x);
        report(ind "f'(x) = " << std::endl
                              << jac);
        report(ind "(f'(x))^(-1) = " << std::endl
                                     << jac_inv);
        dx = jac_inv * (-1.0 * f_x);
        report(ind "dx = " << dx);
        report(ind "||f(x)|| = " << f_x.length());
        res = res + dx;

        report("\n\n");

        f_x = f(res);
    }
    if (i >= 49) {
        report("Ende wegen 50 Schritte bei");
    }
    report(ind "x = " << res);
    report(ind "f(x) = " << f_x);
    report(ind "||f(x)|| = " << f_x.length());
}
