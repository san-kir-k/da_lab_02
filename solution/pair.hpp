#pragma once

namespace NPair {
    using TUll = unsigned long long;
    const TUll MAX_LEN = 256;
    /*
        Класс TPair с полями, типа char[MAX_LEN + 1] и unsigned long long для хранения пары ключ-значение.
        Имеет перегруженный operator= копирования, а также конструктор копирования.

    */
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