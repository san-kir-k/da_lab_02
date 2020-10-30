#pragma once

#include "pair.hpp"
#include <iostream>

namespace NRBTree {
    using TUll = unsigned long long;
    const TUll MAX_LEN = 256;

    enum class TColor {
        Red,
        Black
    };

    struct TRBTreeNode {
        TColor Color = TColor::Black;
        TRBTreeNode* Parent;
        TRBTreeNode* Left;
        TRBTreeNode* Right;
        NPair::TPair<char*, TUll> Data;

        TRBTreeNode();
        TRBTreeNode(const NPair::TPair<char*, TUll>& p);
        ~TRBTreeNode();
    };

    class TRBTree {
        private:
            TRBTreeNode* root;
            
            bool Search(char* key, NPair::TPair<char*, TUll>& res, TRBTreeNode* node);
            bool Insert(const NPair::TPair<char*, TUll>& data, TRBTreeNode* node);
            bool Remove(const char* key, TRBTreeNode* node);
            void LeftRotate(TRBTreeNode* node);
            void RightRotate(TRBTreeNode* node);
            void Recolor(TRBTreeNode* node);
            void DeleteTree(TRBTreeNode* node);

        public:
            TRBTree(): root(NULL) {};
            bool Search(char* key, NPair::TPair<char*, TUll>& res);
            bool Insert(const NPair::TPair<char*, TUll>& data);
            bool Remove(const char* key);
            ~TRBTree();
    };
}