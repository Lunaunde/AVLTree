//自己写的优化AVL树
#ifndef AVLTREE_H
#define AVLTREE_H 

template<typename T>
class AVLTree
{
    static_assert(std::is_default_constructible_v<T>, "Type must be default constructible");
    static_assert(std::is_copy_constructible_v<T>, "Type must be copy constructible");

    // 最重要：确保类型支持比较操作
    static_assert(std::is_same_v<decltype(std::declval<T>() < std::declval<T>()), bool>,"Type must support < operator");
    static_assert(std::is_same_v<decltype(std::declval<T>() == std::declval<T>()), bool>,"Type must support == operator");

	private:
		struct Node;
		Node *root;
        bool balanced;
        bool success;
        T result;
        void deleteTree(Node *&node);
		short getHeight(Node *node);
        short calculateHeight(Node* node);
        void leftRotate(Node *&node);
        void rightRotate(Node *&node);
        void leftRightRotate(Node *&node);
        void rightLeftRotate(Node *&node);

        void balanceInsert(Node *&root);
        void balanceRemove(Node *&root);

        void findAndRemoveMin(Node *&root); // 删除最小节点并存入result

        void insert(const T data, Node *&root);
        void remove(const T data, Node*& root);

        void safelyleftRotate(Node *&node);
        void safelyrightRotate(Node *&node);

        void search(const T data, Node *node);
        bool fastSearch(const T data,Node *node);

        void print(Node *node);

	public:
        AVLTree();
        ~AVLTree();

        bool insert(const T data);
        bool search(const T data);
        bool fastSearch(const T data);
        bool remove(const T data);

        void checkBalance(Node* node, const std::string& path);
        void checkBalance();

        void print();
};

#include "AVLTree.impl.h"

#endif