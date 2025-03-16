#pragma once
#pragma once
#pragma once
#include<iostream>

#include "MinHeap.hpp"

using namespace std;

/*
	稳定性：
	在原始的数据序列中，相同元素，经过排序后，他们的前后顺序并没有发生改变
	就叫做稳定的，否则叫做不稳定的排序
	稳定性影响有关联关系的数据
*/

// ----冒泡排序算法-----------------------------------------------------------------------------------------
void BubbleSort(int arr[], int size) {
	/*
		每次遍历，前后比较，如果前大于后，就交换，这样第一次遍历后最大的就去到最后了
		第二次遍历的时候就遍历到倒数第二个即可

		如果遇到了一次遍历中，没有发生任何一次交换，则说明已经正确的顺序了，不需要接下来
		的遍历。
	*/
	for (int i = 0; i < size - 1; i++) {
		bool label = false;
		for (int j = 0; j < size - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				label = true;
			}
		}
		if (!label) {  // 如果没有发生一次交换，则可以直接润了
			return;
		}
	}
	// 最好时间复杂度：O(n)
	// 最差时间复杂度：O(n^2)
	// 空间复杂度：O(1)
	// 稳定
}

// ----选择排序算法-----------------------------------------------------------------------------------------
void ChoiceSort(int arr[], int size) {
	/*
		从第一个元素开始，把它视为最小的元素，然后往后找
		如果找到了,就把他视为最小的元素，然后接着找，找比这“最小的元素”还要小的
		最后的“最小的元素”就是真正最小的元素，然后把它与第一个元素交换。

		从第二个元素开始，把它视为第二小的元素，然后......
	*/
	for (int i = 0; i < size - 1; i++) {
		int mNumber_ = arr[i];  // 先假设每次遍历的头是最小的
		int mIndex_ = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < mNumber_) {  // 如果比“最小的”小
				mIndex_ = j;  //  记录索引 
				mNumber_ = arr[j];  // 记录值，并视为“真正的”“最小的值”
			}
		}
		if (mIndex_ != i) {  // 如果发生改变，即确实最开始的假设是错误的
			// 交换真正的最小值和最开始假设的最小值（即每次遍历的开头）
			int temp = arr[i];
			arr[i] = arr[mIndex_];
			arr[mIndex_] = temp;
		}
	}
	// 最好时间复杂度：O(n^2)
	// 最差时间复杂度：O(n^2)
	// 空间复杂度：O(1)
	// 不稳定
	// 5 5 3 ...... 第一个5会和3交换，导致两个5的位置前后不一样
}

// ----插入排序算法-----------------------------------------------------------------------------------------
void InsertSort(int arr[], int size) {
	/*
		如果数据趋于有序，那么插入排序是所有排序中效率最高的
		在基础排序中，效率上：插入>冒泡=选择

		从头到尾遍历，对于当前的位置，往前找到比它大的第一个数(指往前找的这个过程的第一个)
		然后插到其后面。
		如果没有比它大的则按兵不动
	*/
	for (int i = 1; i < size; i++) {
		int val = arr[i];
		int j = i - 1;
		//for (; j >= 0; j--) {
		//	if (arr[j] > val) {  // 如果比它大
		//		arr[j + 1] = arr[j];  // 那就把这个大的往后移动一格
		//	}
		//	else {  // 比它小于等于
		//		arr[j + 1] = val;  // 就可以把val放在它的后面
		//		break;
		//	}
		//}
		//if (j == -1) {  // 如果j==-1说明前面的都比它大
		//	arr[0] = val;  // 就把他放在第一个位置
		//}
		for (; j >= 0; j--) {
			if (arr[j] <= val) {  // 如果比它小
				break;
			}
			arr[j + 1] = arr[j];  // 把这个大的往后移动一格
		}
		arr[j + 1] = val;
	}
	// 最好时间复杂度：O(n)
	// 最差时间复杂度：O(n^2)
	// 空间复杂度：O(1)
	// 稳定
}
// 给快排用的
void InsertSort(int arr[], int L_, int R_) {
	for (int i = L_; i <= R_; i++) {
		int val = arr[i];
		int j = i - 1;
		for (; j >= 0; j--) {
			if (arr[j] <= val) {  // 如果比它小
				break;
			}
			arr[j + 1] = arr[j];  // 把这个大的往后移动一格
		}
		arr[j + 1] = val;
	}
}

// ----希尔排序算法-----------------------------------------------------------------------------------------
void ShellSort(int arr[], int size) {
	/*
		对插入算法的优化，让全局数据尽快的趋于有序
		通过分组的插入排序实现
	*/
	int gap = size / 2;
	while (gap >= 1) {
		// 遍历每一个组
		//for (int i = 0; i < gap; i++){
		//	// 每一个组：i, i+gap, i+2*gap, ...但是从第二个开始
		//	for (int j = i + gap; j < size;) {  // j先指向组内第二个元素
		//		int val = arr[j]; // 当前遍历到的元素
		//		int k = j - gap;
		//		// ----进行插入排序--------------------------------------------
		//		for (; k >= 0; ) {
		//			if (arr[k] > val) {
		//				arr[k + gap] = arr[k];
		//			}
		//			else {
		//				arr[k + gap] = val;
		//				break;
		//			}
		//			k -= gap;
		//		}
		//		if (k < i) {
		//			arr[i] = val;
		//		}
		//		// -----------------------------------------------------------
		//		j += gap;
		//	}
		//}

		// 并不需要分组处理
		// j遍历到某个元素，就处理当前元素所在的组，即j，j+gap, j+2*gap,...
		// 8 86 79 78 47 80 54 81 60 82
		// *       *(j)     *        *
		//   *        *(j+1)   *       
		//      *        *(j+2)   *         
		for (int j = gap; j < size; j++) {  // 从gap开始，即从“第一个元素”开始
			int val = arr[j]; // 当前遍历到的元素
			int k = j - gap;
			// ----进行插入排序--------------------------------------------
			for (; k >= 0; k -= gap) {
				if (arr[k] <= val) {
					break;
				}
				arr[k + gap] = arr[k];
			}
			arr[k + gap] = val;
			// -----------------------------------------------------------
		}
		gap /= 2;

	}
	// 最好时间复杂度：O(n)
	// 最差时间复杂度：O(n^2)
	// 空间复杂度：O(1)
	// 不稳定
	// 当相同的两个数倍被分到不同的组，可能后面那个别调到他组里更前面的位置，导致.....
}

