#pragma once
#pragma once
#include<iostream>

using namespace std;



// 顺序栈   c++容器适配器 stack
class SeqStack {
public:  // 构造和析构
	SeqStack(int capacity = 10) :mTop(0), mCap(capacity) {
		this->mpStack = new int[mCap];
	}

	SeqStack(const SeqStack& s) {
		this->mTop = s.mTop;
		this->mCap = s.mCap;
		this->mpStack = new int[mCap];
		// 将数据逐个写入....
		for (int i = 0; i < s.mTop; i++) {
			this->mpStack[i] = s.mpStack[i];
		}
	}

	~SeqStack() {
		delete[] mpStack;
		mpStack = nullptr;
	}

public:  // 栈的方法
	// 入栈
	void push(int val) {
		if (this->mTop == this->mCap) {  // 扩容
			this->expand();
		}
		this->mpStack[this->mTop++] = val;
	}

	// 出栈
	void pop() {
		if (this->mTop == 0) {
			//return this->mpStack[--this->mTop];
			throw "stack is empty";  // 抛出异常
		}
		else {
			this->mTop--;
		}

	}

	// 获取栈顶元素
	int top() const {  // 只读的操作接口
		if (this->mTop == 0) {
			throw "stack is empty";
		}
		else {
			return this->mpStack[this->mTop - 1];
		}
	}

	// 栈空
	bool empty() const {
		return this->mTop == 0;
	}

	// 栈元素个数
	int size() const {
		return this->mTop;
	}

private:
	// 扩容
	void expand() {
		int* newAddress = new int[this->mCap * 2];  // 扩容两倍
		// memcpy(p, mpStack, mtop*sizeof(int))  或者  
		for (int i = 0; i < this->mTop; i++) {
			newAddress[i] = this->mpStack[i];
		}
		delete[] this->mpStack;
		this->mpStack = newAddress;
		this->mCap = this->mCap * 2;
	}

	int* mpStack;
	int mTop;   // 栈顶位置，指向栈顶数据的上一个位置
	int mCap;   // 栈空间大小

};