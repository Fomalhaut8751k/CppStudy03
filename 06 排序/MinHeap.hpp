#pragma once
#pragma once
#include<iostream>

using namespace std;

// С����
class MinHeap {
public:
	MinHeap(int pCar = 10) :pCar_(pCar), pSize_(0) {
		arr = new int[pCar_];
	}

	~MinHeap() {
		delete[] arr;
		arr = nullptr;
	}

public:
	// ����
	void push(int val) {
		if (pSize_ == pCar_) {
			expand(2 * pCar_); // ������
		}
		int idx = pSize_;
		arr[pSize_++] = val;  // �ȷ��������
		// �ӽǣ���ǰ�ڵ������һ���ڵ�
		while (idx != 0 && arr[(idx - 1) / 2] > val) {  // ������, �������ĸ���
			arr[idx] = arr[(idx - 1) / 2];  // �������������
			idx = (idx - 1) / 2;
		}
		arr[idx] = val;
	}

	// ����(�Ӷ��ϳ�)
	int pop() {
		int minVal = arr[0];  // ��Сֵ
		// ���������һ������ֵ�ŵ���
		int val = arr[pSize_-- - 1];
		// Ȼ��Ƚ������ӽڵ㣬�ĸ�С����������
		int idx = 0;
		// �ӽǣ���ǰ�ڵ�������ӽڵ�
		while (idx * 2 + 1 < pSize_) {  // ���ڵ���˵�����ӽڵ���
			if (idx * 2 + 2 < pSize_) {  // ������������ӽڵ�
				// ������ӽڵ���С
				if (arr[idx * 2 + 1] <= arr[idx * 2 + 2] && arr[idx * 2 + 1] < val) {
					arr[idx] = arr[idx * 2 + 1];
					idx = idx * 2 + 1;  // ���������ӽڵ�
				}
				// ������ӽڵ���С
				else if (arr[idx * 2 + 2] <= arr[idx * 2 + 1] && arr[idx * 2 + 2] < val) {
					arr[idx] = arr[idx * 2 + 2];
					idx = idx * 2 + 2;  // ���������ӽڵ�
				}
				else {  // val���
					break;
				}
			}
			else {  // ֻ�����ӽڵ�
				if (arr[idx * 2 + 1] < val) {
					arr[idx] = arr[idx * 2 + 1];
					idx = idx * 2 + 1;
				}
				else {  // val��С
					break;
				}
			}
		}
		// ����Ҷ�ӽ��
		arr[idx] = val;
		return minVal;
	}

	// ����
	void forEach() {
		if (pSize_ > 0) {
			cout << arr[0] << endl;
			int newline = 2;
			int line = 1;
			for (int i = 1; i <= pSize_; i++) {
				if (i == pSize_) {
					cout << endl;
					break;
				}
				cout << arr[i] << " ";
				if (i == newline) {
					cout << endl;
					line++;
					int up = 1;
					for (int j = 0; j < line; j++) {
						up *= 2;
					}
					newline += up;
				}
			}
		}
		cout << endl;
	}

private:
	// ����
	void expand(int newCar_) {
		int* newArr = new int[newCar_];
		for (int i = 0; i < pCar_; i++) {
			newArr[i] = arr[i];
		}
		pCar_ = newCar_;
		delete[] arr;
		arr = newArr;
	}

	int* arr;
	int pCar_;
	int pSize_;
};