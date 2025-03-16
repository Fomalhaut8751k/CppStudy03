#pragma once
#pragma once
#include<iostream>

//#include<list>

using namespace std;

class LinkStack {
	/*
		不需要容量，因为链表用不着扩容
		通过头插和头删，则第一个结点就是栈顶，不需要额外的top指示
	*/
public:
	LinkStack() {
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
	}


public:
	void push(int val) {
		Node* node = new Node(val);
		// 头插法
		node->n_Next = this->n_Head->n_Next;
		this->n_Head->n_Next = node;
	}

	void pop() {
		// 头删法
		Node* node = this->n_Head->n_Next;
		if (node != nullptr) {  // 至少不是空的
			this->n_Head->n_Next = node->n_Next;
			delete node;
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

private:
	struct Node {
		Node(int data = 0) :n_Data(data), n_Next(nullptr) {}
		int n_Data;
		Node* n_Next;
	};

	Node* n_Head;
};
