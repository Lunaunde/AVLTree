#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include "AVLTree.h"

// ���ܲ��Ժ���
void performanceTest(int dataSize) {
	std::cout << "������: " << dataSize << std::endl;

	// ������� double ����
	std::vector<double> data(dataSize);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(1.0, dataSize * 10.0);

	for (int i = 0; i < dataSize; ++i) {
		data[i] = dist(gen);
	}

	// ����һ�������������������������
	std::uniform_int_distribution<int> indexDist(0, dataSize - 1);
	std::chrono::milliseconds avlInsertTime, avlSearchTime, avlDeleteTime, rbInsertTime, rbSearchTime, rbDeleteTime;


	// ���� AVL ��
	{
		auto start = std::chrono::high_resolution_clock::now();
		AVLTree<double> avlTree;
		for (double val : data) {
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
		// ���� std::set (�����)
		auto start = std::chrono::high_resolution_clock::now();
		std::set<double> rbTree;
		for (double val : data) {
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
	}
	// ������

	std::cout << "����� - ����: " << rbInsertTime.count() << "ms, "
		<< "����: " << rbSearchTime.count() << "ms, "
		<< "ɾ��: " << rbDeleteTime.count() << "ms" << std::endl;

	std::cout << "AVL/����� ����ʱ���: "
		<< static_cast<double>(avlInsertTime.count()) / rbInsertTime.count() << std::endl;
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

// ���Ը�������������
void precisionTest() {
	std::cout << "���������Ȳ���..." << std::endl;

	AVLTree<double> tree;

	// ��������ĸ�����
	tree.insert(1.0000001);
	tree.insert(1.0000002);
	tree.insert(1.0000003);

	std::cout << "���� 1.0000001: " << (tree.search(1.0000001) ? "�ҵ�" : "δ�ҵ�") << std::endl;
	std::cout << "���� 1.0000002: " << (tree.search(1.0000002) ? "�ҵ�" : "δ�ҵ�") << std::endl;
	std::cout << "���� 1.0000003: " << (tree.search(1.0000003) ? "�ҵ�" : "δ�ҵ�") << std::endl;

	// ����ɾ��
	tree.remove(1.0000002);
	std::cout << "ɾ������� 1.0000002: " << (tree.search(1.0000002) ? "�ҵ�" : "δ�ҵ�") << std::endl;

	std::cout << "========================================" << std::endl;
}

int main() {
	std::cout << "��ʼ double �������ܶԱȲ���..." << std::endl;
	std::cout << "========================================" << std::endl;

	// ���Բ�ͬ������
	std::vector<int> testSizes = { 1000, 10000, 100000 , 1000000 , 5000000,10000000 };

	for (int size : testSizes) {
		performanceTest(size);
	}

	//std::cout << "˳��������������..." << std::endl;
	//sequentialTest(10000);
	//sequentialTest(50000);

	// ���������Ȳ���
	precisionTest();

	return 0;
}