// ----快速排序算法-----------------------------------------------------------------------------------------
void QuickSort(int arr[], int L_, int R_) {
	/*
		选取一个基准数，把小于基准数的元素都调准到它的左边，大于的就调准到右边
		然后对基准数左右的序列继续进行这样的操作，直到整个序列变成有序的
	*/
	int L = L_, R = R_;

	int val = arr[L];  // 选取基准数(一般取开头的)val

#if 0 // ------------------------------------------------------------------------
	// 快速排序优化一
	/*
		快速排序的优化：当数据趋于有序的时候，快排效率低，而插排效率高
		随着快排的进行，数据趋于有序，在后面可以使用插排来代替快排
	*/
	if (R_ - L_ <= 50) {
		InsertSort(arr, L_, R_);
		return;
	}
#endif 
#if 1 // ------------------------------------------------------------------------ 
	// 快速排序优化二
	/*
		采用“三数取中”法，找合适的基准数
		本身在一般情况下效率就是O(nlogn)，面对数据趋于有序的时候，三数取中可以选择一个
		相对中间的值，来减少退化严重
	*/
	val = arr[(L + R) / 2];
#endif


	// 快速排序的主要逻辑
	while (L < R) {  // 两个下标L，R指向区间的头尾
		// 从R开始往前找第一个小于val的数字，放到L的地方，L++；
		while (arr[R] >= val && R > L) {
			R--;
		}
		/*if (L >= R) {
			break;
		}
		else {
			arr[L++] = arr[R];
		}*/
		if (L < R) {
			arr[L++] = arr[R];
		}

		// 从L开始往后找第一个大于val的数字，放大R的地方，R--；
		while (arr[L] <= val && L < R) {
			L++;
		}
		if (L < R) {
			arr[R--] = arr[L];
		}
	}
	arr[L] = val;  // 把val值给到重叠的位置，这样其之前的值都小于，之后的值都大于

	if (L_ < L - 1) {  // 如果剩下的区间长度大于1（长度为1是等于）
		QuickSort(arr, L_, L - 1);
	}
	if (L + 1 < R_) {  // 如果剩下的区间长度大于1（长度为1是等于）
		QuickSort(arr, L + 1, R_);
	}
	// 平均(最好)时间复杂度：O(nlogn)
	// 最差时间复杂度：O(n^2) [完全不平衡的树，退化的最差情况]

	// 最好空间复杂度：O(logn) [递归的深度——影响栈的空间]
	// 最差空间复杂度：O(n) [完全不平衡的树，退化的最差情况]
	// 不稳定
	// L在++的时候，第一个遇到的大于val的值就被扔到后面去了
}

// ----归并排序算法-----------------------------------------------------------------------------------------
void MergeSort(int arr[], int begin, int end, int* arr_temp) {
	/*
		"分治思想"，先进行序列的划分，再进行元素的有序合并。
	*/
	int number = end + 1 - begin;
	int mid = (begin + end) / 2;

	// 返回条件
	if (number == 1) {
		return;
	}

	// 递
	MergeSort(arr, begin, mid, arr_temp);
	MergeSort(arr, mid + 1, end, arr_temp);

	// 归
	int count = 0;

	int pLeftSeq_ = begin;  // 左边序列的下标
	int pRightSeq_ = mid + 1;  // 右边序列的下标，都先指向第一个

	//int* arr_temp = new int[number];   // 开辟一个新的空间

	while (pLeftSeq_ <= mid && pRightSeq_ <= end) {  // 比较两个区间指向的元素，哪个小就放入哪个
		if (arr[pLeftSeq_] <= arr[pRightSeq_]) {
			arr_temp[count++] = arr[pLeftSeq_++];
		}
		else {
			arr_temp[count++] = arr[pRightSeq_++];
		}
	}
	if (pLeftSeq_ > mid) {  // 当其中一个序列的所有元素放入后，就把另一个剩下的不需要比较全部放入
		while (count < number) {
			arr_temp[count++] = arr[pRightSeq_++];
		}
	}
	else {
		while (count < number) {
			arr_temp[count++] = arr[pLeftSeq_++];
		}
	}

	for (int i = begin; i <= end; i++) {  // 把合并后的序列写到原来的数组中
		arr[i] = arr_temp[i - begin];
	}

	arr_temp = nullptr;

	// 平均(最好)时间复杂度：O(nlogn)
	// 最差时间复杂度：O(nlogn) [都是比较完美的二叉树]

	// 空间复杂度：O(n) [递归的深度——影响栈的空间]
	// 稳定
}


// 堆排序
void HeapSort(int arr[], int size) {
	/*
		一个小根堆，一个一个push，然后一个一个pop?
	*/
	MinHeap mh;
	for (int i = 0; i < size; i++) {
		mh.push(arr[i]);
	}
	for (int i = 0; i < size; i++) {
		arr[i] = mh.pop();
	}
	// 平均(最好)时间复杂度：O(nlogn)
	// 空间复杂度：O(1)  [可以直接操作arr，而不用创建一个大根堆或小根堆]
	// 不稳定
}