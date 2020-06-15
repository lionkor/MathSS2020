#include <iostream>
#include <iomanip>
#include "CZufall.h"
#include "CLotto.h"

int main(int, char**) {
    CZufall cz;
    cz.init(std::time(nullptr));
    int  a   = 3;
    int  b   = 7;
    int  N   = 10000;
    auto res = cz.test(a, b, N);
    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << i + a << ": " << res.at(i) << "\n";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < res.size(); ++i) {
        auto w = (res.at(i) / double(N)) * 300;
        std::cout << i + a << ": " << std::setw(w) << std::setfill('#') << "\n";
    }
    std::cout << std::endl;

    CLotto lotto(-1);
    lotto.set_tippzettel({ 1, 3, 5, 7, 11, 13 });
    size_t ziehungen = 1'000'000;
    size_t genau_drei { 0 };
    for (size_t i = 0; i < ziehungen; ++i) {
        auto result = lotto.ziehung_hits();
        if (result == 3) {
            ++genau_drei;
        }
    }
    
    auto ans = genau_drei / double(ziehungen);
    std::cout << "W' dass eine Ziehung genau 3 uebereinstimmende Zahlen mit einem vorher "
              << "festgelegten Tippzettel hat: " << ans << " (" << ans * 100 << "%)" << std::endl;
    
    genau_drei = 0;
    for (size_t i = 0; i < ziehungen; ++i) {
        auto result = lotto.zwei_ziehungen();
        if (result == 3) {
            ++genau_drei;
        }
    }
    ans = genau_drei / double(ziehungen);
    std::cout << "W' dass zwei Ziehungen genau 3 uebereinstimmende Zahlen haben: " << ans << " (" << ans * 100 << "%)" << std::endl;
}
