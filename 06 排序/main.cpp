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
	return a.second > b.second;			//按照值从大到小排序 
}

int main() {

	/*  基础排序  */
#if 0  // 输出测试
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1;
	}

	cout << "原数组: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

	//BubbleSort(arr, 10);

	//cout << "冒泡排序后的数组: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	//ChoiceSort(arr, 10);

	//cout << "选择排序后的数组: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	//InsertSort(arr, 0, 9);
	InsertSort(arr, 10);
	cout << "插入排序后的数组: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

	//ShellSort(arr, 10);
	//cout << "希尔排序后的数组: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

#endif

/*  高级排序  */
#if 0  // 输出测试
	int arr[10] = {};
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1;
	}

	cout << "原数组: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

	//QuickSort(arr, 0, 9);

	//cout << "快速排序后的数组: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	//MergeSort(arr, 0, 9);
	//cout << "归并排序后的数组: \n";
	//for (int v : arr) {
	//	cout << v << " ";
	//}cout << endl;

	HeapSort(arr, 10);
	cout << "堆排序后的数组: \n";
	for (int v : arr) {
		cout << v << " ";
	}cout << endl;

#endif

#if 0  // 桶排序测试
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

#if 1  // 性能测试
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
	cout << "冒泡排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ChoiceSort(arr_2, COUNT);
	end = clock();
	cout << "选择排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	InsertSort(arr_3, COUNT);
	end = clock();
	cout << "插入排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ShellSort(arr_4, COUNT);
	end = clock();
	cout << "希尔排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	QuickSort(arr_5, 0, COUNT - 1);
	end = clock();
	cout << "快速排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	int* arr = new int[COUNT];  // 频繁在堆区开辟和释放会有额外的时间消耗
	MergeSort(arr_6, 0, COUNT - 1, arr);
	end = clock();
	cout << "归并排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	HeapSort(arr_7, COUNT);
	end = clock();
	cout << "堆排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	BarrelSort(arr_8, COUNT);
	end = clock();
	cout << "桶排序耗时: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	// 希尔 > 插入 > 选择 > 冒泡

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
		1. 不管是快排，或者归并排序，遍历元素的时候都是按照顺序遍历的，对cpu缓存时友好的
		   (CPU缓存命中率高)，但是堆排序，访问元素的时候，是按照父子节点的关系访问的，并
		   不是按照顺序访问的。所以排序过程中，不管是进行元素上浮调整还是下沉调整，对cpu
		   缓存不友好。
		2. 堆排序的过程中，进行元素下沉调整所做的无效操作比较多（比如大根堆从上到下是从大
		   到小，但是出堆时却把“最”小的值放在堆顶然后下沉），导致堆排序相较于快排和归并
		   要花更多的时间。
		3. STL中的sort算法使用的是：快速排序(优化,用插入排序和堆排序)
	*/

}