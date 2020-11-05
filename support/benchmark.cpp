#include <iostream>
#include <map>
#include <chrono>
#include <cstring>
#include <string>
#include "../solution/rb_tree.hpp"

using TUll = unsigned long long;
const TUll MAX_LEN = 256;

struct cmpStr {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs < rhs;
    }
};

void StrToLower(char* str) {
    for (int i = 0; i < MAX_LEN && str[i] != '\0'; ++i) {
        str[i] = std::tolower(str[i]);
    }
}

int main() {
    using duration_t = std::chrono::microseconds;

    std::map<std::string, TUll, cmpStr> mapTree;
    NRBTree::TRBTree RBTree;
    std::string action;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    TUll  mapTsInsert = 0, mapTsDelete = 0, mapTsSearch = 0;
    TUll  rbTsInsert = 0, rbTsDelete = 0, rbTsSearch = 0;
    while (std::cin >> action) {
        if (action == "+") {
            std::string keyStr;
            char key[MAX_LEN + 1];
            TUll val;
            std::cin >> keyStr >> val;
            for (int i = 0; i < keyStr.size(); ++i) {
                key[i] = keyStr[i];
            }
            key[keyStr.size()] = '\0';
            StrToLower(key);
            {
                start = std::chrono::system_clock::now();
                RBTree.Insert({key, val});
                end = std::chrono::system_clock::now();
                rbTsInsert += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                mapTree.insert({keyStr, val});
                end = std::chrono::system_clock::now();
                mapTsInsert += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        } else if (action == "-") {
            std::string keyStr;
            char key[MAX_LEN + 1];
            std::cin >> keyStr;
            for (int i = 0; i < keyStr.size(); ++i) {
                key[i] = keyStr[i];
            }
            key[keyStr.size()] = '\0';
            StrToLower(key);
            {
                start = std::chrono::system_clock::now();
                RBTree.Remove(key);
                end = std::chrono::system_clock::now();
                rbTsDelete += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                mapTree.erase(keyStr);
                end = std::chrono::system_clock::now();
                mapTsDelete += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        } else {
            char key[MAX_LEN + 1];
            for (int i = 0; i < action.size(); ++i) {
                key[i] = action[i];
            }
            key[action.size()] = '\0';
            StrToLower(key);
            NPair::TPair ans;
            {
                start = std::chrono::system_clock::now();
                RBTree.Search(key, ans);
                end = std::chrono::system_clock::now();
                rbTsSearch += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                mapTree.find(action);
                end = std::chrono::system_clock::now();
                mapTsSearch += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
    }
    std::cout << "==============START============\n";
    std::cout << "INSERT std::map time: " << mapTsInsert << "ms" <<
    "\nINSERT rb tree time: " << rbTsInsert << "ms\n";
    std::cout << "===============================\n";
    std::cout << "DELETE std::map time: " << mapTsDelete << "ms" <<
    "\nDELETE rb tree time: " << rbTsDelete << "ms\n";
    std::cout << "===============================\n";
    std::cout << "SEARCH std::map time: " << mapTsSearch << "ms" <<
    "\nSEARCH rb tree time: " << rbTsSearch << "ms\n";
    std::cout << "==============END==============\n";
}
