#include <iostream>
template <typename T>
struct BST<T>::Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
void BST<T>::deleteTree(Node*& node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = nullptr;
    }
}

template <typename T>
void BST<T>::FMAR(Node*& node)
{
    if (node->left != nullptr)
        FMAR(node->left);
    else
    {
        result = node->data;
        Node* temp = node;
        node = node->right;
        delete temp;
        return;
    }
}

template <typename T>
void BST<T>::insert(const T data, Node*& node)
{
    if (node == nullptr)
    {
        node = new Node(data);
        success = true;
    }
    else if (node->data > data)
        insert(data, node->left);
    else if (node->data < data)
        insert(data, node->right);
    else
        return;
}

template <typename T>
void BST<T>::remove(const T data, Node*& node)
{
    if (node == nullptr)
        return;
    if (node->data > data)
        remove(data, node->left);
    else if (node->data < data)
        remove(data, node->right);
    else
    { 
        success = true;
        if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else
        {
            FMAR(node->right);
            node->data = result;
        }
    }
}

template <typename T>
void BST<T>::search(const T data, Node* node)
{
    if (node == nullptr)
        return;
    else if (node->data > data)
        search(data, node->left);
    else if (node->data < data)
        search(data, node->right);
    else
        success = true;
}

template <typename T>
void BST<T>::POTPrint(Node* node)
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        POTPrint(node->left);
        POTPrint(node->right);
    }
}

template <typename T>
void BST<T>::MOTPrint(Node* node)
{
    if (node != nullptr)
    {
        MOTPrint(node->left);
        std::cout << node->data << " ";
        MOTPrint(node->right);
    }
}

template <typename T>
void BST<T>::LOTPrint(Node* node)
{
    if (node != nullptr)
    {
        LOTPrint(node->left);
        LOTPrint(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
BST<T>::BST()
{
    root = nullptr;
}

template <typename T>
BST<T>::~BST()
{
    deleteTree(root);
}

template <typename T>
bool BST<T>::insert(const T data)
{
    success = false;
    insert(data, this->root);
    return success;
}

template <typename T>
bool BST<T>::remove(const T data)
{
    success = false;
    remove(data, this->root);
    return success;
}

template <typename T>
bool BST<T>::search(const T data)
{
    success = false;
    search(data, this->root);
    return success;
}

template <typename T>
void BST<T>::POTPrint()
{
    POTPrint(this->root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::MOTPrint()
{
    MOTPrint(this->root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::LOTPrint()
{
    LOTPrint(this->root);
    std::cout << std::endl;
}