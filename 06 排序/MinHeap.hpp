#pragma once
#pragma once
#include<iostream>

using namespace std;

// 小根堆
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
	// 插入
	void push(int val) {
		if (pSize_ == pCar_) {
			expand(2 * pCar_); // 先扩容
		}
		int idx = pSize_;
		arr[pSize_++] = val;  // 先放在最后面
		// 视角，当前节点和它上一个节点
		while (idx != 0 && arr[(idx - 1) / 2] > val) {  // 往上找, 如果上面的更大
			arr[idx] = arr[(idx - 1) / 2];  // 把上面的拿下来
			idx = (idx - 1) / 2;
		}
		arr[idx] = val;
	}

	// 出堆(从顶上出)
	int pop() {
		int minVal = arr[0];  // 最小值
		// 把数组最后一个结点的值放到顶
		int val = arr[pSize_-- - 1];
		// 然后比较它的子节点，哪个小就用它覆盖
		int idx = 0;
		// 视角，当前节点和它的子节点
		while (idx * 2 + 1 < pSize_) {  // 大于等于说明是子节点了
			if (idx * 2 + 2 < pSize_) {  // 如果存在左右子节点
				// 如果左子节点最小
				if (arr[idx * 2 + 1] <= arr[idx * 2 + 2] && arr[idx * 2 + 1] < val) {
					arr[idx] = arr[idx * 2 + 1];
					idx = idx * 2 + 1;  // 遍历到左子节点
				}
				// 如果右子节点最小
				else if (arr[idx * 2 + 2] <= arr[idx * 2 + 1] && arr[idx * 2 + 2] < val) {
					arr[idx] = arr[idx * 2 + 2];
					idx = idx * 2 + 2;  // 遍历到右子节点
				}
				else {  // val最大
					break;
				}
			}
			else {  // 只有左子节点
				if (arr[idx * 2 + 1] < val) {
					arr[idx] = arr[idx * 2 + 1];
					idx = idx * 2 + 1;
				}
				else {  // val最小
					break;
				}
			}
		}
		// 最后的叶子结点
		arr[idx] = val;
		return minVal;
	}

	// 遍历
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
	// 扩容
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