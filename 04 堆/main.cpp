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
		cout << "����Ԫ�ظ���: " << q.size() << endl;
		cout << endl;
	}
	// ��һ�����������
	//q.expand(20);
	//q.forEach();

	// �ڶ������������ 
	cout << "��������pop��push" << endl;
	for (int i = 0; i < 4; i++) {
		q.pop();
		q.push(i);
		q.forEach();
		cout << "����Ԫ�ظ���: " << q.size() << endl;
		cout << endl;
	}
	q.expand(20);
	q.forEach();
	cout << "����Ԫ�ظ���: " << q.size() << endl;
	cout << endl;
	q.push(10);
	cout << "����Ԫ�ظ���: " << q.size() << endl;
	cout << endl;

	/*	��ʽ����
		1. ��˫��ѭ������ʵ�֣�
			β�巨��ͷɾ��
			˫��ʹ��β�巨���Ӷ�ΪO(1)
	*/

	LinkQueue lq;
	for (auto item : { 1,5,2,6,8,9,4 }) {
		lq.push(item);
		lq.forEach();
		cout << "����Ԫ�ظ���: " << lq.size() << endl;
		cout << endl;
	}
	for (int i = 0; i < 7; i++) {
		lq.pop();
		lq.forEach();
		cout << "����Ԫ�ظ���: " << lq.size() << endl;
		cout << endl;
	}

	cout << "\n����ջ�ϳ�һ������" << endl;
	MyQueue mq;
	for (auto item : { 1,5,2,6 }) {
		mq.push(item);
		mq.foreach();
	}
	for (int i = 0; i < 2; i++) {
		cout << "pop��Ԫ�أ�" << mq.pop() << endl;
		mq.foreach();
	}
	cout << "��ͷԪ��: " << mq.peek() << endl;
	mq.push(9);
	mq.foreach();

	system("pause");
	return 0;
}