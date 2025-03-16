#pragma once
#pragma once
#include<iostream>

using namespace std;

class LinkQueue {
public:
	LinkQueue() : num(0) {
		head = new Node();
		head->n_Pre = head;
		head->n_Next = head;
	}

	// β�巨
	/*void insertTail(int data) {*/
	void push(int data) {
		// head->n_Pre : ָ�����һ����㣬���������Լ�
		Node* node = new Node(data);
		head->n_Pre->n_Next = node;
		node->n_Pre = head->n_Pre;
		node->n_Next = head;
		head->n_Pre = node;
		num++;
	}

	// ͷɾ��
	/*void deleteHead() {*/
	int pop() {
		int var = 0;
		if (head->n_Next != head) {
			Node* node = head->n_Next;

			var = node->n_Data;

			node->n_Next->n_Pre = head;
			head->n_Next = node->n_Next;
			num--;

			return var;
		}
		else {
			throw "queue is empty";
		}
	}

	// �п�
	bool empty() {
		return head->n_Next == head;
	}

	// ���ض�ͷ 
	int front() {
		if (!empty()) {
			return head->n_Next->n_Data;
		}
	}

	// ���ض�β
	int rear() {
		if (!empty()) {
			return head->n_Pre->n_Data;
		}
	}

	// ����Ԫ�صĸ���
	int size() {
		return num;
	}

	// ����(����)
	void forEach(bool infinite = false) const {
		Node* p = head->n_Next;
		if (!infinite) {
			while (p != head) {
				cout << p->n_Data << " ";
				p = p->n_Next;
			}
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
		// head->n_Pre : ָ�����һ����㣬���������Լ�
		head->n_Pre->n_Next = nullptr;  // �൱�ڱ�ɷ�ѭ��
		Node* p = head;
		while (p != nullptr) {
			head = head->n_Next;
			cout << "��ɾ����" << p->n_Data << endl;
			delete p;  // p����headԭ����λ��
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
	int num;  // ����
};

class MyStack {
public:
	MyStack() {
		tQueue_ = &q1;
		pQueue_ = &q2;
	}

	void push(int x) {
		if (empty()) {
			tQueue_->push(x);
		}
		else {
			pQueue_->push(tQueue_->pop());
			tQueue_->push(x);
		}
	}

	int pop() {
		int var = tQueue_->pop();
		while (pQueue_->size() > 1) {
			tQueue_->push(pQueue_->pop());
		}
		auto tempQueue_ = pQueue_;
		pQueue_ = tQueue_;
		tQueue_ = tempQueue_;

		return var;
	}

	int top() {
		return tQueue_->front();
	}

	bool empty() {
		return q1.empty() && q2.empty();
	}

	void forEach() {
		pQueue_->forEach();
		tQueue_->forEach();
		cout << endl;
	}

private:
	LinkQueue q1;
	LinkQueue q2;

	LinkQueue* tQueue_;  // ����ջ��Ԫ�صĶ���
	LinkQueue* pQueue_;

};

/*
	��һ��������ʵ��
	12 5 78 9 21

	���У�12
		  ���ȳ�1����Ȼ��5���룬�ٰ�12����ȥ
		  5 12
		  ���ȳ�2����Ȼ��78���룬�ٰ�5 12����ȥ
		  78 5 12


	������������ʵ��
*/