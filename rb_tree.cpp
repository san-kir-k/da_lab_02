#include "rb_tree.hpp"

namespace NRBTree {
    TRBTreeNode::TRBTreeNode(): Color(TColor::Black), Parent(NULL), Left(NULL), Right(NULL) {
        char* key = new char[MAX_LEN + 1];
        Data = {key, 0};
    }
    TRBTreeNode::TRBTreeNode(const NPair::TPair<char*, TUll>& p):
    Color(TColor::Black), Parent(NULL), Left(NULL), Right(NULL) {
        char* key = new char[MAX_LEN + 1];
        TUll val = p.Second;
        for (int i = 0; i < MAX_LEN + 1; ++i) {
            key[i] = p.First[i];
        } 
        Data = {key, val};
    }
    TRBTreeNode::~TRBTreeNode() {
        delete[] Data.First;
    }

    TRBTreeNode* TRBTree::GetRoot() const {
        return Root;
    }

    bool TRBTree::Search(char* key, NPair::TPair<char*, TUll>& res) {
        return Search(key, res, Root);
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
        if (Root == NULL) {
            Root = new TRBTreeNode(data);
            Root->Color=TColor::Black;
            return true;
        } else {
            return Insert(data, Root);
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
        return Remove(key, Root);
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
            Root = rightSon;
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
            Root = leftSon;
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
            if (grandParent->Right != NULL && grandParent->Right->Color == TColor::Red) {
                grandParent->Left->Color = TColor::Black;
                grandParent->Right->Color = TColor::Black;
                grandParent->Color = TColor::Red;
                if (Root == grandParent) {
                    grandParent->Color = TColor::Black;
                    return;
                }
                if (grandParent->Parent != NULL && grandParent->Color == TColor::Red && grandParent->Parent->Color == TColor::Red) {
                    Recolor(grandParent);
                }
                return;
            } else if (grandParent->Right == NULL || 
            (grandParent->Right != NULL && grandParent->Right->Color == TColor::Black)) {
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
            if (grandParent->Left != NULL && grandParent->Left->Color == TColor::Red) {
                grandParent->Right->Color = TColor::Black;
                grandParent->Left->Color = TColor::Black;
                grandParent->Color = TColor::Red;
                if (Root == grandParent) {
                    grandParent->Color = TColor::Black;
                    return;
                }
                if (grandParent->Parent != NULL && grandParent->Color == TColor::Red && grandParent->Parent->Color == TColor::Red) {
                    Recolor(grandParent);
                }
                return;
            } else if (grandParent->Left == NULL || 
            (grandParent->Left != NULL && grandParent->Left->Color == TColor::Black )) {
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
        DeleteTree(Root);
    }

    void TRBTree::RecursiveLoad(std::ifstream& fs, NRBTree::TRBTreeNode*& node) {
        NPair::TPair<char*, TUll> data;
        char color;
        char key[MAX_LEN + 1];
        fs.read(key, sizeof(char) * MAX_LEN);
        key[MAX_LEN] = '\0';
        data.First = key;
        fs.read((char*)&data.Second, sizeof(TUll));
        fs.read((char*)&color, sizeof(char));    
        if (data.First[0] == '#') {
            return; 
        }
        node = new TRBTreeNode(data);
        if (color == 'r') {
            node->Color = TColor::Red;
        } else {
            node->Color = TColor::Black;
        }
        RecursiveLoad(fs, node->Left); 
        RecursiveLoad(fs, node->Right); 
        if (node->Left != NULL) {
            node->Left->Parent = node;
        }
        if (node->Right != NULL) {
            node->Right->Parent = node;
        }
    }

    void TRBTree::Load(const char* path, NRBTree::TRBTree& t) {
        std::ifstream fs;
        fs.open(path, std::ios::binary);
        RecursiveLoad(fs, t.Root);
        fs.close();
    }

    void TRBTree::RecursiveSave(std::ofstream& fs, NRBTree::TRBTreeNode* t) {
        if (t == NULL) {
            char key[MAX_LEN + 1] = "#";
            TUll val = 0;
            char color = 'b';
            fs.write(key, sizeof(char) * MAX_LEN);
            fs.write((char*)&val, sizeof(TUll));
            fs.write((char*)&color, sizeof(char));      
            return;
        }
        char color = t->Color == TColor::Black ? 'b' : 'r';
        fs.write(t->Data.First, sizeof(char) * MAX_LEN);
        fs.write((char*)&(t->Data.Second), sizeof(TUll));
        fs.write((char*)&color, sizeof(char));    
        RecursiveSave(fs, t->Left);
        RecursiveSave(fs, t->Right);
    }

    void TRBTree::Save(const char* path, NRBTree::TRBTree& t) {
        std::ofstream fs;
        fs.open(path, std::ios::binary);
        RecursiveSave(fs, t.Root);
        fs.close();
    }
}