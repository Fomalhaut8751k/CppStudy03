#pragma once
#include<iostream>

using namespace std;

/*----二分搜索----*/

// 只能处理有序序列
// 二叉树(BST)，从根节点开始搜索....
// 树的层数，反映了的时间复杂度O(logn)
int BinarySearch(int arr[], int size, int val) {
	int first = 0, middle = 0, last = size - 1;
	while (first <= last) {
		middle = (first + last) / 2;
		cout << "first: " << first << "    " << "middle: " << middle << "    " << "last: " << last << endl;
		if (arr[middle] == val) {
			return middle;
		}
		else if (arr[middle] < val) {
			first = middle + 1;
		}
		else {  // arr[middle] > val;
			last = middle - 1;
		}
	}
	return -1;
}

// 递归版本
int BinarySearch(int arr[], int first, int last, int val) {
	if (first > last) {
		return -1;
	}
	int middle = (first + last) / 2;
	if (arr[middle] == val) {
		return middle;
	}
	else if (arr[middle] > val) {
		return BinarySearch(arr, first, middle - 1, val);
	}
	else {  // arr[middle] > val
		return BinarySearch(arr, middle + 1, last, val);
	}
}