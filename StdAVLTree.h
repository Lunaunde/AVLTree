//较为标准的AVL树实现
#ifndef STD_AVLTREE_H
#define STD_AVLTREE_H

template<typename T>
class StdAVLTree
{
    static_assert(std::is_default_constructible_v<T>, "Type must be default constructible");
    static_assert(std::is_copy_constructible_v<T>, "Type must be copy constructible");

    // 最重要：确保类型支持比较操作
    static_assert(std::is_same_v<decltype(std::declval<T>() < std::declval<T>()), bool>, "Type must support < operator");
    static_assert(std::is_same_v<decltype(std::declval<T>() == std::declval<T>()), bool>, "Type must support == operator");

private:
    struct Node;
    Node* root;
    bool success;
    T result;
    void deleteTree(Node*& node);
    short getHeight(Node* node);
    short calculateHeight(Node* node);
    void leftRotate(Node*& node);
    void rightRotate(Node*& node);
    void leftRightRotate(Node*& node);
    void rightLeftRotate(Node*& node);
    void balance(Node*& node);

    void findAndRemoveMin(Node*& root); // 删除最小节点并存入result

    void insert(const T data, Node*& root);
    void remove(const T data, Node*& root);

    void search(const T data, Node* node);

public:
    StdAVLTree();
    ~StdAVLTree();

    bool insert(const T data);
    bool search(const T data);
    bool remove(const T data);
};

#include "StdAVLTree.impl.h"

#endif