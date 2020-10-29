#pragma once

namespace NPair {
    template <class F, class S>
    struct TPair {
        F First;
        S Second;

        TPair(): First(), Second() {};
        TPair(F first, S second): First(first), Second(second) {};
        TPair(const TPair<F, S>& p); // ???? <F, S>
        TPair& operator=(const TPair<F, S>& p);
        ~TPair() = default;
    };

    template <class F, class S>
    TPair<F, S>::TPair(const TPair<F, S>& p) {
        First = p.First;
        Second = p.Second;
    }

    template <class F, class S>
    TPair<F, S>& TPair<F, S>::operator=(const TPair<F, S>& p) {
        First = p.First;
        Second = p.Second;
        return *this;
    }
}