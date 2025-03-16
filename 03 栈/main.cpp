#include<iostream>

#include "SeqStack.hpp"
#include "LinkStack.hpp"
#include "QueueStack.hpp"

#include<stack>
#include<map>

using namespace std;

// ���Ա�������ջ
/*
	�Ƚ����������ȳ�����������ɾ��λ�ã�
	˳��ջ����������ʵ��
	��ʽջ����������ʵ��
*/

// ����׺���ʽתΪ��׺���ʽ(�沨��)
// ����(1 + 2) * (3 + 4) =�� (1 2 +)(3 4 +) *
void MiddleToEndExpr(string expr) {

	multimap<char, int> priority = {
		{')', 4}, {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}
	};

	stack<char> s;
	for (char c : expr) {
		if (c >= '0' && c <= '9') {
			cout << c;
		}
		else {
			if (s.empty() || c == '(') {
				s.push(c);
			}
			else {
				char top_element = s.top();
				if (priority.find(c)->second == 4) {
					while (top_element != '(') {
						cout << top_element;
						s.pop();
						top_element = s.top();
					}
					s.pop();
					continue;
				}
				while (!s.empty() &&
					(priority.find(c)->second <= priority.find(top_element)->second)) {
					cout << top_element;
					s.pop();
					if (!s.empty()) {
						top_element = s.top();
					}
				}
				s.push(c);
			}
		}
	}
	while (!s.empty()) {
		cout << s.top();
		s.pop();
	}
	cout << endl;
}


int main() {

	// ˳��ջ
	cout << "˳��ջ��" << endl;
	SeqStack s1;
	for (auto item : { 12,4,56,7,89,31,53,75 }) {
		s1.push(item);
		cout << s1.top() << " ";
	}cout << endl;

	//SeqStack s2 = s1;  // ����
	//cout << s2.top() << endl;

	while (!s1.empty()) {
		cout << s1.top() << " ";
		s1.pop();
	}cout << endl;

	// ��ʽջ
	cout << "\n��ʽջ��" << endl;
	LinkStack s3;
	for (auto item : { 12,4,56,7,89,31,53,75 }) {
		s3.push(item);
		cout << s3.top() << " ";
	}cout << endl;

	/*
		�沨�����ʽ
		����((1 2 +)(3 4 +)*)
		ȥ�����ź���ʽ������
		�ʺ�ջ�������㣬�������־���ջ���������ȡ�����������м��㣬Ȼ����push��ȥ
	*/

	cout << "\n����׺���ʽתΪ��׺���ʽ(�沨��):" << endl;

	string infix_expression = "(1+2)*(3+4)";
	cout << infix_expression << " => ";
	MiddleToEndExpr(infix_expression);

	infix_expression = "2+(4+6)/2+6/3";
	cout << infix_expression << " => ";
	MiddleToEndExpr(infix_expression);

	infix_expression = "2+6/(4-2)+(4+6)/2";
	cout << infix_expression << " => ";
	MiddleToEndExpr(infix_expression);


	MyStack ms;
	for (auto item : { 1,4,2,8 }) {
		ms.push(item);
		ms.forEach();
	}
	cout << "�Ӷ���pop���ˣ�" << ms.pop() << endl;
	ms.forEach();

	system("pause");
	return 0;
}