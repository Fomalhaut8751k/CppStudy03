#pragma once
#pragma once
#include<iostream>

using namespace std;

class Queue {
public:
	Queue(int capacity) :cap_(capacity) {
		pQue_ = new int[cap_];
		n_Front = n_Rear = 0;
	}
	~Queue() {
		delete[] pQue_;
		pQue_ = nullptr;
	}

	// 入队
	void push(int val) {
		/* front在0，rear在最后一个元素的时候 */
		/*if ((rear + 1)%cap_ != front) {
			pQue_[rear] = val;
			rear = (rear + 1) % cap_;
		}*/
		if ((n_Rear + 1) % cap_ == n_Front) {  // 如果满了
			//expand(2 * cap_);
		}
		pQue_[n_Rear] = val;
		n_Rear = (n_Rear + 1) % cap_;
	}

	// 出队
	void pop() {
		if (n_Front == n_Rear) {  // 如果为空
			throw "queue is empty";
		}
		n_Front = (n_Front + 1) % cap_;
	}

	// 返回队头元素
	int front() const {
		if (n_Front == n_Rear) {
			throw "queue is empty";
		}
		return pQue_[n_Front];
	}

	// 返回队尾元素
	int rear() const {
		if (n_Front == n_Rear) {
			throw "queue is empty";
		}
		return pQue_[(n_Rear + cap_ - 1) % cap_];  // 队尾元素是rear的前一个
	}

	// 判空
	bool empty() const {
		return n_Front == n_Rear;
	}

	// 队列元素的个数
	int size() const {
		/*
			x x 1 2 3 4 5 6 * *
				-           -
			9 x x 2 3 4 5
			  -   -
		*/
		if (n_Rear >= n_Front) {
			return n_Rear - n_Front;
		}
		else {
			return n_Rear + cap_ - n_Front;
		}
	}

	void forEach() const {  // 仅测试用
		for (int i = 0; i < cap_; i++) {
			cout << pQue_[i] << " ";
		}cout << endl;
	}

	void expand(int new_capacity) {
		int* p = new int[new_capacity];
		if (n_Rear >= n_Front) {  // 此时n_Rear还没遍历到前面去
			for (int i = 0; i < cap_; i++) {
				p[i] = pQue_[i];  // 直接把新空间接到后面
			}
		}
		else {  // 新空间要接到中间
			for (int i = 0; i < n_Rear; i++) {
				p[i] = pQue_[i];  // 索引0到n_Rear;
			}
			for (int i = 0; i < cap_ - n_Front; i++) {
				p[new_capacity - 1 - i] = pQue_[cap_ - 1 - i];  // 从后开始
			}
			n_Front = new_capacity - (cap_ - n_Front);
		}
		/*
			或者直接调整顺序为front在前rear在后
		*/
		delete[] pQue_;
		pQue_ = p;
		cap_ = new_capacity;
		// 队尾不用变
	}

private:
	int* pQue_;
	int cap_;  // 容量
	int n_Front;  // 队头
	int n_Rear;  // 队尾
};