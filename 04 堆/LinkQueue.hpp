#pragma once
#pragma once
#include<iostream>

using namespace std;

// 链式队列
class LinkQueue {
public:
	LinkQueue() : num(0) {
		head = new Node();
		head->n_Pre = head;
		head->n_Next = head;
	}

	// 尾插法
	/*void insertTail(int data) {*/
	void push(int data) {
		// head->n_Pre : 指向最后一个结点，至少是它自己
		Node* node = new Node(data);
		head->n_Pre->n_Next = node;
		node->n_Pre = head->n_Pre;
		node->n_Next = head;
		head->n_Pre = node;
		num++;
	}

	// 头删法
	/*void deleteHead() {*/
	void pop() {
		if (head->n_Next != head) {
			Node* node = head->n_Next;
			node->n_Next->n_Pre = head;
			head->n_Next = node->n_Next;
			num--;
		}
		else {
			throw "queue is empty";
		}
	}

	// 判空
	bool empty() {
		return head->n_Next == head;
	}

	// 返回队头 
	int front() {
		if (!empty()) {
			return head->n_Next->n_Data;
		}
	}

	// 返回队尾
	int rear() {
		if (!empty()) {
			return head->n_Pre->n_Data;
		}
	}

	// 队列元素的个数
	int size() {
		return num;
	}

	// 遍历(测试)
	void forEach(bool infinite = false) const {
		Node* p = head->n_Next;
		if (!infinite) {
			while (p != head) {
				cout << p->n_Data << " ";
				p = p->n_Next;
			}cout << endl;
		}
		else {
			while (1) {
				if (p != head) {
					cout << p->n_Data << " ";
					system("pause");
				}
				p = p->n_Next;
			}
		}
	}

	~LinkQueue() {
		// head->n_Pre : 指向最后一个结点，至少是它自己
		head->n_Pre->n_Next = nullptr;  // 相当于变成非循环
		Node* p = head;
		while (p != nullptr) {
			head = head->n_Next;
			cout << "已删除：" << p->n_Data << endl;
			delete p;  // p留在head原来的位置
			p = head;
		}
		delete head;
		head = nullptr;
		num = 0;
	}


private:
	struct Node {
		Node(int data = 0) :n_Data(data) {
			n_Pre = n_Next = nullptr;
		};

		int n_Data;
		Node* n_Pre;
		Node* n_Next;


	};

	Node* head;
	int num;  // 个数
};

