#pragma once
#pragma once
#include<iostream>

//#include<list>

using namespace std;

class LinkStack {
	/*
		����Ҫ��������Ϊ�����ò�������
		ͨ��ͷ���ͷɾ�����һ��������ջ��������Ҫ�����topָʾ
	*/
public:
	LinkStack() {
		n_Head = new Node();
	};

	~LinkStack() {
		Node* p = this->n_Head->n_Next;
		while (p != nullptr) {
			this->n_Head->n_Next = p->n_Next;
			cout << "��ɾ��: " << p->n_Data << endl;
			delete p;
			p = this->n_Head->n_Next;
		}
		delete this->n_Head;
		this->n_Head = nullptr;
	}


public:
	void push(int val) {
		Node* node = new Node(val);
		// ͷ�巨
		node->n_Next = this->n_Head->n_Next;
		this->n_Head->n_Next = node;
	}

	void pop() {
		// ͷɾ��
		Node* node = this->n_Head->n_Next;
		if (node != nullptr) {  // ���ٲ��ǿյ�
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

	// ջԪ�ظ��������Ա�����Ҳ��������һ�������洢

private:
	struct Node {
		Node(int data = 0) :n_Data(data), n_Next(nullptr) {}
		int n_Data;
		Node* n_Next;
	};

	Node* n_Head;
};
