#include<iostream>
#include<time.h>

#include<map>
#include<algorithm>

#include "utils.hpp"

using namespace std;

class MyPrint {
public:
	void operator()(pair<int, int>s) {
		cout << s.first << " " << s.second << endl;
	}
};


bool cmp(const pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;			//����ֵ�Ӵ�С���� 
}

int main() {

	/*  ��������  */
#if 0  // �������
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1;
	}

	cout << "ԭ����: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

	//BubbleSort(arr, 10);

	//cout << "ð������������: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	//ChoiceSort(arr, 10);

	//cout << "ѡ������������: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	//InsertSort(arr, 0, 9);
	InsertSort(arr, 10);
	cout << "��������������: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

	//ShellSort(arr, 10);
	//cout << "ϣ������������: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

#endif

/*  �߼�����  */
#if 0  // �������
	int arr[10] = {};
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1;
	}

	cout << "ԭ����: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

	//QuickSort(arr, 0, 9);

	//cout << "��������������: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	//MergeSort(arr, 0, 9);
	//cout << "�鲢����������: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	HeapSort(arr, 10);
	cout << "������������: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

#endif

#if 0  // Ͱ�������
	srand((unsigned int)time(NULL));
	int arr[20] = {};
	for (int i = 0; i < 20; i++)
	{
		arr[i] = rand() % 100 - 40;
	}
	for (int i = 0; i < 20; i++)
	{
		cout << arr[i] << " ";
	}cout << endl;

	BarrelSort_v2(arr, 20);

	for (int i = 0; i < 20; i++)
	{
		cout << arr[i] << " ";
	}cout << endl;


#endif

#if 1  // ���ܲ���
	const int COUNT = 200000;

	int* arr_1 = new int[COUNT];
	int* arr_2 = new int[COUNT];
	int* arr_3 = new int[COUNT];
	int* arr_4 = new int[COUNT];
	int* arr_5 = new int[COUNT];
	int* arr_6 = new int[COUNT];
	int* arr_7 = new int[COUNT];
	int* arr_8 = new int[COUNT];

	srand((unsigned)time(NULL));

	for (int i = 0; i < COUNT; i++) {
		int val = rand() % 100000 + 1;
		arr_1[i] = arr_2[i] = arr_3[i] = arr_4[i] = arr_5[i] = arr_6[i] = arr_7[i] = arr_8[i]= val;
	}

	clock_t begin, end;
	begin = clock();
	BubbleSort(arr_1, COUNT);
	end = clock();
	cout << "ð�������ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ChoiceSort(arr_2, COUNT);
	end = clock();
	cout << "ѡ�������ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	InsertSort(arr_3, COUNT);
	end = clock();
	cout << "���������ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ShellSort(arr_4, COUNT);
	end = clock();
	cout << "ϣ�������ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	QuickSort(arr_5, 0, COUNT - 1);
	end = clock();
	cout << "���������ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	int* arr = new int[COUNT];  // Ƶ���ڶ������ٺ��ͷŻ��ж����ʱ������
	MergeSort(arr_6, 0, COUNT - 1, arr);
	end = clock();
	cout << "�鲢�����ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	HeapSort(arr_7, COUNT);
	end = clock();
	cout << "�������ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	BarrelSort(arr_8, COUNT);
	end = clock();
	cout << "Ͱ�����ʱ: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	// ϣ�� > ���� > ѡ�� > ð��

	delete[] arr_1;
	delete[] arr_2;
	delete[] arr_3;
	delete[] arr_4;
	delete[] arr_5;
	delete[] arr_6;
	delete[] arr_7;

	arr_1 = nullptr;
	arr_2 = nullptr;
	arr_3 = nullptr;
	arr_4 = nullptr;
	arr_5 = nullptr;
	arr_6 = nullptr;
	arr_7 = nullptr;

#endif
	system("pause");
	return 0;
	
	/*
		1. �����ǿ��ţ����߹鲢���򣬱���Ԫ�ص�ʱ���ǰ���˳������ģ���cpu����ʱ�Ѻõ�
		   (CPU���������ʸ�)�����Ƕ����򣬷���Ԫ�ص�ʱ���ǰ��ո��ӽڵ�Ĺ�ϵ���ʵģ���
		   ���ǰ���˳����ʵġ�������������У������ǽ���Ԫ���ϸ����������³���������cpu
		   ���治�Ѻá�
		2. ������Ĺ����У�����Ԫ���³�������������Ч�����Ƚ϶ࣨ�������Ѵ��ϵ����ǴӴ�
		   ��С�����ǳ���ʱȴ�ѡ��С��ֵ���ڶѶ�Ȼ���³��������¶���������ڿ��ź͹鲢
		   Ҫ�������ʱ�䡣
		3. STL�е�sort�㷨ʹ�õ��ǣ���������(�Ż�,�ò�������Ͷ�����)
	*/

}