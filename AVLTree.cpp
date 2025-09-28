#include <iostream>
#include "AVLTree.h"

template <typename T>
bool AVLTree<T>::balanced = true;

template <typename T>
struct AVLTree<T>::Node
{
	T data;
	Node* left;
	Node* right;
	int height;

	Node(const T& val) : data(val), left(nullptr), right(nullptr), height(-1) {}
};

template <typename T>
void AVLTree<T>::deleteTree(Node*& node)
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
int AVLTree<T>::getHeight(Node* node)
{
	if (node == nullptr)
		return -1;
	else
		return node->height;
}

template <typename T>
int AVLTree<T>::calculateHeight(Node* node)
{
	return getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) + 1 : getHeight(node->right) + 1;
}

template <typename T>
void AVLTree<T>::leftRotate(Node*& node)
{
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	node = right;
}

template <typename T>
void AVLTree<T>::rightRotate(Node*& node)
{
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	node = left;
}

template <typename T>
void AVLTree<T>::leftRightRotate(Node*& node)
{
	Node* left = node->left;
	Node* leftRight = left->right;
	node->left = leftRight->right;
	left->right = leftRight->left;
	leftRight->right = node;
	leftRight->left = left;
	node = leftRight;
}

template <typename T>
void AVLTree<T>::rightLeftRotate(Node*& node)
{
	Node* right = node->right;
	Node* rightLeft = right->left;
	node->right = rightLeft->left;
	right->left = rightLeft->right;
	rightLeft->left = node;
	rightLeft->right = right;
	node = rightLeft;
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

	if (balanced)
		return;
	int balance = getHeight(node->left) - getHeight(node->right);
	int nodeHeight = node->height;
	if (balance > 1)
	{
		if (getHeight(node->left->left) > getHeight(node->left->right))
		{
			rightRotate(node);
			node->right->height = (node->height) - 1;
		}
		else
		{
			leftRightRotate(node);
			node->left->height = node->height;
			node->right->height = node->height;
			(node->height)++;
		}
	}
	else if (balance < -1)
	{
		if (getHeight(node->right->right) > getHeight(node->right->left))
		{
			leftRotate(node);
			node->left->height = (node->height) - 1;
		}
		else
		{
			rightLeftRotate(node);
			node->right->height = node->height;
			node->left->height = node->height;
			(node->height)++;
		}
	}
	else
	{
		node->height = calculateHeight(node);
	}
	if (nodeHeight == node->height)
		balanced = true;
}

template <typename T>
void AVLTree<T>::safelyleftRotate(Node*& node)
{
	leftRotate(node);
	node->height = calculateHeight(node);
	node->right->height = calculateHeight(node->right);
}

template <typename T>
void AVLTree<T>::safelyrightRotate(Node*& node)
{
	rightRotate(node);
	node->height = calculateHeight(node);
	node->left->height = calculateHeight(node->left);
}

template <typename T>
bool AVLTree<T>::search(const T data, Node* node)
{ 
	if (node == nullptr)
		return false;
    if (node->data == data)
		return true;
	return (search(data, node->left) || search(data, node->right));
}

template <typename T>
void AVLTree<T>::print(Node* node)
{
	if (node != nullptr)
	{
		if (node->left != nullptr)
			print(node->left);
		std::cout << "|data: " << node->data << " height: " << node->height << std::endl;
		if (node->right != nullptr)
			print(node->right);
	}
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
	balanced = false;
	insert(data, this->root);
}

template <typename T>
bool AVLTree<T>::search(const T data)
{
	search(data, this->root);
}

template <typename T>
void AVLTree<T>::print()
{
	print(this->root);
}

template class AVLTree<int>;