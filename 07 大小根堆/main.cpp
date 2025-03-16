#include<iostream>

#include "BinaryTree.hpp"

using namespace std;



int main() {

	MaxHeap maxh;
	MinHeap minh;

	srand((unsigned)time(NULL));

	for (int i = 0; i < 16; i++) {
		int val = rand() % 100;
		cout << "����ѣ�" << endl;
		maxh.push(val);
		maxh.forEach();
		cout << "С���ѣ�" << endl;
		minh.push(val);
		minh.forEach();
	}
	for (int i = 0; i < 16; i++) {
		cout << "����ѣ�" << endl;
		maxh.pop();
		maxh.forEach();
		cout << "С���ѣ�" << endl;
		minh.pop();
		minh.forEach();
	}

	system("pause");
	return 0;
}