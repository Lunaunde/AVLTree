#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include "AVLTree.h"

int main()
{
	AVLTree<int> tree;
	for (int i = 0; i < 1000000; i++)
		tree.insert(i);
	tree.search(114514);
	// �ڲ����е���
	tree.checkBalance();
	return 0;
}