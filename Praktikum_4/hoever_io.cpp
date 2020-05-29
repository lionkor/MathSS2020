#include "hoever_io.h"
#include <fstream>

std::vector<CKomplex> werte_einlesen(const std::string& dateiname) {
    std::size_t           N;
    std::size_t           index;
    double                re;
    double                im;
    std::vector<CKomplex> werte;

    // File oeffnen
    std::ifstream fp;
    fp.open(dateiname);
    // Dimension einlesen
    fp >> N;
    // Werte-Vektor anlegen
    werte.resize(N, CKomplex(0, 0));
    CKomplex null(0, 0);
    for (std::size_t i = 0; i < N; ++i) {
        werte[i] = null;
    }
    // Eintraege einlesen und im Werte-Vektor ablegen
    while (!fp.eof()) {
        fp >> index >> re >> im;
        CKomplex a(re, im);
        werte[index] = a;
    }
    // File schliessen
    fp.close();

    return werte;
}

void werte_ausgeben(const std::string& dateiname, const std::vector<CKomplex>& werte, double epsilon) {
    std::size_t N = werte.size();
    // File oeffnen
    std::ofstream fp;
    fp.open(dateiname);
    // Dimension in das File schreiben
    fp << N << std::endl;
    // Eintraege in das File schreiben
    fp.precision(10);
    for (std::size_t i = 0; i < N; i++)
        if (werte[i].abs() > epsilon)
            fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << std::endl;
    // File schliessen
    fp.close();
}
