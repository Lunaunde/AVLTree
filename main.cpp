#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include "AVLTree.h"
#include "BST.h"
#include "StdAVLTree.h"

// 性能测试函数
void performanceTest(int dataSize) {
	std::cout << "数据量: " << dataSize << std::endl;

	std::vector<int> data(dataSize);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, INT_MAX);

	for (int i = 0; i < dataSize; ++i) {
		data[i] = dist(gen);
	}

	// 创建一个整数随机数生成器用于索引
	std::uniform_int_distribution<int> indexDist(0, dataSize - 1);
	std::chrono::milliseconds avlInsertTime, avlSearchTime, avlDeleteTime, rbInsertTime, rbSearchTime, rbDeleteTime, stdAVLTreeInsertTime, stdAVLTreeSearchTime, stdAVLTreeDeleteTime;

	{
		// 测试 std::set (红黑树)
		auto start = std::chrono::high_resolution_clock::now();
		std::set<int> rbTree;
		for (int val : data) {
			rbTree.insert(val);
		}
		auto end = std::chrono::high_resolution_clock::now();
		rbInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// 测试查找性能
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			rbTree.find(data[indexDist(gen)]);  // 使用整数随机索引
		}
		end = std::chrono::high_resolution_clock::now();
		rbSearchTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// 测试删除性能
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			rbTree.erase(data[indexDist(gen)]);  // 使用整数随机索引
		}
		end = std::chrono::high_resolution_clock::now();
		rbDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "红黑树 - 插入: " << rbInsertTime.count() << "ms, "
			<< "查找: " << rbSearchTime.count() << "ms, "
			<< "删除: " << rbDeleteTime.count() << "ms" << std::endl;
	}

	// 测试 AVL 树
	{
		auto start = std::chrono::high_resolution_clock::now();
		AVLTree<int> avlTree;
		for (int val : data) {
			avlTree.insert(val);
		}
		auto end = std::chrono::high_resolution_clock::now();
		avlInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// 测试查找性能
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			avlTree.search(data[indexDist(gen)]);  // 使用整数随机索引
		}
		end = std::chrono::high_resolution_clock::now();
		avlSearchTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// 测试删除性能
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			avlTree.remove(data[indexDist(gen)]);  // 使用整数随机索引
		}
		end = std::chrono::high_resolution_clock::now();
		avlDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "AVL 树 - 插入: " << avlInsertTime.count() << "ms, "
			<< "查找: " << avlSearchTime.count() << "ms, "
			<< "删除: " << avlDeleteTime.count() << "ms" << std::endl;
	}

	{
		auto start = std::chrono::high_resolution_clock::now();
		StdAVLTree<int> stdAVLTree;
        for (int val : data) {
			stdAVLTree.insert(val);
		}
        auto end = std::chrono::high_resolution_clock::now();
        stdAVLTreeInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < dataSize / 10; ++i) {
            stdAVLTree.search(data[indexDist(gen)]);  // 使用整数随机索引
        }
        end = std::chrono::high_resolution_clock::now();
        stdAVLTreeSearchTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < dataSize / 10; ++i) {
            stdAVLTree.remove(data[indexDist(gen)]);  // 使用整数随机索引
        }
        end = std::chrono::high_resolution_clock::now();
        stdAVLTreeDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "StdAVLTree - 插入: " << stdAVLTreeInsertTime.count() << "ms, "
            << "查找: " << stdAVLTreeSearchTime.count() << "ms, "
            << "删除: " << stdAVLTreeDeleteTime.count() << "ms" << std::endl;

	}
	// 输出结果

	//std::cout << "AVL/红黑树 插入时间比: "
	//	<< static_cast<double>(avlInsertTime.count()) / rbInsertTime.count() << std::endl;
	std::cout << "----------------------------------------" << std::endl;

}

// 顺序数据测试（最坏情况测试）
void sequentialTest(int dataSize) {
	std::cout << "顺序数据测试 - 数据量: " << dataSize << std::endl;

	// 测试 AVL 树
	auto start = std::chrono::high_resolution_clock::now();
	AVLTree<double> avlTree;
	for (int i = 0; i < dataSize; ++i) {
		avlTree.insert(static_cast<double>(i) + 0.5);  // 加0.5避免整数
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto avlTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// 测试 std::set
	start = std::chrono::high_resolution_clock::now();
	std::set<double> rbTree;
	for (int i = 0; i < dataSize; ++i) {
		rbTree.insert(static_cast<double>(i) + 0.5);  // 加0.5避免整数
	}
	end = std::chrono::high_resolution_clock::now();
	auto rbTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "AVL 树顺序插入: " << avlTime.count() << "ms" << std::endl;
	std::cout << "红黑树顺序插入: " << rbTime.count() << "ms" << std::endl;
	std::cout << "AVL/红黑树 时间比: "
		<< static_cast<double>(avlTime.count()) / rbTime.count() << std::endl;
	std::cout << "========================================" << std::endl;
}

int main() {

	for (int k = 0; k < 3; k++)
	{
		int inputSize, data;
		std::vector<int> datas;
		std::cout << "BST数据量: ";
		std::cin >> inputSize;
		BST<int> bst;
		for (int i = 0; i < inputSize; i++)
		{
			std::cin >> data;
			datas.push_back(data);
		}
		if (k < 2)
		{
			for(int i = 0; i < inputSize; i++)
                bst.insert(datas[i]);
            std::cout << "BST前序遍历: "<<std::endl;
			bst.POTPrint();
            std::cout << "BST中序遍历: "<<std::endl;
            bst.MOTPrint();
            std::cout << "BST后序遍历: "<<std::endl;
            bst.LOTPrint();
		}
		else
        {
			for (int i = 0; i < inputSize; i++)
			{
                bst.insert(datas[i]);
				bst.LOTPrint();
			}
			std::cout << "查找: ";
            std::cin >> data;
            std::cout << "查找结果: " << bst.search(data) << std::endl;
			
			for (int i = inputSize - 1; i >= 0; i--)
			{
				bst.remove(datas[i]);
                bst.LOTPrint();
			}
        }
	}

	//测试不同数据量
	std::vector<int> testSizes = { 100000,1000000,10000000 };
	for (int size : testSizes) {
		performanceTest(size);
	}
	return 0;
}