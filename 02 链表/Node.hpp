#pragma once
#pragma once
#pragma once
#include <iostream>

using namespace std;

class Node {  // 节点类(单链表)
public:
	Node(int data = 0, Node* next = nullptr) :n_Data(data), n_Next(next) {}
	Node(const Node& n) {
		this->n_Data = n.n_Data;
		this->n_Next = n.n_Next;
		cout << "Node的拷贝构造函数调用" << endl;
	}

	Node* operator++(int) {
		return this->n_Next;
	}

	int n_Data;
	Node* n_Next;
};

class TWNode {  // 双向节点
public:
	TWNode(int data = 0) {
		this->n_Data = data;
		this->n_Pre = nullptr;
		this->n_Next = nullptr;
	}
	int n_Data;
	TWNode* n_Pre;
	TWNode* n_Next;
};