#include<iostream>

#include "Queue.hpp"
#include "LinkQueue.hpp"
#include "StackQueue.hpp"

using namespace std;

int main() {

	Queue q(10);
	for (int i = 0; i < 7; i++) {
		q.push(i);
		q.forEach();
		cout << "队列元素个数: " << q.size() << endl;
		cout << endl;
	}
	// 第一种情况的扩容
	//q.expand(20);
	//q.forEach();

	// 第二种情况的扩容 
	cout << "接下来边pop边push" << endl;
	for (int i = 0; i < 4; i++) {
		q.pop();
		q.push(i);
		q.forEach();
		cout << "队列元素个数: " << q.size() << endl;
		cout << endl;
	}
	q.expand(20);
	q.forEach();
	cout << "队列元素个数: " << q.size() << endl;
	cout << endl;
	q.push(10);
	cout << "队列元素个数: " << q.size() << endl;
	cout << endl;

	/*	链式队列
		1. 用双向循环链表实现：
			尾插法，头删法
			双向使得尾插法复杂度为O(1)
	*/

	LinkQueue lq;
	for (auto item : { 1,5,2,6,8,9,4 }) {
		lq.push(item);
		lq.forEach();
		cout << "队列元素个数: " << lq.size() << endl;
		cout << endl;
	}
	for (int i = 0; i < 7; i++) {
		lq.pop();
		lq.forEach();
		cout << "队列元素个数: " << lq.size() << endl;
		cout << endl;
	}

	cout << "\n两个栈合成一个队列" << endl;
	MyQueue mq;
	for (auto item : { 1,5,2,6 }) {
		mq.push(item);
		mq.foreach();
	}
	for (int i = 0; i < 2; i++) {
		cout << "pop的元素：" << mq.pop() << endl;
		mq.foreach();
	}
	cout << "队头元素: " << mq.peek() << endl;
	mq.push(9);
	mq.foreach();

	system("pause");
	return 0;
}