#pragma once
#pragma once
#include<iostream>

using namespace std;

/*
	完全的二叉树（最后一层的叶子结点都是靠左的）
				12
		 11             7
	  8      9      3        2
	5   6
	完全的二叉树：最后一层的叶子结点都是靠左的，这样可以把二叉树存储在数组中
	结点(下标i)对应的子节点的下标分别为 2*i+1 和 2*i+2并且连续

	二叉堆就是一棵完全的二叉树，可以分为两类：大根堆和小根堆
	满足 0 <= i <= (n - 1)/2, n代表最后一个元素的下标
	如果arr[i] <= arr[2*i + 1] && arr[i] <= arr[2*i + 2]，就是小根堆（上面小，下面大）
	如果arr[i] >= arr[2*i + 1] && arr[i] >= arr[2*i + 2]，就是大根堆（下面小，上面大）

	优先级队列的底层就是大根堆

	判断：找第一个非叶子节点：最后一个节点：arr的最后一个元素的下标（长度-1）：
		(右)偶数则-2除以2 = i
		(左)奇数则-1除以2 = i
		甚至直接-1除以2即可

		然后遍历每一个非叶子结点，判断如果2*i+1和2*i+2对应的arr都满足....
*/

// 大根堆
class MaxHeap {
public:
	MaxHeap(int pCar = 10) :pCar_(pCar), pSize_(0) {
		arr = new int[pCar_];
	}

	~MaxHeap() {
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
		while (idx != 0 && arr[(idx - 1) / 2] < val) {  // 往上找, 如果上面的更小
			arr[idx] = arr[(idx - 1) / 2];  // 把上面的拿下来
			idx = (idx - 1) / 2;
		}
		arr[idx] = val;
	}

	// 出堆(从顶上出)
	void pop() {
		// 把数组最后一个结点的值放到顶
		int val = arr[pSize_-- - 1];
		// 然后比较它的子节点，哪个大就用它覆盖
		int idx = 0;
		// 视角，当前节点和它的子节点
		while (idx * 2 + 1 < pSize_) {  // 大于等于说明是子节点了
			if (idx * 2 + 2 < pSize_) {  // 如果存在左右子节点
				// 如果左子节点最大
				if (arr[idx * 2 + 1] >= arr[idx * 2 + 2] && arr[idx * 2 + 1] > val) {
					arr[idx] = arr[idx * 2 + 1];
					idx = idx * 2 + 1;  // 遍历到左子节点
				}
				// 如果右子节点最大
				else if (arr[idx * 2 + 2] >= arr[idx * 2 + 1] && arr[idx * 2 + 2] > val) {
					arr[idx] = arr[idx * 2 + 2];
					idx = idx * 2 + 2;  // 遍历到右子节点
				}
				else {  // val最大
					break;
				}
			}
			else {  // 只有左子节点
				if (arr[idx * 2 + 1] > val) {
					arr[idx] = arr[idx * 2 + 1];
					idx = idx * 2 + 1;
				}
				else {  // val最大
					break;
				}
			}
		}
		// 最后的叶子结点
		arr[idx] = val;
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
	void pop() {
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