#pragma once
#include<iostream>

using namespace std;

/*----��������----*/

// ֻ�ܴ�����������
// ������(BST)���Ӹ��ڵ㿪ʼ����....
// ���Ĳ�������ӳ�˵�ʱ�临�Ӷ�O(logn)
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

// �ݹ�汾
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