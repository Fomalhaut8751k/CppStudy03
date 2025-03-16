#include<iostream>

#include "BinaryTree.hpp"

using namespace std;



int main() {

	MaxHeap maxh;
	MinHeap minh;

	srand((unsigned)time(NULL));

	for (int i = 0; i < 16; i++) {
		int val = rand() % 100;
		cout << "大根堆：" << endl;
		maxh.push(val);
		maxh.forEach();
		cout << "小根堆：" << endl;
		minh.push(val);
		minh.forEach();
	}
	for (int i = 0; i < 16; i++) {
		cout << "大根堆：" << endl;
		maxh.pop();
		maxh.forEach();
		cout << "小根堆：" << endl;
		minh.pop();
		minh.forEach();
	}

	system("pause");
	return 0;
}