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
        } else if (strcmp(key, node->Data.First) == 0) {
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
        const char* key = data.First;
        if (strcmp(key, node->Data.First) == 0) {
            return false;
        } else if (strcmp(key, node->Data.First) < 0) {
            if (node->Left == NULL) {
                node->Left = new TRBTreeNode(data);
                node->Left->Parent = node;
                node->Left->Color = TColor::Red;
                if (node->Color == TColor::Red) {
                    Recolor(node->Left);
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
                    Recolor(node->Right);
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
        TRBTreeNode* rightSon = node->Right;
        node->Right = rightSon->Left;
        if (rightSon->Left != NULL) {
            rightSon->Left->Parent = node;
        }
        rightSon->Parent = node->Parent;
        if (node->Parent == NULL) {
            root = rightSon;
        } else if (node == node->Parent->Left) {
            node->Parent->Left = rightSon;
        } else {
            node->Parent->Right = rightSon;
        }
        rightSon->Left = node;
        node->Parent = rightSon; 
    }
    void TRBTree::RightRotate(TRBTreeNode* node) {
        TRBTreeNode* leftSon = node->Left;
        node->Left = leftSon->Right;
        if (leftSon->Right != NULL) {
            leftSon->Right->Parent = node;
        }
        leftSon->Parent = node->Parent;
        if (node->Parent == NULL) {
            root = leftSon;
        } else if (node == node->Parent->Right) {
            node->Parent->Right = leftSon;
        } else {
            node->Parent->Left = leftSon;
        }
        leftSon->Right = node;
        node->Parent = leftSon; 
    }

    void TRBTree::Recolor(TRBTreeNode* node) {
        TRBTreeNode* grandParent = node->Parent->Parent;
        if (grandParent->Left == node->Parent) {
            if (grandParent->Right->Color == TColor::Red) {
                grandParent->Left->Color = TColor::Black;
                grandParent->Right->Color = TColor::Black;
                grandParent->Color = TColor::Red;
                if (root == grandParent) {
                    grandParent->Color = TColor::Black;
                    return;
                }
                if (grandParent->Color == TColor::Red && grandParent->Parent->Color == TColor::Red) {
                    Recolor(grandParent);
                }
                return;
            } else if (grandParent->Right->Color == TColor::Black || grandParent->Right == NULL) {
                if (node == node->Parent->Left) {
                    grandParent->Color = TColor::Red;
                    node->Parent->Color = TColor::Black;
                    RightRotate(grandParent);
                    return;
                } else {
                    LeftRotate(node->Parent);
                    node->Color = TColor::Black;
                    node->Parent->Color = TColor::Red;
                    RightRotate(node->Parent);
                    return;
                }
            }
        } else {
            if (grandParent->Left->Color == TColor::Red) {
                grandParent->Right->Color = TColor::Black;
                grandParent->Left->Color = TColor::Black;
                grandParent->Color = TColor::Red;
                if (root == grandParent) {
                    grandParent->Color = TColor::Black;
                    return;
                }
                if (grandParent->Color == TColor::Red && grandParent->Parent->Color == TColor::Red) {
                    Recolor(grandParent);
                }
                return;
            } else if (grandParent->Left->Color == TColor::Black || grandParent->Left == NULL) {
                if (node == node->Parent->Right) {
                    grandParent->Color = TColor::Red;
                    node->Parent->Color = TColor::Black;
                    LeftRotate(grandParent);
                    return;
                } else {
                    RightRotate(node->Parent);
                    node->Color = TColor::Black;
                    node->Parent->Color = TColor::Red;
                    LeftRotate(node->Parent);
                    return;
                }
            }
        }
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