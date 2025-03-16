#pragma once
#pragma once
#include<iostream>
#include<stack>

using namespace std;

class LinkStack {
	/*
		不需要容量，因为链表用不着扩容
		通过头插和头删，则第一个结点就是栈顶，不需要额外的top指示
	*/
public:
	LinkStack() :num(0) {
		n_Head = new Node();
	};

	~LinkStack() {
		Node* p = this->n_Head->n_Next;
		while (p != nullptr) {
			this->n_Head->n_Next = p->n_Next;
			cout << "已删除: " << p->n_Data << endl;
			delete p;
			p = this->n_Head->n_Next;
		}
		delete this->n_Head;
		this->n_Head = nullptr;
		num = 0;
	}


public:
	void push(int val) {
		Node* node = new Node(val);
		// 头插法
		node->n_Next = this->n_Head->n_Next;
		this->n_Head->n_Next = node;
		num++;
	}

	void pop() {
		// 头删法
		Node* node = this->n_Head->n_Next;
		if (node != nullptr) {  // 至少不是空的
			this->n_Head->n_Next = node->n_Next;
			delete node;
			num--;
		}
		else {
			throw "stack is empty";
		}
	}

	int top() const {
		Node* node = this->n_Head->n_Next;
		if (node != nullptr) {
			return node->n_Data;
		}
		else {
			throw "stack is empty";
		}
	}

	bool empty() const {
		return this->n_Head->n_Next == nullptr;
	}

	// 栈元素个数：可以遍历，也可以先用一个变量存储

	void forEach(bool reverse = false) {
		int* arr_int = new int[num];
		int index = 0;
		Node* p = n_Head->n_Next;
		while (p != nullptr) {
			arr_int[index] = p->n_Data;
			p = p->n_Next;
			index++;
		}
		for (int i = 0; i < num; i++) {
			if (reverse) {
				cout << arr_int[i] << " ";
			}
			else {
				cout << arr_int[num - 1 - i] << " ";
			}
		}
		delete[] arr_int;
		arr_int = nullptr;
	}


private:
	struct Node {
		Node(int data = 0) :n_Data(data), n_Next(nullptr) {}
		int n_Data;
		Node* n_Next;
	};

	Node* n_Head;
	int num;
};


class MyQueue {
	// 用两个栈构成的队列
public:
	void push(int x) {
		s1.push(x);
	}

	int pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		int top = s2.top();
		s2.pop();
		return top;
	}

	bool empty() {
		return s1.empty() && s2.empty();
	}

	int peek() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.top();
	}

	void foreach() {
		if (s2.empty()) {
			s1.forEach();
		}
		else {
			s2.forEach(true);
			s1.forEach();
		}
		cout << endl;
	}

private:
	LinkStack s1;
	LinkStack s2;
};