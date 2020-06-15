#include "CLotto.h"
#include <ctime>
#include <algorithm>

CLotto::CLotto(int init_n) {
    if (init_n < 0)
        m_rng.init(std::time(nullptr));
    else
        m_rng.init(init_n);
}

void CLotto::set_tippzettel(std::initializer_list<int> tipps) {
    m_tippzettel = tipps;
}

template<class ContainerT, class ValueT>
static inline bool contains(ContainerT container, ValueT value) {
    return std::find(container.begin(), container.end(), value) != container.end();
}

std::vector<int> CLotto::ziehen() const {
    std::vector<int> hit_values;
    hit_values.resize(6);
    for (size_t i = 0; i < 6; ++i) {
        int value { 0 };
        do {
            value = m_rng.wert(1, 49);
        } while (contains(hit_values, value));
        hit_values.at(i) = value;
    }
    return hit_values;
}

int CLotto::ziehung_hits() const {
    int  hits { 0 };
    auto ziehung = ziehen();
    for (int& zahl : ziehung) {
        if (contains(m_tippzettel, zahl))
            ++hits;
    }
    return hits;
}

int CLotto::zwei_ziehungen() const {
    auto ziehung_a = ziehen();
    auto ziehung_b = ziehen();
    int  uebereinstimmungen { 0 };
    for (int& i : ziehung_a) {
        if (contains(ziehung_b, i))
            ++uebereinstimmungen;
    }
    return uebereinstimmungen;
}
