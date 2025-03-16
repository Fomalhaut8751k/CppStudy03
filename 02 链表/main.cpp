#include<iostream>

#include "Clink.hpp"
#include "CircleLink.hpp"
#include "DoubleLink.hpp"
#include "DoubleCircleLink.hpp"

using namespace std;

int main() {

#if 0  // 普通链表
	Clink c;

	cout << "尾插法" << endl;
	for (int i = 0; i < 10; i++) {
		c.insertTail(i);  // 尾插
		c.forEach();
	}
	cout << "尾删法" << endl;
	for (int i = 0; i < 5; i++) {
		c.deleteTail();  // 尾删
		c.forEach();
	}
	cout << "头插法" << endl;
	for (int i = 0; i < 5; i++) {
		c.insertHead(i + 5);  // 头插
		c.forEach();
	}
	cout << "头删法" << endl;
	for (int i = 0; i < 3; i++) {
		c.deleteHead();  // 头删
		c.forEach();
	}
	cout << "按值删除，删一个0，然后删一个4" << endl;
	c.remove(0);  // 按值删
	c.forEach();

	c.remove(4);
	c.forEach();

	cout << "尾插法" << endl;
	for (int i = 0; i < 10; i++) {
		c.insertTail(i % 2 + 2);
	}
	c.forEach();

	cout << "删除所有的3" << endl;
	c.removeAll(3);
	c.forEach();

	c.insertTail(9);
	c.forEach();
	cout << "是否存在元素9:" << c.find(9) << endl << endl;

	cout << "逆序" << endl;
	c.reverse();
	c.forEach();
	cout << "逆序2.0版本" << endl;
	c.reverse2_0();
	c.forEach();
	cout << "逆序3.0版本" << endl;
	c.reverse3_0();
	c.forEach();

	cout << "\n";
	for (int i = 0; i < 13; i++) {
		cout << "倒数第" << i << "个元素: ";  c.backward(i);
	}

	// 两个有序链表合并
	cout << "\n合并两个有序链表(从小到大)" << endl;
	Clink c1;
	c1.insertTail(9); c1.insertTail(25); c1.insertTail(37); c1.insertTail(520); c1.insertTail(780);
	cout << "主链表为: ";  c1.forEach();
	Clink c2;
	c2.insertTail(13); c2.insertTail(23); c2.insertTail(40); c2.insertTail(100); c2.insertTail(503);
	cout << "副链表为: ";  c2.forEach();
	// c1.combineOrder(c2);
	c1.reverse();
	c2.reverse2_0();
	c1.combineOrder2_0(c2);
	cout << "倒序后合并后的主链表为: ";  c1.forEach();

	cout << "\n判断是否存在环: "; c1.findCycle();
	cout << "以第8个结点为入口生成环" << endl;
	c1.createCycle(8);
	cout << "判断是否存在环: "; c1.findCycle();


	Clink c3;
	int arr_c3[4] = { 3,5,1,9 };
	for (int i = 0; i < 4; i++) {
		c3.insertTail(arr_c3[i]);
	}
	cout << "\nc3链表为: "; c3.forEach();
	Clink c4;
	c4.insertTail(4);
	c4.insertTail(23);

	Node n1(12); // 有参构造
	c3.insertTail(n1);
	c3.insertTail(15);
	cout << "c4链表为: "; c3.forEach();

	cout << "c4链表为: "; c4.forEach();
	// 因为一开始创建n1时地址为nullptr，但是后面插了节点就因此改变了
	c3.ifIntersect(c4);
	// 在这里给n1附上c3中对应的next
	//n1.n_Next = c3.find2_0(12)->n_Next;  
	c4.insertTail(n1);  // 值传递的形式

	// 如果不使用引用，由于触发了拷贝构造函数,这两个值为12的的结点是不一样的(地址不同)
	Node* n1_ = c3.find2_0(12);  Node* n2_ = c4.find2_0(12);

	cout << "c3插入的结点: " << n1_ << "\t下一个节点的地址：" << n1_->n_Next << endl;
	cout << "c4插入的结点: " << n2_ << "\t下一个节点的地址：" << n2_->n_Next << endl;

	cout << "c4链表为: "; c4.forEach();
	c3.ifIntersect(c4);
#endif

#if 1  // 单向循环链表
	//CircleLink1_0 uc1;
	//uc1.insertTail(2);
	//uc1.insertTail(4);
	//uc1.insertTail(5);
	//uc1.forEach(1);

	CircleLink2_0 c1;
	for (int i = 0; i < 5; i++) {
		c1.insertTail(i + 1);
		c1.forEach(false);
	}
	for (int i = 0; i < 5; i++) {
		c1.insertHead(i + 6);
		c1.forEach(false);
	}

	c1.remove(1);
	c1.forEach(false);

	c1.remove(5);
	c1.forEach(false);

	c1.insertHead(3); c1.insertHead(3); c1.insertTail(3); c1.insertTail(3);
	c1.forEach(false);

	c1.remove(3, false);
	c1.forEach();

	//c1.forEach(true);  // 用来检查链表循环有没有问题

	//cout << "c1中是否有5003: " << c1.find(5003) << endl;
	//cout << "c1中是否有5: " << c1.find(4) << endl;

	// 约瑟夫环
	/*
		n个人(以编号1,2,3,4.....) 围坐于一圆桌，从编号为k的人开始报数，数到m的人滚蛋，然后下一个人
		从1继续开始，如此一个个滚蛋，直到所有人都滚了，求出列顺序
	*/
	CircleLink2_0 c;
	for (int i = 1; i <= 20; i++) {
		c.insertTail(i);
	}
	c.Josephus();
#endif

#if 0 // 双向链表
	DoubleLink d;
	for (int i = 1; i < 6; i++) {
		d.insertTail(i);
		d.forEach();
	}

	d.remove(1);
	d.forEach();
	d.remove(5);
	d.forEach();

	d.insertHead(3);
	d.forEach();
	d.remove(3, false);
	d.forEach();

	d.find(2);

#endif

#if 0  // 双向循环链表
	DoubleCircleLink dc;
	for (int i = 0; i < 7; i++) {
		dc.insertHead(i);
		dc.forEach();
	}
	for (int i = 0; i < 5; i++) {
		dc.InsertTail(i + 3);
		dc.forEach();
	}
	dc.remove(3);
	dc.forEach();
	dc.remove(6, false);
	dc.forEach();
	dc.remove(7);
	dc.forEach();
	cout << "是否存在3: " << dc.find(3) << endl;

#endif

	system("pause");
	return 0;
}