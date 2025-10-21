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

	void leftRotate(Node** nodePtr);
	void rightRotate(Node** nodePtr);
	void leftRightRotate(Node** nodePtr);
	void rightLeftRotate(Node** nodePtr);

	bool balanceInsert(Node** nodePtr);
	bool balanceRemove(Node** nodePtr);

	T findAndRemoveMin(Node** nodePtr)
public:
	IterativeAVLTree();
	~IterativeAVLTree();

	bool insert(const T data);
	bool search(const T data);
	bool remove(const T data);
};

#include "IterativeAVLTree.impl.h"

#endif