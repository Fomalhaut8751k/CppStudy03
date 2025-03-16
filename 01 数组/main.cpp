#include<iostream>
#include "Array.hpp"
#include<string.h>
#include<vector>

using namespace std;

/*
	���ݽṹ���໥֮�����һ�ֻ��߶����ض���ϵ������Ԫ�صļ��ϡ����߼��Ͽ��Է�Ϊ���Խṹ��ɢ�нṹ�����νṹ��ͼ�νṹ��
	�㷨������������Ĳ��������������ϱ��ֳ����ǽ���ض������һ�����޵�ָ������
	�㷨���Ӷȣ�ʱ��Ϳռ临�Ӷȣ������㷨Ч�ʣ��㷨��ִ�й����У��������ݹ�ģn���������㷨ִ�������ѵ�ʱ��Ϳռ�������ٶ�

	������ʱ�临�Ӷȣ�
	O(1)		����������ʣ���ϣ��
	O(logn)		��������������ѵ�����AVL�����������
	O(n)		��������
	O(nlogn)	�����У��������򣬹鲢����
	O(n**2)		ð������ѡ�����򣬲�������
	O(2**n)		�Ӽ���
	O(n!))		������
*/

// 1. �����ַ�����˫ָ��˼�룩
/*Ҫ���ޣ�˼·����*/
void Reverse(char arr[], int size) {
	char* head = arr; // ��
	char* tail = arr + size - 1;  // β
	while (head < tail) {  // �� head = tail��head > tail�ǲ���Ҫ������
		char ch = *head;
		*head = *tail;
		*tail = ch;

		head++;
		tail--;
	}
}

// 2. ��ż��������˫ָ��˼�룩
/*
	Ҫ�󣺰������ĵ�������ߣ���ż���ĵ������ұ�
	˼·������ָ�룬ͷ��β
		  1309285�������߼У�ֱ��
		  ͷ���棬β��ż��������������
		  1309285 -> 8309215
		  *    *
		  8309215 -> 8209315
		   *  *
*/
void OddEvenAdjustment(int arr[], int size) {
	int* head = arr;
	int* tail = arr + size - 1;
	while (head < tail) {
		if (*head % 2 == 0) {  // ͷ��ż���
			head++;
		}
		if (*tail % 2 == 1) {  // β�������
			tail--;
		}
		if ((*head % 2 == 1) && (*tail % 2 == 0)) {  // ͷ���棬β��ż������
			int i = *head;
			*head = *tail;
			*tail = i;
		}
	}
}


int main() {
	// ���Ա�

	/*
	 1. ���飺�ڴ���������
			�ŵ㣺�±���ʣ�������ʣ���β��βɾʱ�临�Ӷ�O(1)������Ԫ��ǰ������Ԫ�غܷ���
			ȱ�㣺��β��βɾ��Ҫ�����������ƶ���
				  ������ʱ�临�Ӷȣ��������飺O(n)
									�������飺O(logn)
				  �����������ıȽϴ�
	*/
	Array arr1(4);  // ����Ϊ4
	for (int i = 0; i < 5; i++) {
		arr1.push_back(i + 1);  // ����4��ʱ����Զ�����
		arr1.forEach();
		cout << "arr1������Ϊ��" << arr1.returnCapacity() << "\tarr1�Ĵ�СΪ��" << arr1.returnSize() << endl;
	}
	arr1.insert(3, 9); // ������Ϊ3�ĵط�����
	arr1.forEach();

	arr1.erase(2);  // ��Ԫ��2ɾ��
	arr1.forEach();
	cout << "��ɾ����β��Ԫ��:" << arr1.pop_back() << endl;  // ɾ�����Ԫ�ز�����
	arr1.forEach();

	cout << "Ԫ��10������λ�ã�" << arr1.find(10) << endl;
	cout << "Ԫ��3������λ�ã�" << arr1.find(3) << endl;

	Array arr2(arr1);  // ��������
	arr2.forEach();

	arr2.insert(4, 5003);
	arr2.forEach();

	// -------------------���������˫ָ��Ӧ��-------------------------------
	// 1. �����ַ���
	char ch[] = "Cristiano Ronaldo Dos Santos Aveiro";
	//int len_ch =  sizeof(ch) / sizeof(ch[0]);  // 35
	Reverse(ch, strlen(ch));
	cout << ch << endl;

	// 2.��ż������
	int arr3[] = { 1,9,4,7,2,0,3,6,8 };
	int len_arr3 = sizeof(arr3) / sizeof(arr3[0]);
	OddEvenAdjustment(arr3, len_arr3);
	for (auto item : arr3) {
		cout << item << " ";
	}cout << endl;

	// 3.���ۡ�27.�Ƴ�Ԫ�ء�
	vector<int> v = { 1,2,3,4,5,6 };
	vector<int>* tail = &v;
	tail++;
	tail++;
	tail++;
	cout << tail - &v << endl;
	system("pause");
	return 0;
}
