#include "C_DGLSolver.h"

#include <cassert>

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

CMyVector C_DGLSolver::transform_system(const CMyVector& y, double x) const {
    assert(m_is_n_dim);
    CMyVector result(y.dimension());
    for (std::size_t i = 0; i < y.dimension(); ++i)
        result[i] = y[i + 1];
    result[y.dimension() - 1] = m_fn.ndim(y, x);
    return result;
}
