#include<iostream>

#include "Clink.hpp"
#include "CircleLink.hpp"
#include "DoubleLink.hpp"
#include "DoubleCircleLink.hpp"

using namespace std;

int main() {

#if 0  // ��ͨ����
	Clink c;

	cout << "β�巨" << endl;
	for (int i = 0; i < 10; i++) {
		c.insertTail(i);  // β��
		c.forEach();
	}
	cout << "βɾ��" << endl;
	for (int i = 0; i < 5; i++) {
		c.deleteTail();  // βɾ
		c.forEach();
	}
	cout << "ͷ�巨" << endl;
	for (int i = 0; i < 5; i++) {
		c.insertHead(i + 5);  // ͷ��
		c.forEach();
	}
	cout << "ͷɾ��" << endl;
	for (int i = 0; i < 3; i++) {
		c.deleteHead();  // ͷɾ
		c.forEach();
	}
	cout << "��ֵɾ����ɾһ��0��Ȼ��ɾһ��4" << endl;
	c.remove(0);  // ��ֵɾ
	c.forEach();

	c.remove(4);
	c.forEach();

	cout << "β�巨" << endl;
	for (int i = 0; i < 10; i++) {
		c.insertTail(i % 2 + 2);
	}
	c.forEach();

	cout << "ɾ�����е�3" << endl;
	c.removeAll(3);
	c.forEach();

	c.insertTail(9);
	c.forEach();
	cout << "�Ƿ����Ԫ��9:" << c.find(9) << endl << endl;

	cout << "����" << endl;
	c.reverse();
	c.forEach();
	cout << "����2.0�汾" << endl;
	c.reverse2_0();
	c.forEach();
	cout << "����3.0�汾" << endl;
	c.reverse3_0();
	c.forEach();

	cout << "\n";
	for (int i = 0; i < 13; i++) {
		cout << "������" << i << "��Ԫ��: ";  c.backward(i);
	}

	// ������������ϲ�
	cout << "\n�ϲ�������������(��С����)" << endl;
	Clink c1;
	c1.insertTail(9); c1.insertTail(25); c1.insertTail(37); c1.insertTail(520); c1.insertTail(780);
	cout << "������Ϊ: ";  c1.forEach();
	Clink c2;
	c2.insertTail(13); c2.insertTail(23); c2.insertTail(40); c2.insertTail(100); c2.insertTail(503);
	cout << "������Ϊ: ";  c2.forEach();
	// c1.combineOrder(c2);
	c1.reverse();
	c2.reverse2_0();
	c1.combineOrder2_0(c2);
	cout << "�����ϲ����������Ϊ: ";  c1.forEach();

	cout << "\n�ж��Ƿ���ڻ�: "; c1.findCycle();
	cout << "�Ե�8�����Ϊ������ɻ�" << endl;
	c1.createCycle(8);
	cout << "�ж��Ƿ���ڻ�: "; c1.findCycle();


	Clink c3;
	int arr_c3[4] = { 3,5,1,9 };
	for (int i = 0; i < 4; i++) {
		c3.insertTail(arr_c3[i]);
	}
	cout << "\nc3����Ϊ: "; c3.forEach();
	Clink c4;
	c4.insertTail(4);
	c4.insertTail(23);

	Node n1(12); // �вι���
	c3.insertTail(n1);
	c3.insertTail(15);
	cout << "c4����Ϊ: "; c3.forEach();

	cout << "c4����Ϊ: "; c4.forEach();
	// ��Ϊһ��ʼ����n1ʱ��ַΪnullptr�����Ǻ�����˽ڵ����˸ı���
	c3.ifIntersect(c4);
	// �������n1����c3�ж�Ӧ��next
	//n1.n_Next = c3.find2_0(12)->n_Next;  
	c4.insertTail(n1);  // ֵ���ݵ���ʽ

	// �����ʹ�����ã����ڴ����˿������캯��,������ֵΪ12�ĵĽ���ǲ�һ����(��ַ��ͬ)
	Node* n1_ = c3.find2_0(12);  Node* n2_ = c4.find2_0(12);

	cout << "c3����Ľ��: " << n1_ << "\t��һ���ڵ�ĵ�ַ��" << n1_->n_Next << endl;
	cout << "c4����Ľ��: " << n2_ << "\t��һ���ڵ�ĵ�ַ��" << n2_->n_Next << endl;

	cout << "c4����Ϊ: "; c4.forEach();
	c3.ifIntersect(c4);
#endif

#if 1  // ����ѭ������
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

	//c1.forEach(true);  // �����������ѭ����û������

	//cout << "c1���Ƿ���5003: " << c1.find(5003) << endl;
	//cout << "c1���Ƿ���5: " << c1.find(4) << endl;

	// Լɪ��
	/*
		n����(�Ա��1,2,3,4.....) Χ����һԲ�����ӱ��Ϊk���˿�ʼ����������m���˹�����Ȼ����һ����
		��1������ʼ�����һ����������ֱ�������˶����ˣ������˳��
	*/
	CircleLink2_0 c;
	for (int i = 1; i <= 20; i++) {
		c.insertTail(i);
	}
	c.Josephus();
#endif

#if 0 // ˫������
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

#if 0  // ˫��ѭ������
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
	cout << "�Ƿ����3: " << dc.find(3) << endl;

#endif

	system("pause");
	return 0;
}