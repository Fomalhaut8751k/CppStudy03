#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

// 单向循环链表
/*
	单向：只能从前往后遍历
	循环：最后一节点的next记录着头结点地址，所以正常遍历会循环
*/
class CircleLink1_0 {
public:
	CircleLink1_0() {
		this->head = new Node();
	}

	void insertTail(int val) {
		// 如何遍历到最后一个结点？
		Node* node = new Node(val);
		if (this->head->n_Next == nullptr) {  // 如果一个节点都没有
			this->head->n_Next = node;
			node->n_Next = node;  // 自己放自己
		}
		else {
			// 如何处理插入的结点？
				// this->head->n_Next是第一个结点的地址
			Node* p = this->head->n_Next;  // 从第一个节点开始【不能从head开始】
			while (p->n_Next != this->head->n_Next) {  // 如果只有一个节点，不会走这个循环，但第一个就是最后一个
				p = p->n_Next;
			}// 这个时候就是最后一个结点
			node->n_Next = this->head->n_Next; // 让插入的结点指向第一个结点
			p->n_Next = node;  // 然后接到最后一个节点上
		}

	}

	// 遍历（暂停版）
	void forEach(int mode = 0) {
		Node* p = head->n_Next;
		if (this->head->n_Next != nullptr) {  // 至少有一个结点 
			if (mode == 0) {
				while (1) {
					cout << p->n_Data << " ";
					p = p->n_Next;
					system("pause");
				}
			}
			else {
				// 此时p在第一个节点，能保证进入下面的判断
				cout << p->n_Data << " ";
				p = p->n_Next;
				// 如果p->n_Next != head->n_Next,当只有一个节点时进不去
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


// 用双指针来实现
class CircleLink2_0 {
public:
	// 视频中的tail->n_Next存储的是头指针
	// 这里tail->n_Next存储的是第一个结点的地址
	CircleLink2_0() {
		this->head = new Node();
		this->tail = this->head;  // 尾指针指向末尾结点，head=tail时为空链表
	}

	// 尾插法
	void insertTail(int val) {  // 变成O(1)
		Node* node = new Node(val);
		node->n_Next = this->head->n_Next;  // 把第一个结点的地址给到node的next
		if (this->head == this->tail) {  // 原来没有结点时插入第一个结点
			node->n_Next = node;
		}
		this->tail->n_Next = node; // 原来最后一个结点后面接上node
		this->tail = node; // 指向新的尾结点
	}

	// 头插法
	void insertHead(int val) {
		Node* node = new Node(val);
		node->n_Next = this->head->n_Next;  // 接尾
		this->head->n_Next = node;  // 接头
		if (this->head == this->tail) {  // 插入前没有结点
			this->tail = node;  // 需要把在head的tail放到第一个结点上
		}
		this->tail->n_Next = this->head->n_Next;
	}

	// 删除节点
	void remove(int val, bool only = true) {
		if (this->head != this->tail) {  // 首先至少有一个结点
			Node* p = this->head->n_Next; // 指向第一个节点
			Node* p_before = this->head;  // 记录p之前的结点
			while (p != this->tail) {  // 这个循环会在最后一个节点前停下
				if (p->n_Data == val) {
					// 如果删除第一个结点的话，需要更改tail指向节点的next
					if (p == this->head->n_Next) {  // 删掉第一个后第二个就变成第一个，可能继续
						this->tail->n_Next = p->n_Next;
					}
					p_before->n_Next = p->n_Next; // 跨接

					Node* p_clear = p;
					p = p->n_Next;  // before不用变
					delete p_clear;
					if (only) {  // 如果只删第一个，删完第一个就返回
						return;
					}
				}
				else {
					p_before = p;
					p = p->n_Next;
				}
			}
			// 最后一个结点的情况比较复杂
			if (p->n_Data == val) {
				this->tail = p_before;  // tail指向前一个节点
				p_before->n_Next = this->head->n_Next;  // 接到第一个节点
				delete p;
			}
		}
	}

	// 遍历
	void forEach(bool infinite = false) {
		Node* p = head;
		if (!infinite) {
			do {
				p = p->n_Next;
				cout << p->n_Data << " ";

			} while (p != this->tail);
			cout << endl;
		}
		else {  // 无限循环
			while (1) {
				p = p->n_Next;
				cout << p->n_Data << " " << p;
				system("pause");
			}
			cout << endl;
		}
	}

	// 查询
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

	// 约瑟夫环问题
	void Josephus() {
		int m = 7;  // 每报m个数踢一个人
		int k = 3;  // 从第三个人开始

		Node* p = this->head->n_Next;
		Node* p_before = this->tail;

		while (--k > 0) {
			p_before = p;
			p = p->n_Next;
		}

		int num = 0;
		while (this->head->n_Next != this->tail) {  // 只剩下一个结点的情况
			num++;
			if (num == m) {
				num = 0;
				Node* p_next = p->n_Next;
				p_before->n_Next = p->n_Next;
				cout << p->n_Data << "\t";

				if (p == this->head->n_Next) {  // 如果删除的是第一个结点
					this->head->n_Next = p_next;
				}
				else if (p == tail) {  // 如果删除的是最后一个节点
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
		tail->n_Next = nullptr;  // 断开，变成普通链表
		do {  // 多次的去删除第一个结点
			head->n_Next = p->n_Next;
			//cout << "已删除: " << p->n_Data << endl;
			delete p;
			p = head->n_Next;
		} while (p != nullptr);
		delete head;
		head = nullptr;

		// 下面这个会爆
		//  Node* p = this->head->n_Next; 
		// 【很明显，p==this->head不会成立，p是指向第一个节点的而不是头】
		//  while (p != this->head) {  // 头删法，一个一个删掉
		//	  this->head->n_Next = p->n_Next; // 跨过去
		//	  cout << p->n_Data << endl;
		//	  delete p;  // 把p删掉
		//	  p = this->head->n_Next;  // 下一个p
		// 【
		//		并没有处理tail->next, 存储的一直是最开始的第一个节点的地址，记为&first
		//		删除最后一个节点时:
		//		this->head->n_Next = p->n_Next = &first
		//		p = this->head->n_Next = &first, 但这个空间已经被delete掉了
		// 】
		//  }
		//  delete head;  // 把头结点删掉
	}

private:
	Node* head;
	Node* tail;
};
