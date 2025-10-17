#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include "AVLTree.h"
#include "BST.h"
#include "StdAVLTree.h"

// ���ܲ��Ժ���
void performanceTest(int dataSize) {
	std::cout << "������: " << dataSize << std::endl;

	std::vector<int> data(dataSize);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, INT_MAX);

	for (int i = 0; i < dataSize; ++i) {
		data[i] = dist(gen);
	}

	// ����һ�������������������������
	std::uniform_int_distribution<int> indexDist(0, dataSize - 1);
	std::chrono::milliseconds avlInsertTime, avlSearchTime, avlDeleteTime, rbInsertTime, rbSearchTime, rbDeleteTime, stdAVLTreeInsertTime, stdAVLTreeSearchTime, stdAVLTreeDeleteTime;

	{
		// ���� std::set (�����)
		auto start = std::chrono::high_resolution_clock::now();
		std::set<int> rbTree;
		for (int val : data) {
			rbTree.insert(val);
		}
		auto end = std::chrono::high_resolution_clock::now();
		rbInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// ���Բ�������
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			rbTree.find(data[indexDist(gen)]);  // ʹ�������������
		}
		end = std::chrono::high_resolution_clock::now();
		rbSearchTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// ����ɾ������
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			rbTree.erase(data[indexDist(gen)]);  // ʹ�������������
		}
		end = std::chrono::high_resolution_clock::now();
		rbDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "����� - ����: " << rbInsertTime.count() << "ms, "
			<< "����: " << rbSearchTime.count() << "ms, "
			<< "ɾ��: " << rbDeleteTime.count() << "ms" << std::endl;
	}

	// ���� AVL ��
	{
		auto start = std::chrono::high_resolution_clock::now();
		AVLTree<int> avlTree;
		for (int val : data) {
			avlTree.insert(val);
		}
		auto end = std::chrono::high_resolution_clock::now();
		avlInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// ���Բ�������
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			avlTree.search(data[indexDist(gen)]);  // ʹ�������������
		}
		end = std::chrono::high_resolution_clock::now();
		avlSearchTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// ����ɾ������
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dataSize / 10; ++i) {
			avlTree.remove(data[indexDist(gen)]);  // ʹ�������������
		}
		end = std::chrono::high_resolution_clock::now();
		avlDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "AVL �� - ����: " << avlInsertTime.count() << "ms, "
			<< "����: " << avlSearchTime.count() << "ms, "
			<< "ɾ��: " << avlDeleteTime.count() << "ms" << std::endl;
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
            stdAVLTree.search(data[indexDist(gen)]);  // ʹ�������������
        }
        end = std::chrono::high_resolution_clock::now();
        stdAVLTreeSearchTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < dataSize / 10; ++i) {
            stdAVLTree.remove(data[indexDist(gen)]);  // ʹ�������������
        }
        end = std::chrono::high_resolution_clock::now();
        stdAVLTreeDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "StdAVLTree - ����: " << stdAVLTreeInsertTime.count() << "ms, "
            << "����: " << stdAVLTreeSearchTime.count() << "ms, "
            << "ɾ��: " << stdAVLTreeDeleteTime.count() << "ms" << std::endl;

	}
	// ������

	//std::cout << "AVL/����� ����ʱ���: "
	//	<< static_cast<double>(avlInsertTime.count()) / rbInsertTime.count() << std::endl;
	std::cout << "----------------------------------------" << std::endl;

}

// ˳�����ݲ��ԣ��������ԣ�
void sequentialTest(int dataSize) {
	std::cout << "˳�����ݲ��� - ������: " << dataSize << std::endl;

	// ���� AVL ��
	auto start = std::chrono::high_resolution_clock::now();
	AVLTree<double> avlTree;
	for (int i = 0; i < dataSize; ++i) {
		avlTree.insert(static_cast<double>(i) + 0.5);  // ��0.5��������
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto avlTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// ���� std::set
	start = std::chrono::high_resolution_clock::now();
	std::set<double> rbTree;
	for (int i = 0; i < dataSize; ++i) {
		rbTree.insert(static_cast<double>(i) + 0.5);  // ��0.5��������
	}
	end = std::chrono::high_resolution_clock::now();
	auto rbTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "AVL ��˳�����: " << avlTime.count() << "ms" << std::endl;
	std::cout << "�����˳�����: " << rbTime.count() << "ms" << std::endl;
	std::cout << "AVL/����� ʱ���: "
		<< static_cast<double>(avlTime.count()) / rbTime.count() << std::endl;
	std::cout << "========================================" << std::endl;
}

int main() {

	for (int k = 0; k < 3; k++)
	{
		int inputSize, data;
		std::vector<int> datas;
		std::cout << "BST������: ";
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
            std::cout << "BSTǰ�����: "<<std::endl;
			bst.POTPrint();
            std::cout << "BST�������: "<<std::endl;
            bst.MOTPrint();
            std::cout << "BST�������: "<<std::endl;
            bst.LOTPrint();
		}
		else
        {
			for (int i = 0; i < inputSize; i++)
			{
                bst.insert(datas[i]);
				bst.LOTPrint();
			}
			std::cout << "����: ";
            std::cin >> data;
            std::cout << "���ҽ��: " << bst.search(data) << std::endl;
			
			for (int i = inputSize - 1; i >= 0; i--)
			{
				bst.remove(datas[i]);
                bst.LOTPrint();
			}
        }
	}

	//���Բ�ͬ������
	std::vector<int> testSizes = { 100000,1000000,10000000 };
	for (int size : testSizes) {
		performanceTest(size);
	}
	return 0;
}