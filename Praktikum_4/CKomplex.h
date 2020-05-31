#ifndef CKOMPLEX_H
#define CKOMPLEX_H

#include <cmath>

class CKomplex
{
private:
    double m_im { 0 };
    double m_re { 0 };

    CKomplex() = default;

public:
    CKomplex(double _re, double _im)
        : m_im(_im), m_re(_re) { }
    CKomplex(double _phi)
        : m_im(std::sin(_phi))
        , m_re(std::cos(_phi)) { }

    double im() const { return m_im; }
    double re() const { return m_re; }
    void   set_im(double v) { m_im = v; }
    void   set_re(double v) { m_re = v; }

    double abs() const;

    CKomplex  operator-() const;
    CKomplex  operator+(const CKomplex& rhs) const;
    CKomplex  operator-(const CKomplex& rhs) const;
    CKomplex  operator*(const CKomplex& rhs) const;
    CKomplex& operator+=(const CKomplex& rhs);
    CKomplex& operator-=(const CKomplex& rhs);
    CKomplex& operator*=(const CKomplex& rhs);

    bool operator==(const CKomplex& rhs) const;
    bool operator!=(const CKomplex& rhs) const;

    friend CKomplex operator*(double, const CKomplex&);
    friend CKomplex operator*(const CKomplex&, double);
};

#endif // CKOMPLEX_H
