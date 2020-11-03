#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <cerrno>

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
        NPair::TPair Data;

        TRBTreeNode(): Color(TColor::Black), Parent(NULL), Left(NULL), Right(NULL), Data() {}
        TRBTreeNode(const NPair::TPair& p): Color(TColor::Black), Parent(NULL), Left(NULL), Right(NULL), Data(p) {}
        ~TRBTreeNode() = default;
    };

    class TRBTree {
        private:
            TRBTreeNode* Root;
            
            bool Search(char* key, NPair::TPair& res, TRBTreeNode* node);
            bool Insert(const NPair::TPair& data, TRBTreeNode* node);
            void Remove(TRBTreeNode* node);
            void Transplant(TRBTreeNode* u, TRBTreeNode* v);
            void RemoveFixUp(TRBTreeNode* node, TRBTreeNode* nodeParent);
            void LeftRotate(TRBTreeNode* node);
            void RightRotate(TRBTreeNode* node);
            void Recolor(TRBTreeNode* node);
            void DeleteTree(TRBTreeNode* node);
            static void RecursiveLoad(std::ifstream& fs, NRBTree::TRBTreeNode*& node);
            static void RecursiveSave(std::ofstream& fs, NRBTree::TRBTreeNode* node);

        public:
            TRBTree(): Root(NULL) {};
            TRBTreeNode* GetRoot() const;
            bool Search(char key[MAX_LEN + 1], NPair::TPair& res);
            bool Insert(const NPair::TPair& data);
            bool Remove(const char key[MAX_LEN + 1]);
            static void Load(const char path[MAX_LEN + 1], NRBTree::TRBTree& t);
            static void Save(const char path[MAX_LEN + 1], NRBTree::TRBTree& t);
            ~TRBTree();
    };
}