#include "C_DGLSolver.h"

#include <cassert>
#include <iostream>

C_DGLSolver::C_DGLSolver(DGLSystemFnPtr f_DGL_System) noexcept
    : m_is_n_dim(false)
    , m_fn({ .simple = f_DGL_System }) { }

C_DGLSolver::C_DGLSolver(DGLSystemNDimFnPtr f_DGL_System) noexcept
    : m_is_n_dim(true)
    , m_fn({ .ndim = f_DGL_System }) { }

CMyVector C_DGLSolver::ableitungen(const CMyVector& y, double x) const {
    if (!m_is_n_dim) {
        return m_fn.simple(y, x);
    } else {
        return transform_system(y, x);
    }
}

CMyVector C_DGLSolver::euler(const CMyVector& y_start, double x_start, double x_end, double step_count, std::ostream& os) const {
    const double delta = (x_end - x_start) / step_count;

    CMyVector y(y_start.dimension());
    CMyVector y_old = y_start;

    for (auto i = 0; i < step_count; ++i) {
        auto y_deriv = ableitungen(y_old, x_start);

        os << "Schritt " << i << ":" << std::endl
           << "\tx = " << x_start << std::endl
           << "\ty = " << y_old << std::endl
           << "\ty' = " << y_deriv << std::endl
           << std::endl;

        //  y     + h     * y'
        y = y_old + delta * y_deriv;

        x_start += delta;
        y_old = y;
    }

    os << "Ende bei" << std::endl
       << "\tx = " << x_start << std::endl
       << "\ty = " << y_old << std::endl;
    return y_old;
}

CMyVector C_DGLSolver::heun(const CMyVector& y_start, double x_start, double x_end, double step_count, std::ostream& os) const {
    double    delta = (x_end - x_start) / step_count;
    auto      d     = y_start.dimension();
    double    x     = x_start;
    double    old_x;
    CMyVector y_test = y_start;
    CMyVector y(d);
    CMyVector y_deriv_mittel(d);
    CMyVector y_deriv_test(d);

    for (auto i = 0; i < step_count; i++) {
        y = y_test;

        os << "Schritt " << i << ":\n"
           << "\tx = " << x << "\n"
           << "\ty = " << y << "\n"
           << "\ty'_orig = " << ableitungen(y, x) << "\n"
           << std::endl;

        y_test = y_test + delta * ableitungen(y_test, x);
        old_x  = x;
        x += delta;
        y_deriv_test   = ableitungen(y_test, x);
        y_deriv_mittel = 0.5 * (ableitungen(y, old_x) + y_deriv_test);

        os << "\ty_test = " << y_test << "\n"
           << "\ty'_test = " << y_deriv_test << "\n\n"
           << "\ty'_mittel = " << y_deriv_mittel << "\n"
           << std::endl;

        y_test = y + delta * y_deriv_mittel;
    }

    os << "Ende bei\n"
       << "\tx = " << x << "\n"
       << "\ty = " << y_test << std::endl;

    return y_test;
}

CMyVector C_DGLSolver::transform_system(const CMyVector& y, double x) const {
    assert(m_is_n_dim);
    CMyVector result(y.dimension());
    for (std::size_t i = 0; i < y.dimension() - 1; ++i)
        result[i] = y[i + 1];
    result[y.dimension() - 1] = m_fn.ndim(y, x);
    return result;
}
