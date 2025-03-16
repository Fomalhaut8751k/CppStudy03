#pragma once
#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

class DoubleLink {
public:
	DoubleLink() {
		this->head = new TWNode();
	}
	// ͷ��
	void insertHead(int val) {
		TWNode* node = new TWNode(val);  // �����ڵ�
		TWNode* node_next = head->n_Next;  // ��¼��ǰ�ĵ�һ����㣬������Ϊnode����һ�����
		node->n_Next = node_next;  // ��ԭ����һ�����ӵ�node֮��
		node->n_Pre = head;  // ��node��pre��Ϊhead
		head->n_Next = node; // head��next��Ϊnode���ͷ��
		if (node_next != nullptr) {  // ���ԭ��û�н�㣬��ônode_next����nullptr
			node_next->n_Pre = node;
		}
	}

	// β��
	void insertTail(int val) {
		TWNode* p = head;
		while (p->n_Next != nullptr) {
			p = p->n_Next;
		}
		TWNode* node = new TWNode(val);
		p->n_Next = node;
		node->n_Pre = p;
	}

	// ����
	void forEach() {
		TWNode* p = head->n_Next;
		while (p != nullptr) {
			cout << p->n_Data << " ";
			p = p->n_Next;
		}
		cout << endl;
	}

	// �ڵ�ɾ��
	void remove(int val, bool only = true) {
		TWNode* p = head->n_Next;
		while (p != nullptr) {
			if (p->n_Data == val) {
				p->n_Pre->n_Next = p->n_Next;
				if (p->n_Next != nullptr) {
					p->n_Next->n_Pre = p->n_Pre;
				}
				TWNode* p_next = p->n_Next;
				delete p;
				if (only) {
					return;
				}
				p = p_next;
			}
			else {
				p = p->n_Next;
			}
		}
	}

	// �ڵ�����
	bool find(int val) {
		TWNode* p = head->n_Next;
		while (p != nullptr) {
			if (p->n_Data == val) {
				return true;
			}
			p = p->n_Next;
		}
		return false;
	}

	~DoubleLink() {
		TWNode* p = head->n_Next;
		while (p != nullptr) {
			head->n_Next = p->n_Next;
			cout << "��ɾ��: " << p->n_Data << endl;
			delete p;
			p = head->n_Next;
		}
		delete head;
	}

private:
	TWNode* head;
};