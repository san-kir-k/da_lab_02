#include <string>
#include <cstring>
#include <iostream>

#include "rb_tree.hpp"
#include "pair.hpp"

namespace NRBTree {
    bool TRBTree::Search(char* key, NPair::TPair<char*, TUll>& res) {
        return Search(key, res, root);
    }
    bool TRBTree::Search(char* key, NPair::TPair<char*, TUll>& res, TRBTreeNode* node) {
        if (node == NULL) {
            return false;
        } else if (key == node->Data.First) {
            res = node->Data;
            return true;
        } else {
            TRBTreeNode* to = (strcmp(key, node->Data.First) < 0) ? node->Left : node->Right;
            return Search(key, res, to);
        }
    }

    bool TRBTree::Insert(const NPair::TPair<char*, TUll>& data) {
        if (root == NULL) {
            root = new TRBTreeNode(data);
            root->Color=TColor::Black;
            return true;
        } else {
            return Insert(data, root);
        }
    }
    bool TRBTree::Insert(const NPair::TPair<char*, TUll>& data, TRBTreeNode* node) {
        std::string key = data.First;
        if (node->Data.First == key) {
            return false;
        } else if ((key.compare(node->Data.First) < 0)) {
            if (node->Left == NULL) {
                node->Left = new TRBTreeNode(data);
                node->Left->Parent = node;
                node->Left->Color = TColor::Red;
                if (node->Color == TColor::Red) {
                    // recolor
                }
                return true;
            } else {
                return Insert(data, node->Left);
            }
        } else {
            if (node->Right == NULL) {
                node->Right = new TRBTreeNode(data);
                node->Right->Parent = node;
                node->Right->Color = TColor::Red;
                if (node->Color == TColor::Red) {
                    // recolor
                }
                return true;
            } else {
                return Insert(data, node->Right);
            }
        }
    }

    bool TRBTree::Remove(const char* key) {
        return Remove(key, root);
    }
    bool TRBTree::Remove(const char* key, TRBTreeNode* node) {
        // ...
    }

    void TRBTree::LeftRotate(TRBTreeNode* node) {
        // ...
    }

    void TRBTree::RightRotate(TRBTreeNode* node) {
        // ...
    }

    void TRBTree::DeleteTree(TRBTreeNode* node) {
        if (node == NULL) {
            return;
        } else {
            DeleteTree(node->Left);
            DeleteTree(node->Right);
            Remove(node->Data.First, node);
        }
    }

    TRBTree::~TRBTree() {
        DeleteTree(root);
    }
}