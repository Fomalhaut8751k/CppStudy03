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
	// 头插
	void insertHead(int val) {
		TWNode* node = new TWNode(val);  // 创建节点
		TWNode* node_next = head->n_Next;  // 记录当前的第一个结点，即将成为node的下一个结点
		node->n_Next = node_next;  // 把原来第一个结点接到node之后
		node->n_Pre = head;  // 把node的pre置为head
		head->n_Next = node; // head的next置为node完成头接
		if (node_next != nullptr) {  // 如果原来没有结点，那么node_next就是nullptr
			node_next->n_Pre = node;
		}
	}

	// 尾插
	void insertTail(int val) {
		TWNode* p = head;
		while (p->n_Next != nullptr) {
			p = p->n_Next;
		}
		TWNode* node = new TWNode(val);
		p->n_Next = node;
		node->n_Pre = p;
	}

	// 遍历
	void forEach() {
		TWNode* p = head->n_Next;
		while (p != nullptr) {
			cout << p->n_Data << " ";
			p = p->n_Next;
		}
		cout << endl;
	}

	// 节点删除
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

	// 节点搜索
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
			cout << "已删除: " << p->n_Data << endl;
			delete p;
			p = head->n_Next;
		}
		delete head;
	}

private:
	TWNode* head;
};