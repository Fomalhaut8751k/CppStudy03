#pragma once
#pragma once
#include<iostream>

using namespace std;



// ˳��ջ   c++���������� stack
class SeqStack {
public:  // ���������
	SeqStack(int capacity = 10) :mTop(0), mCap(capacity) {
		this->mpStack = new int[mCap];
	}

	SeqStack(const SeqStack& s) {
		this->mTop = s.mTop;
		this->mCap = s.mCap;
		this->mpStack = new int[mCap];
		// ���������д��....
		for (int i = 0; i < s.mTop; i++) {
			this->mpStack[i] = s.mpStack[i];
		}
	}

	~SeqStack() {
		delete[] mpStack;
		mpStack = nullptr;
	}

public:  // ջ�ķ���
	// ��ջ
	void push(int val) {
		if (this->mTop == this->mCap) {  // ����
			this->expand();
		}
		this->mpStack[this->mTop++] = val;
	}

	// ��ջ
	void pop() {
		if (this->mTop == 0) {
			//return this->mpStack[--this->mTop];
			throw "stack is empty";  // �׳��쳣
		}
		else {
			this->mTop--;
		}

	}

	// ��ȡջ��Ԫ��
	int top() const {  // ֻ���Ĳ����ӿ�
		if (this->mTop == 0) {
			throw "stack is empty";
		}
		else {
			return this->mpStack[this->mTop - 1];
		}
	}

	// ջ��
	bool empty() const {
		return this->mTop == 0;
	}

	// ջԪ�ظ���
	int size() const {
		return this->mTop;
	}

private:
	// ����
	void expand() {
		int* newAddress = new int[this->mCap * 2];  // ��������
		// memcpy(p, mpStack, mtop*sizeof(int))  ����  
		for (int i = 0; i < this->mTop; i++) {
			newAddress[i] = this->mpStack[i];
		}
		delete[] this->mpStack;
		this->mpStack = newAddress;
		this->mCap = this->mCap * 2;
	}

	int* mpStack;
	int mTop;   // ջ��λ�ã�ָ��ջ�����ݵ���һ��λ��
	int mCap;   // ջ�ռ��С

};