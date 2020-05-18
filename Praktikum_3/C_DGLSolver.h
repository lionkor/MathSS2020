#ifndef C_DGL_SOLVER_H
#define C_DGL_SOLVER_H

#include "CMyVector.h"

class C_DGLSolver
{
public:
    typedef CMyVector (*DGLSystemFnPtr)(const CMyVector&, double);
    typedef double (*DGLSystemNDimFnPtr)(const CMyVector&, double);

private:
    bool m_is_n_dim;

    union {
        DGLSystemFnPtr     simple;
        DGLSystemNDimFnPtr ndim;
    } m_fn;

    CMyVector transform_system(const CMyVector& y, double x) const;

public:
    C_DGLSolver(DGLSystemFnPtr f_DGL_System) noexcept;
    C_DGLSolver(DGLSystemNDimFnPtr f_DGL_System) noexcept;

    CMyVector ableitungen(const CMyVector& y, double x) const;
};

#endif // C_DGL_SOLVER_H

