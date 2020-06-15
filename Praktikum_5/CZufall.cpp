#include "CZufall.h"
#include <random>
#include <chrono>

CZufall::CZufall() {
    srand(0);
}

int CZufall::wert(int a, int b) const {
    return (rand() % (b + 1 - a)) + a;
}

void CZufall::init(int n) {
    srand(n);
}

std::vector<int> CZufall::test(int a, int b, int N) {
    std::vector<int> result;
    result.resize(b - a + 1);
    for (int i = 0; i < N; ++i) {
        ++result.at(wert(a, b) - a);
    }
    return result;
}

std::vector<int> CZufall::test_falsch(int a, int b, int N) {
    std::vector<int> result;
    result.resize(b - a + 1);
    for (int i = 0; i < N; ++i) {
        init(time(nullptr));
        ++result.at(wert(a, b) - a);
    }
    return result;
}

std::vector<int> CZufall::test_falsch_chrono(int a, int b, int N) {
    std::vector<int> result;
    result.resize(b - a + 1);
    for (int i = 0; i < N; ++i) {
        auto now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
        init(now.count());
        ++result.at(wert(a, b) - a);
    }
    return result;
}
