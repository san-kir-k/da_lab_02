#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cerrno>

#include "pair.hpp"
#include "rb_tree.hpp"

/*УДАЛИТЬ*/#include <vector>

using TUll = unsigned long long;
const TUll MAX_LEN = 256;

void StrToLower(char* str) {
    for (int i = 0; i < 256; ++i) {
        str[i] = std::tolower(str[i]);
    }
}

void RequestHandler() {
    char req[MAX_LEN + 1];
    /*TEST, УДАЛИТЬ*/
    NRBTree::TRBTree t;
    //--------
    while (std::cin >> req) {
        if (strcmp(req,"+") == 0) {
            char key[MAX_LEN + 1];
            TUll val;
            std::cin >> key >> val;
            StrToLower(key);
            // УДАЛИТЬ
            t.Insert({key, val});
            //--------
        } else if (strcmp(req,"-") == 0) {
            char key[MAX_LEN + 1];
            std::cin >> key;
            // remove
        } else if (strcmp(req,"!") == 0) {
            char path[MAX_LEN + 1];
            std::cin >> req;
            std::cin.getline(path, MAX_LEN, '\n');
            if (strcmp(req,"Save") == 0) {
                std::FILE* f = std::fopen(path, "w");
                if (f == NULL) {
                    std::cout << "ERROR: " << std::strerror(errno) << "\n";
                }
                // save in file
            }  else {
                std::FILE* f = std::fopen(path, "r");
                if (f == NULL) {
                    std::cout << "ERROR: " << std::strerror(errno) << "\n";
                }
                // load from file
            }   
        } else {
            StrToLower(req);
            /* УДАЛИТЬ */
            NPair::TPair<char*, TUll> ans;
            if (t.Search(req, ans)) {
                std::cout << ans.First << " - " << ans.Second << "\n";
            }
            //--------
        }
    }
}

int main() {
    RequestHandler();
    return 0;
}