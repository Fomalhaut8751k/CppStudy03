#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

// ����ѭ������
/*
	����ֻ�ܴ�ǰ�������
	ѭ�������һ�ڵ��next��¼��ͷ����ַ����������������ѭ��
*/
class CircleLink1_0 {
public:
	CircleLink1_0() {
		this->head = new Node();
	}

	void insertTail(int val) {
		// ��α��������һ����㣿
		Node* node = new Node(val);
		if (this->head->n_Next == nullptr) {  // ���һ���ڵ㶼û��
			this->head->n_Next = node;
			node->n_Next = node;  // �Լ����Լ�
		}
		else {
			// ��δ������Ľ�㣿
				// this->head->n_Next�ǵ�һ�����ĵ�ַ
			Node* p = this->head->n_Next;  // �ӵ�һ���ڵ㿪ʼ�����ܴ�head��ʼ��
			while (p->n_Next != this->head->n_Next) {  // ���ֻ��һ���ڵ㣬���������ѭ��������һ���������һ��
				p = p->n_Next;
			}// ���ʱ��������һ�����
			node->n_Next = this->head->n_Next; // �ò���Ľ��ָ���һ�����
			p->n_Next = node;  // Ȼ��ӵ����һ���ڵ���
		}

	}

	// ��������ͣ�棩
	void forEach(int mode = 0) {
		Node* p = head->n_Next;
		if (this->head->n_Next != nullptr) {  // ������һ����� 
			if (mode == 0) {
				while (1) {
					cout << p->n_Data << " ";
					p = p->n_Next;
					system("pause");
				}
			}
			else {
				// ��ʱp�ڵ�һ���ڵ㣬�ܱ�֤����������ж�
				cout << p->n_Data << " ";
				p = p->n_Next;
				// ���p->n_Next != head->n_Next,��ֻ��һ���ڵ�ʱ����ȥ
				while (p != head->n_Next) {
					cout << p->n_Data << " ";
					p = p->n_Next;
				}cout << endl;
			}
		}
	}

private:
	Node* head;
};


// ��˫ָ����ʵ��
class CircleLink2_0 {
public:
	// ��Ƶ�е�tail->n_Next�洢����ͷָ��
	// ����tail->n_Next�洢���ǵ�һ�����ĵ�ַ
	CircleLink2_0() {
		this->head = new Node();
		this->tail = this->head;  // βָ��ָ��ĩβ��㣬head=tailʱΪ������
	}

	// β�巨
	void insertTail(int val) {  // ���O(1)
		Node* node = new Node(val);
		node->n_Next = this->head->n_Next;  // �ѵ�һ�����ĵ�ַ����node��next
		if (this->head == this->tail) {  // ԭ��û�н��ʱ�����һ�����
			node->n_Next = node;
		}
		this->tail->n_Next = node; // ԭ�����һ�����������node
		this->tail = node; // ָ���µ�β���
	}

	// ͷ�巨
	void insertHead(int val) {
		Node* node = new Node(val);
		node->n_Next = this->head->n_Next;  // ��β
		this->head->n_Next = node;  // ��ͷ
		if (this->head == this->tail) {  // ����ǰû�н��
			this->tail = node;  // ��Ҫ����head��tail�ŵ���һ�������
		}
		this->tail->n_Next = this->head->n_Next;
	}

	// ɾ���ڵ�
	void remove(int val, bool only = true) {
		if (this->head != this->tail) {  // ����������һ�����
			Node* p = this->head->n_Next; // ָ���һ���ڵ�
			Node* p_before = this->head;  // ��¼p֮ǰ�Ľ��
			while (p != this->tail) {  // ���ѭ���������һ���ڵ�ǰͣ��
				if (p->n_Data == val) {
					// ���ɾ����һ�����Ļ�����Ҫ����tailָ��ڵ��next
					if (p == this->head->n_Next) {  // ɾ����һ����ڶ����ͱ�ɵ�һ�������ܼ���
						this->tail->n_Next = p->n_Next;
					}
					p_before->n_Next = p->n_Next; // ���

					Node* p_clear = p;
					p = p->n_Next;  // before���ñ�
					delete p_clear;
					if (only) {  // ���ֻɾ��һ����ɾ���һ���ͷ���
						return;
					}
				}
				else {
					p_before = p;
					p = p->n_Next;
				}
			}
			// ���һ����������Ƚϸ���
			if (p->n_Data == val) {
				this->tail = p_before;  // tailָ��ǰһ���ڵ�
				p_before->n_Next = this->head->n_Next;  // �ӵ���һ���ڵ�
				delete p;
			}
		}
	}

	// ����
	void forEach(bool infinite = false) {
		Node* p = head;
		if (!infinite) {
			do {
				p = p->n_Next;
				cout << p->n_Data << " ";

			} while (p != this->tail);
			cout << endl;
		}
		else {  // ����ѭ��
			while (1) {
				p = p->n_Next;
				cout << p->n_Data << " " << p;
				system("pause");
			}
			cout << endl;
		}
	}

	// ��ѯ
	bool find(int val) {
		Node* p = this->head;
		do {
			p = p->n_Next;
			if (p->n_Data == val) {
				return true;
			}
		} while (p != this->tail);
		return false;
	}

	// Լɪ������
	void Josephus() {
		int m = 7;  // ÿ��m������һ����
		int k = 3;  // �ӵ������˿�ʼ

		Node* p = this->head->n_Next;
		Node* p_before = this->tail;

		while (--k > 0) {
			p_before = p;
			p = p->n_Next;
		}

		int num = 0;
		while (this->head->n_Next != this->tail) {  // ֻʣ��һ���������
			num++;
			if (num == m) {
				num = 0;
				Node* p_next = p->n_Next;
				p_before->n_Next = p->n_Next;
				cout << p->n_Data << "\t";

				if (p == this->head->n_Next) {  // ���ɾ�����ǵ�һ�����
					this->head->n_Next = p_next;
				}
				else if (p == tail) {  // ���ɾ���������һ���ڵ�
					tail = p_before;
				}
				delete p;
				p = p_next;

				this->forEach();
				//system("pause");
			}
			else {
				p_before = p;
				p = p->n_Next;
			}
		}
		cout << tail->n_Data << endl;
	}


	~CircleLink2_0() {
		Node* p = head->n_Next;
		tail->n_Next = nullptr;  // �Ͽ��������ͨ����
		do {  // ��ε�ȥɾ����һ�����
			head->n_Next = p->n_Next;
			//cout << "��ɾ��: " << p->n_Data << endl;
			delete p;
			p = head->n_Next;
		} while (p != nullptr);
		delete head;
		head = nullptr;

		// ��������ᱬ
		//  Node* p = this->head->n_Next; 
		// �������ԣ�p==this->head���������p��ָ���һ���ڵ�Ķ�����ͷ��
		//  while (p != this->head) {  // ͷɾ����һ��һ��ɾ��
		//	  this->head->n_Next = p->n_Next; // ���ȥ
		//	  cout << p->n_Data << endl;
		//	  delete p;  // ��pɾ��
		//	  p = this->head->n_Next;  // ��һ��p
		// ��
		//		��û�д���tail->next, �洢��һֱ���ʼ�ĵ�һ���ڵ�ĵ�ַ����Ϊ&first
		//		ɾ�����һ���ڵ�ʱ:
		//		this->head->n_Next = p->n_Next = &first
		//		p = this->head->n_Next = &first, ������ռ��Ѿ���delete����
		// ��
		//  }
		//  delete head;  // ��ͷ���ɾ��
	}

private:
	Node* head;
	Node* tail;
};
