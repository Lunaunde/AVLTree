#ifndef BST_H
#define BST_H
template<typename T>
class BST
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

    void FMAR(Node*& root); // 删除最小节点并存入result中
    void insert(const T data, Node*& root);
    void remove(const T data, Node*& root);
    void search(const T data, Node* node);

    void POTPrint(Node* node);
    void MOTPrint(Node* node);
    void LOTPrint(Node* node);

public:
    BST();
    ~BST();

    bool insert(const T data);
    bool search(const T data);
    bool remove(const T data);

    void POTPrint(); // 先序遍历
    void MOTPrint(); // 中序遍历
    void LOTPrint(); // 后序遍历
};

#include "BST.impl.h"

#endif