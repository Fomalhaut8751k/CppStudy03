#pragma once
#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

// ˫��ѭ������

class DoubleCircleLink {
public:
	DoubleCircleLink() {
		head = new TWNode();
		head->n_Next = head;
		head->n_Pre = head;
	}

	// ͷ��
	void insertHead(int val) {
		TWNode* node = new TWNode(val);
		/*
			���һ����㶼û��
		*/
		node->n_Next = head->n_Next;  // ԭ����һ�����ӵ�node�ĺ���
		node->n_Pre = head; //  ͷ���ӵ�node��ǰ��

		head->n_Next->n_Pre = node;  // node�ӵ�ԭ���ĵ�һ�����(���ڵڶ���)��ǰ��
		head->n_Next = node;  // node�ӵ�ͷ���ĺ���
	}

	// β�巨
	void InsertTail(int val) {  // O(1) ����Ҫ������β���
		TWNode* node = new TWNode(val);
		node->n_Next = head;  // head���ӵ�node��β��
		node->n_Pre = head->n_Pre;
		head->n_Pre->n_Next = node;  // head->Pre�������һ���ڵ�
		head->n_Pre = node;
	}

	// ���ɾ��
	void remove(int val, bool only = true) {
		TWNode* p = head->n_Next;
		while (p != head) {  // �ص�head
			if (p->n_Data == val) {
				p->n_Pre->n_Next = p->n_Next;
				p->n_Next->n_Pre = p->n_Pre;
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

	// ����
	bool find(int val) {
		TWNode* p = head->n_Next;
		while (p != head) {
			if (p->n_Data == val) {
				return true;
			}
			p = p->n_Next;
		}
		return false;
	}

	// ����
	void forEach() {
		TWNode* p = head->n_Next;
		/*  p->n_Next == head�����
			(x)p��head��û�н��
			( )p�����һ�����
		*/
		while (p->n_Next != head) {
			cout << p->n_Data << " ";
			p = p->n_Next;
		}
		cout << p->n_Data << " ";
		cout << endl;
	}

	~DoubleCircleLink() {
		TWNode* p = head->n_Next;
		while (p != head) {
			TWNode* p_next = p->n_Next;  // ��¼��һ�����
			head->n_Next = p_next;  // �����һ�������������
			p->n_Next->n_Pre = head;  // �����һ�������������
			cout << "��ɾ��: " << p->n_Data << endl;
			delete p;  // ɾ����һ���ڵ�
			p = p_next;  // ָ���µĵ�һ�����
		}
	}
private:
	TWNode* head;
};