#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <cerrno>
#include <cctype>

#include "pair.hpp"

namespace NRBTree {
    using TUll = unsigned long long;
    const TUll MAX_LEN = 256;

    /*
        Класс-перечисление для окраски вершины к-ч дерева.
    */
    enum class TColor {
        Red,
        Black
    };

    /*
        Струткура узла к-ч дерева. Содержит указатель на левого, правого сыновей, указатель на родителя,
        поле цвета а также поле с данными, типа ключ-значение. Имеет конструктор копирования.
    */
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

    /*
        Класс к-ч дерева. Содержит в себе поле - указатель на корень. Имеет пользовательски public методы поиска
        вершины по ключу, вставки, удаления по ключу, а также загрузки в файл и выгрузки из файла. В классе находятся
        служебные private методы для реализации пользовательских методов.
    */
    class TRBTree {
        private:
            TRBTreeNode* Root;
            // Поиск вершины по ключу, результат будет записан в res. В случае успеха вернет true, иначе false.
            // В случае успеха указатель на искомую вершину будет лежать в node.
            bool Search(char* key, NPair::TPair& res, TRBTreeNode* node);
            // Вставка в дерево пары ключ-значение. В случае успеха вернет true, иначе false.
            // В случае успеха node будет указателем на родительскую вершину.
            bool Insert(const NPair::TPair& data, TRBTreeNode* node);
            // Удаление вершины из дерева по ключу. В случае успеха вернет true, иначе false.
            // В случае успеха node указывает на место, с которого удалили вершину.
            void Remove(TRBTreeNode* node);
            // Восстановление свойств к-ч дерева после удаления
            void RemoveFixUp(TRBTreeNode* node, TRBTreeNode* nodeParent);
            // Левый и правый повороты
            void LeftRotate(TRBTreeNode* node);
            void RightRotate(TRBTreeNode* node);
            // Восстановление свойств к-ч дерева после вставки
            void Recolor(TRBTreeNode* node);
            // Ддаление всего поддерева, начиная с node
            void DeleteTree(TRBTreeNode* node);
            // Вспомогательная функция для загрузки очередной вершины дерева из файла
            static void RecursiveLoad(std::ifstream& fs, NRBTree::TRBTreeNode*& node, bool& isOK);
            // Вспомогательная функция для сохранения очередной вершины дерева в файл
            static void RecursiveSave(std::ofstream& fs, NRBTree::TRBTreeNode* node, bool& isOK);

        public:
            TRBTree(): Root(NULL) {};
            // Геттер для корня дерева
            TRBTreeNode* GetRoot() const;
            // Поиск вершины по ключу, результат будет записан в res. В случае успеха вернет true, иначе false.
            bool Search(char key[MAX_LEN + 1], NPair::TPair& res);
            // Вставка в дерево пары ключ-значение. В случае успеха вернет true, иначе false.
            bool Insert(const NPair::TPair& data);
            // Удаление вершины из дерева по ключу. В случае успеха вернет true, иначе false.
            bool Remove(const char key[MAX_LEN + 1]);
            // Загрузка дерева из файла по пути path, корень нового дерева будет записан в t.
            // В случае успеха запишет true в переменную isOK, иначе false.
            static void Load(const char path[MAX_LEN + 1], NRBTree::TRBTree& t, bool& isOK);
            // Сохранение дерева в файл по пути path дерева t. В случае успеха запишет true в переменную isOK, иначе false.
            static void Save(const char path[MAX_LEN + 1], NRBTree::TRBTree& t, bool& isOK);
            ~TRBTree();
    };
}