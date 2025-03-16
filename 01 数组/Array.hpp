#pragma once
#pragma once
#include<iostream>

using namespace std;


// ����ʵ��
class Array {
public:
	Array(int size = 10) {  // �вι��캯��
		this->mCap_ = size;
		this->mCur_ = 0;
		this->mpArr = new int[this->mCap_];
	}
	Array(const Array& arr) {  // �������캯��
		this->mCap_ = arr.mCap_;
		this->mCur_ = arr.mCur_;
		this->mpArr = new int[this->mCap_];  // ���ٵ�������ͬʱʵ�����
		memcpy(this->mpArr, arr.mpArr, sizeof(int) * this->mCur_);
	}

	// β�巨
	void push_back(int val) {
		if (this->mCur_ < this->mCap_) {
			/*	this->mpArr[this->mCur_] = val;
				this->mCur_++;*/
			this->mpArr[this->mCur_++] = val;  // д��һ��
			this->expansion();
		}
	}
	// βɾ��
	int pop_back() {
		if (this->mCur_ >= 1) {
			this->mCur_--;
			return this->mpArr[this->mCur_];
		}
		else {
			return -1;
		}
	}
	// ��λ�����Ԫ��
	void insert(int pos, int val) {  // posΪ����
		if ((this->mCur_ < this->mCap_) && (pos >= 0) && (pos <= this->mCur_)) {
			for (int i = this->mCur_; i > pos; i--) {  // �ƶ�Ԫ��
				this->mpArr[i] = this->mpArr[i - 1];
			}
			this->mpArr[pos] = val;
			this->mCur_++;
			this->expansion();
		}
	}
	// ��Ԫ��ɾ��Ԫ��
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
	// Ԫ�ز�ѯ
	int find(int val) {
		int index = -1;
		for (int i = 0; i < this->mCur_; i++) {
			if (this->mpArr[i] == val) {
				index = i;
				break;
			}
		}
		return index;  // ���û�ҵ��ͷ���-1
	}

	// ����
	int returnCapacity() {
		return this->mCap_;
	}
	// ��С
	int returnSize() {
		return this->mCur_;
	}
	// �������
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
	// ���ݣ�����һ������Ŀռ䣬��ԭ���Ŀ�����ȥ��
	void expansion() {
		// ���������ʱ�Զ�����
		if (this->mCur_ == this->mCap_) {
			int* new_mpArr = new int[this->mCap_ + 10];  // Ĭ������10
			//for (int i = 0; i < this->mCap_; i++) {  // �������µĿռ�
			//	new_mpArr[i] = this->mpArr[i];
			//}
			memcpy(new_mpArr, this->mpArr, sizeof(int) * this->mCur_);  // �¿ռ䣬�ɿռ䣬������

			this->mCap_ += 10;  // �޸�����
			delete[] this->mpArr;  // ��ԭ�����е�����ɾ��
			this->mpArr = new_mpArr;
		}
	}

	int* mpArr; // �ڶ��Ͽ���
	int mCap_; // ��������
	int mCur_; // ������ЧԪ�ظ��� 
};