#include "pair.hpp"

namespace NPair{
    TPair::TPair(char* first, TUll second) {
        for (int i = 0; i < MAX_LEN + 1; ++i) {
            First[i] = first[i];
        }
        Second = second;
    }
    TPair::TPair(const TPair& p) {
        for (int i = 0; i < MAX_LEN + 1; ++i) {
            First[i] = p.First[i];
        }
        Second = p.Second;
    }

    TPair& TPair::operator=(const TPair& p) {
        for (int i = 0; i < MAX_LEN + 1; ++i) {
            First[i] = p.First[i];
        }
        Second = p.Second;
        return *this;
    }
}