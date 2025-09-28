#include "AVLTree.h"

template <typename T>
struct AVLTree<T>::Node
{
	T data;
	Node *left = nullptr;
	Node *right = nullptr;
	int height = 0;
};

template <typename T>
void AVLTree<T>::deleteTree(Node *&node)
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
int AVLTree<T>::getHeight(Node *node)
{ 
	if (node == nullptr)
		return -1;
	else
		return node->height;
}

template <typename T>
void AVLTree<T>::insert(const T data, Node*& node)
{
	if (node == nullptr)
		node = new Node(data);
    else if (node->data > data)
        insert(data, node->left);
    else if (node->data < data)
        insert(data, node->right);
    else
        return;

	int balance = getHeight(node->left) - getHeight(node->right);
	if (balance > 1)
	{
	}
	else if (balance < -1)
	{
	}

template <typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	deleteTree(root);
}

template <typename T>
void AVLTree<T>::insert(const T data)
{
	insert(data, this->root);
}