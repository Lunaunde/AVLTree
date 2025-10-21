#ifndef ITERATIVEAVLTREE_H
#define ITERATIVEAVLTREE_H

template <typename T>
class FixedStack
{
private:
	int capacity;
	int index;
	T* stack;
public:
	FixedStack(int capacity);
	~FixedStack();
	bool push(const T data);
	bool pop();
	T top();
	bool empty();
};

template <typename T>
class IterativeAVLTree
{
private:
	struct Node;
	Node* root;

	short getHeight(Node* node);
	short calculateHeight(Node* node);

	void leftRotate(Node*& node);
	void rightRotate(Node*& node);
	void leftRightRotate(Node*& node);
	void rightLeftRotate(Node*& node);

	bool balanceInsert(Node** node);
public:
	IterativeAVLTree();
	~IterativeAVLTree();
	bool insert(const T data);
};

#include "IterativeAVLTree.impl.h"

#endif