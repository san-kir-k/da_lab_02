#pragma once

namespace NPair {
    using TUll = unsigned long long;
    const TUll MAX_LEN = 256;
    struct TPair {
        char First[MAX_LEN + 1];
        TUll Second;

        TPair() = default;
        TPair(char* first, TUll second);
        TPair(const TPair& p); 
        TPair& operator=(const TPair& p);
        ~TPair() = default;
    };
}