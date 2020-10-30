#pragma once

#include "pair.hpp"

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

        TRBTreeNode(): Color(TColor::Black), Parent(NULL), Left(NULL), Right(NULL), Data() {};
        TRBTreeNode(NPair::TPair<char*, TUll> p):
        Color(TColor::Black), Parent(NULL), Left(NULL), Right(NULL), Data(p) {};
        ~TRBTreeNode() = default;
    };

    class TRBTree {
        private:
            TRBTreeNode* root = NULL;

            bool Search(char* key, NPair::TPair<char*, TUll>& res, TRBTreeNode* node);
            bool Insert(const NPair::TPair<char*, TUll>& data, TRBTreeNode* node);
            bool Remove(const char* key, TRBTreeNode* node);
            void LeftRotate(TRBTreeNode* node);
            void RightRotate(TRBTreeNode* node);
            void Recolor(TRBTreeNode* node);
            void DeleteTree(TRBTreeNode* node);

        public:
            TRBTree() {};
            bool Search(char* key, NPair::TPair<char*, TUll>& res);
            bool Insert(const NPair::TPair<char*, TUll>& data);
            bool Remove(const char* key);
            ~TRBTree();
    };
}