#pragma once
#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

// 双向循环链表

class DoubleCircleLink {
public:
	DoubleCircleLink() {
		head = new TWNode();
		head->n_Next = head;
		head->n_Pre = head;
	}

	// 头插
	void insertHead(int val) {
		TWNode* node = new TWNode(val);
		/*
			如果一个结点都没有
		*/
		node->n_Next = head->n_Next;  // 原来第一个结点接到node的后面
		node->n_Pre = head; //  头结点接到node的前面

		head->n_Next->n_Pre = node;  // node接到原来的第一个结点(现在第二个)的前面
		head->n_Next = node;  // node接到头结点的后面
	}

	// 尾插法
	void InsertTail(int val) {  // O(1) 不需要遍历找尾结点
		TWNode* node = new TWNode(val);
		node->n_Next = head;  // head链接到node的尾部
		node->n_Pre = head->n_Pre;
		head->n_Pre->n_Next = node;  // head->Pre就是最后一个节点
		head->n_Pre = node;
	}

	// 结点删除
	void remove(int val, bool only = true) {
		TWNode* p = head->n_Next;
		while (p != head) {  // 回到head
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

	// 查找
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

	// 遍历
	void forEach() {
		TWNode* p = head->n_Next;
		/*  p->n_Next == head的情况
			(x)p是head且没有结点
			( )p是最后一个结点
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
			TWNode* p_next = p->n_Next;  // 记录下一个结点
			head->n_Next = p_next;  // 跨过第一个结点向右链接
			p->n_Next->n_Pre = head;  // 跨过第一个结点向左链接
			cout << "已删除: " << p->n_Data << endl;
			delete p;  // 删除第一个节点
			p = p_next;  // 指向新的第一个结点
		}
	}
private:
	TWNode* head;
};