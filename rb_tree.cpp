#include "rb_tree.hpp"

namespace NRBTree {
    TRBTreeNode* TRBTree::GetRoot() const {
        return Root;
    }

    bool TRBTree::Search(char key[MAX_LEN + 1], NPair::TPair& res) {
        return Search(key, res, Root);
    }
    bool TRBTree::Search(char key[MAX_LEN + 1], NPair::TPair& res, TRBTreeNode* node) {
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

    bool TRBTree::Insert(const NPair::TPair& data) {
        if (Root == NULL) {
            Root = new TRBTreeNode(data);
            Root->Color=TColor::Black;
            return true;
        } else {
            return Insert(data, Root);
        }
    }
    bool TRBTree::Insert(const NPair::TPair& data, TRBTreeNode* node) {
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

    bool TRBTree::Remove(const char key[MAX_LEN + 1]) {
        TRBTreeNode* node = Root;
        while (node != NULL && strcmp(key, node->Data.First) != 0) {
            TRBTreeNode* to = (strcmp(key, node->Data.First) < 0) ? node->Left : node->Right;
            node = to;
        }
        if (node == NULL) {
            return false;
        }
        Remove(node);
        return true;
    }
    // void TRBTree::Remove(TRBTreeNode* node) {
    //     bool delRep = false;
    //     TRBTreeNode* toDelete = node;
    //     TColor toDeleteColor = toDelete->Color;
    //     TRBTreeNode* toReplace;
    //     if (node->Left == NULL) {
    //         if (node->Right == NULL) {
    //             delRep = true;
    //             node->Right = new TRBTreeNode;
    //             node->Right->Parent = node;
    //             node->Right->Color = TColor::Black;
    //         }
    //         toReplace = node->Right;
    //         Transplant(node, node->Right);
    //     } else if (node->Right == NULL) {
    //         toReplace = node->Left;
    //         Transplant(node, node->Left);
    //     } else {
    //         TRBTreeNode* minInRight = node->Right;
    //         while(minInRight->Left != NULL) {
    //             minInRight = minInRight->Left;
    //         }
    //         toDelete = minInRight;
    //         toDeleteColor = toDelete->Color;
    //         if (toDelete->Right == NULL) {
    //             delRep = true;
    //             toDelete->Right = new TRBTreeNode;
    //             toDelete->Right->Parent = toDelete;
    //             toDelete->Right->Color = TColor::Black;
    //         }
    //         toReplace = toDelete->Right;
    //         if (toDelete->Parent == node) {
    //             toReplace->Parent = toDelete;
    //         } else {
    //             Transplant(toDelete, toDelete->Right);
    //             toDelete->Right = node->Right;
    //             toDelete->Right->Parent = toDelete;
    //         }
    //         Transplant(node, toDelete);
    //         toDelete->Left = node->Left;
    //         toDelete->Left->Parent = toDelete;
    //         toDelete->Color = node->Color;
    //     }
    //     if (toDeleteColor == TColor::Black) {
    //         RemoveFixUp(toReplace);
    //     }
    //     if (delRep) {
    //         if (toReplace->Parent != NULL && toReplace == toReplace->Parent->Left) {
    //             toReplace->Parent->Left = NULL;
    //         } else if (toReplace->Parent != NULL && toReplace == toReplace->Parent->Right) {
    //             toReplace->Parent->Right = NULL;
    //         }
    //         delete toReplace;
    //     }
    //     delete node;
    // }

    // void TRBTree::RemoveFixUp(TRBTreeNode* node) {
    //     while (node != NULL && node->Color == TColor::Black && node != Root) {
    //         if (node == node->Parent->Left) {
    //             TRBTreeNode* brother = node->Parent->Right;
    //             if (brother->Color == TColor::Red) {
    //                 brother->Color = TColor::Black;
    //                 node->Parent->Color = TColor::Red;
    //                 LeftRotate(node->Parent);
    //                 brother = node->Parent->Right;
    //             }
    //             if (brother->Left->Color == TColor::Black && brother->Right->Color == TColor::Black) {
    //                 brother->Color = TColor::Red;
    //                 node = node->Parent;
    //             } else {
    //                 if (brother->Right->Color == TColor::Black) {
    //                     brother->Left->Color = TColor::Black;
    //                     brother->Color = TColor::Red;
    //                     RightRotate(brother);
    //                     brother = node->Parent->Right;
    //                 }
    //                 brother->Color = node->Parent->Color;
    //                 node->Parent->Color = TColor::Black;
    //                 brother->Right->Color = TColor::Black;
    //                 LeftRotate(node->Parent);
    //                 break;
    //             }
    //         } else {
    //             TRBTreeNode* brother = node->Parent->Left;
    //             if (brother->Color == TColor::Red) {
    //                 brother->Color = TColor::Black;
    //                 node->Parent->Color = TColor::Red;
    //                 RightRotate(node->Parent);
    //                 brother = node->Parent->Left;
    //             }
    //             if (brother->Right->Color == TColor::Black && brother->Left->Color == TColor::Black) {
    //                 brother->Color = TColor::Red;
    //                 node = node->Parent;
    //             } else {
    //                 if (brother->Left->Color == TColor::Black) {
    //                     brother->Right->Color = TColor::Black;
    //                     brother->Color = TColor::Red;
    //                     LeftRotate(brother);
    //                     brother = node->Parent->Left;
    //                 }
    //                 brother->Color = node->Parent->Color;
    //                 node->Parent->Color = TColor::Black;
    //                 brother->Left->Color = TColor::Black;
    //                 RightRotate(node->Parent);
    //                 break;
    //             }
    //         }
    //     }
    //     node->Color = TColor::Black;
    // }

    // void TRBTree::Transplant(TRBTreeNode* u, TRBTreeNode* v) {
    //     if (u->Parent == NULL) {
    //         Root = v;
    //         Root->Parent = NULL;
    //     } else if (u == u->Parent->Left) {
    //         u->Parent->Left = v;
    //     } else {
    //         u->Parent->Right = v;
    //     }
    //     if (v != NULL && v != Root) {
    //         v->Parent = u->Parent;
    //     }
    // }

    void TRBTree::LeftRotate(TRBTreeNode* node) {
        TRBTreeNode* rightSon = node->Right;
        if (rightSon == NULL) {
            return;
        }
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
        if (leftSon == NULL) {
            return;
        }
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
            delete node;
        }
    }

    TRBTree::~TRBTree() {
        DeleteTree(Root);
        Root = NULL;
    }

    void TRBTree::RecursiveLoad(std::ifstream& fs, NRBTree::TRBTreeNode*& node, bool& isOK) {
        if (!isOK) {
            return;
        }
        NPair::TPair data;
        short len = 0;
        fs.read((char*)&len, sizeof(short));
        if (len == -1) {
            return;
        } else if (len != -1 && (len <= 0 || len > MAX_LEN)) {
            std::cout << "ERROR: Wrong file format\n";
            isOK = false;
            return;
        }
        char color;
        for (int i = 0; i < len; ++i) {
            fs.read(&(data.First[i]), sizeof(char));
            if (isalpha(data.First[i]) == 0) {
                std::cout << "ERROR: Wrong file format\n";
                isOK = false;
                return;
            }
        }
        data.First[len] = '\0';
        fs.read((char*)&data.Second, sizeof(TUll));
        fs.read((char*)&color, sizeof(char));    
        node = new TRBTreeNode(data);
        if (color == 'r') {
            node->Color = TColor::Red;
        } else if (color == 'b') {
            node->Color = TColor::Black;
        } else {
            std::cout << "ERROR: Wrong file format\n";
            isOK = false;
            return;
        }
        RecursiveLoad(fs, node->Left, isOK); 
        RecursiveLoad(fs, node->Right, isOK); 
        if (node->Left != NULL) {
            node->Left->Parent = node;
        }
        if (node->Right != NULL) {
            node->Right->Parent = node;
        }
    }

    void TRBTree::Load(const char* path, NRBTree::TRBTree& t, bool& isOK) {
        std::ifstream fs;
        fs.open(path, std::ios::binary);
        RecursiveLoad(fs, t.Root, isOK);
        fs.close();
    }

    void TRBTree::RecursiveSave(std::ofstream& fs, NRBTree::TRBTreeNode* t, bool& isOK) {
        short len = 0;
        if (t == NULL) {
            len = -1;
            fs.write((char*)&len, sizeof(short));    
            return;
        }
        char color = t->Color == TColor::Black ? 'b' : 'r';
        for (int i = 0; i < MAX_LEN && t->Data.First[i] != '\0' && isalpha(t->Data.First[i]) != 0; ++i) {
            len++;
        }
        fs.write((char*)&len, sizeof(short));
        fs.write(t->Data.First, sizeof(char) * len);
        fs.write((char*)&(t->Data.Second), sizeof(TUll));
        fs.write((char*)&color, sizeof(char));    
        RecursiveSave(fs, t->Left, isOK);
        RecursiveSave(fs, t->Right, isOK);
    }

    void TRBTree::Save(const char* path, NRBTree::TRBTree& t, bool& isOK) {
        std::ofstream fs;
        fs.open(path, std::ios::binary);
        RecursiveSave(fs, t.Root, isOK);
        fs.close();
    }

    void TRBTree::Remove(TRBTreeNode* node) {
        TRBTreeNode* toDelete = node;
        TColor toDeleteColor = toDelete->Color;
        TRBTreeNode* toReplace;
        TRBTreeNode* toReplaceParent;
        if (node->Left == NULL) {
            toReplace = node->Right;
            if (toReplace != NULL) {
                toReplace->Parent = node->Parent;
            } else {
                toReplaceParent = node->Parent;
                if (node == Root) {
                    toReplaceParent = NULL;
                    Root = NULL;
                }
            }
            if (node->Parent != NULL) {
                if (node->Parent->Left == node) {
                    node->Parent->Left = toReplace;
                } else {
                    node->Parent->Right = toReplace;
                }
            } else {
                Root = toReplace;
            }
        } else if (node->Right == NULL) {
            toReplace = node->Left;
            toReplace->Parent = node->Parent;
            toReplaceParent = node->Parent;
            if (node->Parent != NULL) {
                if (node->Parent->Left == node) {
                    node->Parent->Left = toReplace;
                } else {
                    node->Parent->Right = toReplace;
                }
            } else {
                Root = toReplace;
            }           
        } else {
            TRBTreeNode* minInRight = node->Right;
            while(minInRight->Left != NULL) {
                minInRight = minInRight->Left;
            }
            toDelete = minInRight;
            toDeleteColor = toDelete->Color;
            toReplace = toDelete->Right;
            if (toDelete->Parent == node) {
                if (toReplace != NULL) {
                    toReplace->Parent = toDelete;
                }
                toReplaceParent = toDelete;
            } else {
                toDelete->Parent->Left = toReplace;
                if (toReplace != NULL) {
                    toReplace->Parent = toDelete->Parent;
                }
                toReplaceParent = toDelete->Parent;
                toDelete->Right = node->Right;
                toDelete->Right->Parent = toDelete;
            }
            if (node->Parent != NULL) {
                if (node->Parent->Left == node) {
                    node->Parent->Left = toDelete;
                } else {
                    node->Parent->Right = toDelete;
                }
            } else {
                Root = toDelete;
            }
            toDelete->Parent = node->Parent;
            toDelete->Left = node->Left;
            toDelete->Left->Parent = toDelete;
            toDelete->Color = node->Color;
        }
        if (toDeleteColor == TColor::Black) {
            RemoveFixUp(toReplace, toReplaceParent);
        }
        delete node;
    }

     void TRBTree::RemoveFixUp(TRBTreeNode* node, TRBTreeNode* nodeParent) {
        while ((node == NULL || node->Color == TColor::Black) && node != Root) {
            TRBTreeNode* brother;
            if (node == nodeParent->Left) {
                brother = nodeParent->Right;
                if (brother->Color == TColor::Red) {
                    brother->Color = TColor::Black;
                    nodeParent->Color = TColor::Red;
                    LeftRotate(nodeParent);
                    brother = nodeParent->Right;
                }
                if (brother->Color == TColor::Black) {
                    if ((brother->Left == NULL || brother->Left->Color == TColor::Black)
                    && (brother->Right == NULL || brother->Right->Color == TColor::Black)) {
                        brother->Color = TColor::Red;
                        node = nodeParent;
                        if (node != NULL) {
                            nodeParent = node->Parent;
                        }
                    } else {
                        if (brother->Right == NULL || brother->Right->Color == TColor::Black) {
                            brother->Left->Color = TColor::Black;
                            brother->Color = TColor::Red;
                            RightRotate(brother);
                            brother = nodeParent->Right;
                        }
                        brother->Color = nodeParent->Color;
                        nodeParent->Color = TColor::Black;
                        brother->Right->Color = TColor::Black;
                        LeftRotate(nodeParent);
                        break;
                    }
                }
            } else {
                brother = nodeParent->Left;
                if (brother->Color == TColor::Red) {
                    brother->Color = TColor::Black;
                    nodeParent->Color = TColor::Red;
                    RightRotate(nodeParent);
                    brother = nodeParent->Left;
                }
                if (brother->Color == TColor::Black) {
                    if (brother->Right->Color == TColor::Black && brother->Left->Color == TColor::Black) {
                        brother->Color = TColor::Red;
                        node = nodeParent;
                        if (node != NULL) {
                            nodeParent = node->Parent;
                        }
                    } else {
                        if (brother->Left->Color == TColor::Black) {
                            brother->Right->Color = TColor::Black;
                            brother->Color = TColor::Red;
                            LeftRotate(brother);
                            brother = nodeParent->Left;
                        }
                        brother->Color = nodeParent->Color;
                        nodeParent->Color = TColor::Black;
                        brother->Left->Color = TColor::Black;
                        RightRotate(nodeParent);
                        break;
                    }
                }
            }
        }
        if (node != NULL) {
            node->Color = TColor::Black;
        }
     }
}
