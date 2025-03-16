#include<iostream>
#include "Array.hpp"
#include<string.h>
#include<vector>

using namespace std;

/*
	数据结构：相互之间存在一种或者多种特定关系的数据元素的集合。在逻辑上可以分为线性结构，散列结构，树形结构，图形结构等
	算法：求解具体问题的步骤描述，代码上表现出来是解决特定问题的一组有限的指令序列
	算法复杂度：时间和空间复杂度，衡量算法效率，算法在执行过程中，随着数据规模n的增长，算法执行所花费的时间和空间的增长速度

	常见的时间复杂度：
	O(1)		数组随机访问，哈希表
	O(logn)		二分搜索，二叉堆调整，AVL，红黑树查找
	O(n)		线性搜索
	O(nlogn)	堆排列，快速排序，归并排序
	O(n**2)		冒泡排序，选择排序，插入排序
	O(2**n)		子集数
	O(n!))		排列数
*/

// 1. 逆序字符串（双指针思想）
/*要求：无，思路：无*/
void Reverse(char arr[], int size) {
	char* head = arr; // 首
	char* tail = arr + size - 1;  // 尾
	while (head < tail) {  // 当 head = tail和head > tail是不需要交换了
		char ch = *head;
		*head = *tail;
		*tail = ch;

		head++;
		tail--;
	}
}

// 2. 奇偶数调整（双指针思想）
/*
	要求：把奇数的调整到左边，把偶数的调整到右边
	思路：两个指针，头和尾
		  1309285，往两边夹，直到
		  头是奇，尾是偶，交换，继续夹
		  1309285 -> 8309215
		  *    *
		  8309215 -> 8209315
		   *  *
*/
void OddEvenAdjustment(int arr[], int size) {
	int* head = arr;
	int* tail = arr + size - 1;
	while (head < tail) {
		if (*head % 2 == 0) {  // 头是偶则加
			head++;
		}
		if (*tail % 2 == 1) {  // 尾是奇则减
			tail--;
		}
		if ((*head % 2 == 1) && (*tail % 2 == 0)) {  // 头是奇，尾是偶，交换
			int i = *head;
			*head = *tail;
			*tail = i;
		}
	}
}


int main() {
	// 线性表

	/*
	 1. 数组：内存是连续的
			优点：下标访问（随机访问），尾插尾删时间复杂度O(1)。访问元素前后相邻元素很方便
			缺点：非尾插尾删需要大量的数据移动，
				  搜索的时间复杂度：无序数组：O(n)
									有序数组：O(logn)
				  数组扩容消耗比较大
	*/
	Array arr1(4);  // 长度为4
	for (int i = 0; i < 5; i++) {
		arr1.push_back(i + 1);  // 插入4的时候会自动扩容
		arr1.forEach();
		cout << "arr1的容量为：" << arr1.returnCapacity() << "\tarr1的大小为：" << arr1.returnSize() << endl;
	}
	arr1.insert(3, 9); // 在索引为3的地方插入
	arr1.forEach();

	arr1.erase(2);  // 把元素2删掉
	arr1.forEach();
	cout << "被删除的尾部元素:" << arr1.pop_back() << endl;  // 删掉最后元素并返回
	arr1.forEach();

	cout << "元素10的索引位置：" << arr1.find(10) << endl;
	cout << "元素3的索引位置：" << arr1.find(3) << endl;

	Array arr2(arr1);  // 拷贝构造
	arr2.forEach();

	arr2.insert(4, 5003);
	arr2.forEach();

	// -------------------基于数组的双指针应用-------------------------------
	// 1. 逆序字符串
	char ch[] = "Cristiano Ronaldo Dos Santos Aveiro";
	//int len_ch =  sizeof(ch) / sizeof(ch[0]);  // 35
	Reverse(ch, strlen(ch));
	cout << ch << endl;

	// 2.奇偶数调整
	int arr3[] = { 1,9,4,7,2,0,3,6,8 };
	int len_arr3 = sizeof(arr3) / sizeof(arr3[0]);
	OddEvenAdjustment(arr3, len_arr3);
	for (auto item : arr3) {
		cout << item << " ";
	}cout << endl;

	// 3.力扣【27.移除元素】
	vector<int> v = { 1,2,3,4,5,6 };
	vector<int>* tail = &v;
	tail++;
	tail++;
	tail++;
	cout << tail - &v << endl;
	system("pause");
	return 0;
}
