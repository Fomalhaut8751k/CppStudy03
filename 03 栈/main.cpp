#include<iostream>

#include "SeqStack.hpp"
#include "LinkStack.hpp"
#include "QueueStack.hpp"

#include<stack>
#include<map>

using namespace std;

// 线性表三——栈
/*
	先进后出，后进先出（限制了增删的位置）
	顺序栈：依靠数组实现
	链式栈：依靠链表实现
*/

// 将中缀表达式转为后缀表达式(逆波兰)
// 比如(1 + 2) * (3 + 4) =》 (1 2 +)(3 4 +) *
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

	// 顺序栈
	cout << "顺序栈：" << endl;
	SeqStack s1;
	for (auto item : { 12,4,56,7,89,31,53,75 }) {
		s1.push(item);
		cout << s1.top() << " ";
	}cout << endl;

	//SeqStack s2 = s1;  // 拷贝
	//cout << s2.top() << endl;

	while (!s1.empty()) {
		cout << s1.top() << " ";
		s1.pop();
	}cout << endl;

	// 链式栈
	cout << "\n链式栈：" << endl;
	LinkStack s3;
	for (auto item : { 12,4,56,7,89,31,53,75 }) {
		s3.push(item);
		cout << s3.top() << " ";
	}cout << endl;

	/*
		逆波兰表达式
		形如((1 2 +)(3 4 +)*)
		去掉括号后表达式无歧义
		适合栈操作运算，遇到数字就入栈遇到算符则取出来两个进行计算，然后结果push进去
	*/

	cout << "\n将中缀表达式转为后缀表达式(逆波兰):" << endl;

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
	cout << "从顶上pop出了：" << ms.pop() << endl;
	ms.forEach();

	system("pause");
	return 0;
}