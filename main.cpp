#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include "AVLTree.h"

// 性能测试函数
void performanceTest(int dataSize) {
	std::cout << "数据量: " << dataSize << std::endl;

	// 生成随机 double 数据
	std::vector<double> data(dataSize);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(1.0, dataSize * 10.0);

	for (int i = 0; i < dataSize; ++i) {
		data[i] = dist(gen);
	}

	// 创建一个整数随机数生成器用于索引
	std::uniform_int_distribution<int> indexDist(0, dataSize - 1);
	std::chrono::milliseconds avlInsertTime, avlSearchTime, avlDeleteTime, rbInsertTime, rbSearchTime, rbDeleteTime;


	// 测试 AVL 树
	{
		auto start = std::chrono::high_resolution_clock::now();
		AVLTree<double> avlTree;
		for (double val : data) {
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
		// 测试 std::set (红黑树)
		auto start = std::chrono::high_resolution_clock::now();
		std::set<double> rbTree;
		for (double val : data) {
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
	}
	// 输出结果

	std::cout << "红黑树 - 插入: " << rbInsertTime.count() << "ms, "
		<< "查找: " << rbSearchTime.count() << "ms, "
		<< "删除: " << rbDeleteTime.count() << "ms" << std::endl;

	std::cout << "AVL/红黑树 插入时间比: "
		<< static_cast<double>(avlInsertTime.count()) / rbInsertTime.count() << std::endl;
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

// 测试浮点数精度问题
void precisionTest() {
	std::cout << "浮点数精度测试..." << std::endl;

	AVLTree<double> tree;

	// 测试相近的浮点数
	tree.insert(1.0000001);
	tree.insert(1.0000002);
	tree.insert(1.0000003);

	std::cout << "查找 1.0000001: " << (tree.search(1.0000001) ? "找到" : "未找到") << std::endl;
	std::cout << "查找 1.0000002: " << (tree.search(1.0000002) ? "找到" : "未找到") << std::endl;
	std::cout << "查找 1.0000003: " << (tree.search(1.0000003) ? "找到" : "未找到") << std::endl;

	// 测试删除
	tree.remove(1.0000002);
	std::cout << "删除后查找 1.0000002: " << (tree.search(1.0000002) ? "找到" : "未找到") << std::endl;

	std::cout << "========================================" << std::endl;
}

int main() {
	std::cout << "开始 double 类型性能对比测试..." << std::endl;
	std::cout << "========================================" << std::endl;

	// 测试不同数据量
	std::vector<int> testSizes = { 1000, 10000, 100000 , 1000000 , 5000000,10000000 };

	for (int size : testSizes) {
		performanceTest(size);
	}

	//std::cout << "顺序数据最坏情况测试..." << std::endl;
	//sequentialTest(10000);
	//sequentialTest(50000);

	// 浮点数精度测试
	precisionTest();

	return 0;
}