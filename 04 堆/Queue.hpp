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

	// ���
	void push(int val) {
		/* front��0��rear�����һ��Ԫ�ص�ʱ�� */
		/*if ((rear + 1)%cap_ != front) {
			pQue_[rear] = val;
			rear = (rear + 1) % cap_;
		}*/
		if ((n_Rear + 1) % cap_ == n_Front) {  // �������
			//expand(2 * cap_);
		}
		pQue_[n_Rear] = val;
		n_Rear = (n_Rear + 1) % cap_;
	}

	// ����
	void pop() {
		if (n_Front == n_Rear) {  // ���Ϊ��
			throw "queue is empty";
		}
		n_Front = (n_Front + 1) % cap_;
	}

	// ���ض�ͷԪ��
	int front() const {
		if (n_Front == n_Rear) {
			throw "queue is empty";
		}
		return pQue_[n_Front];
	}

	// ���ض�βԪ��
	int rear() const {
		if (n_Front == n_Rear) {
			throw "queue is empty";
		}
		return pQue_[(n_Rear + cap_ - 1) % cap_];  // ��βԪ����rear��ǰһ��
	}

	// �п�
	bool empty() const {
		return n_Front == n_Rear;
	}

	// ����Ԫ�صĸ���
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

	void forEach() const {  // ��������
		for (int i = 0; i < cap_; i++) {
			cout << pQue_[i] << " ";
		}cout << endl;
	}

	void expand(int new_capacity) {
		int* p = new int[new_capacity];
		if (n_Rear >= n_Front) {  // ��ʱn_Rear��û������ǰ��ȥ
			for (int i = 0; i < cap_; i++) {
				p[i] = pQue_[i];  // ֱ�Ӱ��¿ռ�ӵ�����
			}
		}
		else {  // �¿ռ�Ҫ�ӵ��м�
			for (int i = 0; i < n_Rear; i++) {
				p[i] = pQue_[i];  // ����0��n_Rear;
			}
			for (int i = 0; i < cap_ - n_Front; i++) {
				p[new_capacity - 1 - i] = pQue_[cap_ - 1 - i];  // �Ӻ�ʼ
			}
			n_Front = new_capacity - (cap_ - n_Front);
		}
		/*
			����ֱ�ӵ���˳��Ϊfront��ǰrear�ں�
		*/
		delete[] pQue_;
		pQue_ = p;
		cap_ = new_capacity;
		// ��β���ñ�
	}

private:
	int* pQue_;
	int cap_;  // ����
	int n_Front;  // ��ͷ
	int n_Rear;  // ��β
};