#include <iostream>
#include "AVLTree.h"
#include <random>
int main()
{
	AVLTree<int> tree;
	for (int i = 0; i < 7; i++)
	{
        tree.insert(rand());
		tree.print();
        std::cout << std::endl;
	}
}