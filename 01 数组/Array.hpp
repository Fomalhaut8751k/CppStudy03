#pragma once
#pragma once
#include<iostream>

using namespace std;


// 数组实现
class Array {
public:
	Array(int size = 10) {  // 有参构造函数
		this->mCap_ = size;
		this->mCur_ = 0;
		this->mpArr = new int[this->mCap_];
	}
	Array(const Array& arr) {  // 拷贝构造函数
		this->mCap_ = arr.mCap_;
		this->mCur_ = arr.mCur_;
		this->mpArr = new int[this->mCap_];  // 开辟到堆区，同时实现深拷贝
		memcpy(this->mpArr, arr.mpArr, sizeof(int) * this->mCur_);
	}

	// 尾插法
	void push_back(int val) {
		if (this->mCur_ < this->mCap_) {
			/*	this->mpArr[this->mCur_] = val;
				this->mCur_++;*/
			this->mpArr[this->mCur_++] = val;  // 写在一句
			this->expansion();
		}
	}
	// 尾删法
	int pop_back() {
		if (this->mCur_ >= 1) {
			this->mCur_--;
			return this->mpArr[this->mCur_];
		}
		else {
			return -1;
		}
	}
	// 按位置添加元素
	void insert(int pos, int val) {  // pos为索引
		if ((this->mCur_ < this->mCap_) && (pos >= 0) && (pos <= this->mCur_)) {
			for (int i = this->mCur_; i > pos; i--) {  // 移动元素
				this->mpArr[i] = this->mpArr[i - 1];
			}
			this->mpArr[pos] = val;
			this->mCur_++;
			this->expansion();
		}
	}
	// 按元素删除元素
	void erase(int val) {
		if (this->mCur_ >= 1) {
			for (int i = 0; i < this->mCur_; i++) {
				if (this->mpArr[i] == val) {
					for (int j = i; j < this->mCur_ - 1; j++) {
						this->mpArr[j] = this->mpArr[j + 1];
					}
				}
			}
			this->mCur_--;
		}
	}
	// 元素查询
	int find(int val) {
		int index = -1;
		for (int i = 0; i < this->mCur_; i++) {
			if (this->mpArr[i] == val) {
				index = i;
				break;
			}
		}
		return index;  // 如果没找到就返回-1
	}

	// 容量
	int returnCapacity() {
		return this->mCap_;
	}
	// 大小
	int returnSize() {
		return this->mCur_;
	}
	// 遍历输出
	void forEach() {
		for (int i = 0; i < this->mCur_; i++) {
			cout << this->mpArr[i] << " ";
		}cout << endl;
	}

	~Array() {
		delete[] this->mpArr;
		this->mpArr = nullptr;
	}

private:
	// 扩容？开辟一个更大的空间，把原来的拷贝过去？
	void expansion() {
		// 当容量相等时自动扩大
		if (this->mCur_ == this->mCap_) {
			int* new_mpArr = new int[this->mCap_ + 10];  // 默认扩容10
			//for (int i = 0; i < this->mCap_; i++) {  // 拷贝到新的空间
			//	new_mpArr[i] = this->mpArr[i];
			//}
			memcpy(new_mpArr, this->mpArr, sizeof(int) * this->mCur_);  // 新空间，旧空间，数据量

			this->mCap_ += 10;  // 修改容量
			delete[] this->mpArr;  // 把原数组中的数据删除
			this->mpArr = new_mpArr;
		}
	}

	int* mpArr; // 在堆上开辟
	int mCap_; // 数组容量
	int mCur_; // 数组有效元素个数 
};