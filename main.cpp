#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cerrno>

#include "pair.hpp"
#include "rb_tree.hpp"

using TUll = unsigned long long;
const TUll MAX_LEN = 256;

// перевести строку в нижний регистр для общности
void StrToLower(char* str) {
    for (int i = 0; i < MAX_LEN && str[i] != '\0'; ++i) {
        str[i] = std::tolower(str[i]);
    }
}

void RequestHandler() {
    char req[MAX_LEN + 1];
    NRBTree::TRBTree* tPtr = new NRBTree::TRBTree;
    while (std::cin >> req) {
        if (strcmp(req,"+") == 0) {
            char key[MAX_LEN + 1];
            TUll val;
            std::cin >> key >> val;
            StrToLower(key);
            if (tPtr->Insert({key, val})) {
                std::cout << "OK\n";
            } else {
                std::cout << "Exist\n";
            }
        } else if (strcmp(req,"-") == 0) {
            char key[MAX_LEN + 1];
            std::cin >> key;
            StrToLower(key);
            if (tPtr->Remove(key)) {
                std::cout << "OK\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        } else if (strcmp(req,"!") == 0) {
            char path[MAX_LEN + 1];
            std::cin >> req;
            std::cin.get();
            std::cin.getline(path, MAX_LEN, '\n');
            bool isOK = true;
            if (strcmp(req,"Save") == 0) {
                NRBTree::TRBTree::Save(path, *tPtr, isOK);
                if (isOK) {
                    std::cout << "OK\n";
                }
            }  else {
                NRBTree::TRBTree* tmpTreePtr = new NRBTree::TRBTree;
                NRBTree::TRBTree::Load(path, *tmpTreePtr, isOK);
                if (isOK) {
                    std::cout << "OK\n";
                    delete tPtr;
                    tPtr = tmpTreePtr;
                } else {
                    delete tmpTreePtr;
                }
            }   
        } else {
            StrToLower(req);
            NPair::TPair ans;
            if (tPtr->Search(req, ans)) {
                std::cout << "OK: " << ans.Second << "\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        }
    }
    delete tPtr;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // обработчик запросов
    RequestHandler();
    return 0;
}
