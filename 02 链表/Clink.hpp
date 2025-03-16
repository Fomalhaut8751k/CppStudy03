#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

// 链表：每一个结点都是在堆区内存上独立new出来的，节点内存不连续
/*
	优点：内存利用率高，不需要大块连续的内存
		  插入和删除节点不需要移动其他节点，时间复杂度为O(1)
		  不需要专门的扩容操作
	缺点：内存占用量大，每一个结点多出存放地址的空间
		  节点内存不连续，无法进行内存的随机访问
		  链表搜索效率不高，只能从头节点开始逐节点遍历
*/

// 单链表实现
class Clink {
public:
	Clink() {
		this->head = new Node();
	};
	// 尾插法
	void insertTail(int val) {
		// 遍历到结点的next是nullptr，就是最后一个结点
		Node* node = this->head;
		while (node->n_Next != nullptr) {  // 如果不是尾结点
			node = node->n_Next;  // 指针就指向下一个节点，
		}
		//tail->n_Next = new Node();
		//tail->n_Next->n_Data = val;
		node->n_Next = new Node(val);
	}
	// 尾插法2.0
	void insertTail(Node& node_) {  // 不引用会触发拷贝构造？
		/*
			拷贝构造函数的调用时机其二：值传递的方式给函数参数传值
		*/
		// 遍历到结点的next是nullptr，就是最后一个结点
		Node* node = this->head;
		while (node->n_Next != nullptr) {  // 如果不是尾结点
			node = node->n_Next;  // 指针就指向下一个节点，
		}
		//tail->n_Next = new Node();
		//tail->n_Next->n_Data = val;
		node->n_Next = &node_;
	}
	// 头插法
	void insertHead(int val) {
		Node* node = new Node(val);
		node->n_Next = this->head->n_Next;  // 把原本head指向的空间给到node
		this->head->n_Next = node;  // 让head指向node
	}
	// 尾删法
	void deleteTail() {
		// 得找到倒数第二个结点
		if (this->head->n_Next == nullptr) {  // 如果只有头结点，就不执行
			return;
		}
		Node* node = this->head;
		while (node->n_Next->n_Next != nullptr) {
			node = node->n_Next;
		}
		delete node->n_Next;
		node->n_Next = nullptr;
	}
	// 头删法
	void deleteHead() {
		if (this->head->n_Next == nullptr) {  // 如果只有头结点，就不执行
			return;
		}
		Node* node = this->head->n_Next;  // 待删除的结点
		this->head->n_Next = this->head->n_Next->n_Next;  // 把第一个结点的next给到头结点的next
		delete node;
	}
	// 按值删除节点法
	void remove(int val) {
		//Node* p= this->head->n_Next;
		//while(p!=nullptr){  // p表示当前节点的地址而不是使当前节点存储的下一个结点的地址
		//	/*
		//		head node1, node2, node3......node10, nullptr
		//			   *
		//	*/
		//	if (p->n_Next->n_Data == val) {
		//		

		//		break;
		//	}
		//}
		Node* node = this->head->n_Next;
		do {
			if (node->n_Next->n_Data == val) {  // 如果下一个节点是
				Node* node_delete = node->n_Next;
				node->n_Next = node->n_Next->n_Next;
				delete node_delete;
				break;
			}
			node = node->n_Next;
		} // 在最后一个结点位置，->next已经是nullptr，不会再执行了
		while (node->n_Next != nullptr);
	}
	// 按值删除所有值
	void removeAll(int val) {
		Node* node = this->head->n_Next;
		do {
			if (node->n_Next->n_Data == val) {  // 如果下一个节点是
				Node* node_delete = node->n_Next;
				node->n_Next = node->n_Next->n_Next;
				delete node_delete;
				// 此时已经删除下一个结点，如果是最后一个节点，则node->n_Next=nullptr
				if (node->n_Next == nullptr) {
					break;
				}
			}
			node = node->n_Next;
		} // 在最后一个结点位置，->next已经是nullptr，不会再执行了
		while (node->n_Next != nullptr);
	}

	//遍历
	void forEach() {
		Node* node = this->head;  // 遍历时不管头结点
		do {
			node = node->n_Next;
			cout << node->n_Data << " ";
		} while (node->n_Next != nullptr);
		cout << endl;
	}
	void forEach2_0() {
		Node* node = this->head;
		while (node++->n_Next != nullptr) {
			cout << node->n_Data << " ";
		}
		cout << endl;
	}

	// 搜索
	bool find(int val) {
		Node* node = this->head;
		while (node != nullptr) {
			if (node->n_Data == val) {
				return true;
			}
			node = node->n_Next;
		}
		return false;
	}
	Node* find2_0(int val) {
		Node* node = this->head;
		while (node != nullptr) {
			if (node->n_Data == val) {
				return node;
			}
			node = node->n_Next;
		}
		return nullptr;
	}

	// 1. 单列表逆序
	void reverse() {
		Node* p = this->head->n_Next;  // 先定位到第一个结点
		Node* first = this->head->n_Next;  // 指向第一个节点
		bool label = false;

		Node* q = p->n_Next;  // 第二个结点
		// 接下来就是，把p的地址给到q的next，然后都向后
		while (!label) {
			// 因为最后结点的next的nullptr会在下面的操作被覆盖，所以while停不下来会报错
			// 因此不能通过 q->n_Next==nullptr来让while结束
			if (q->n_Next == nullptr) {
				label = true;
			}
			// 先保存q的next
			Node* r = q->n_Next;
			q->n_Next = p;
			p = q; // p指向下一个结点即当前q的位置
			q = r; // q指向下一个结点q->n_Next
		}
		// 把第一个结点的next置为nullptr
		first->n_Next = nullptr;
		// 最后把p的地址给到了head的n_Next
		this->head->n_Next = p;
	}
	void reverse2_0() {  // 头插和尾插形成相反的链表，通过这个思路来实现
		Node* node = this->head->n_Next;  // 指向第一个节点
		this->head->n_Next = nullptr;  // 断开头结点和第一个节点，把剩下的头结点当成空链表
		while (node != nullptr) {
			this->insertHead(node->n_Data);
			Node* node_delete = node;
			node = node->n_Next;
			delete node_delete;
		}
	}
	void reverse3_0() {  // 不涉及新节点的开辟删除,以及头插函数
		Node* p = this->head->n_Next;  // 第一个结点
		this->head->n_Next = nullptr;  // 视为空链表和另一根链表
		while (p != nullptr) {
			Node* q = p->n_Next;
			p->n_Next = this->head->n_Next;  // p的next为第一个节点
			this->head->n_Next = p;  // 头结点保存p
			p = q;
		}
	}

	// 2. 单链表求倒数第k个节点
	void backward(int k) {
		// 双指针的思路，间隔为k-1个单位的两个指针一一起往后走，如果前面的到最后一个结点，那么后面就是倒数第k个
		Node* q = head->n_Next;
		Node* p = head->n_Next;
		int count = 0;  // 记录
		while (q->n_Next != nullptr) {  // 等到q到最后一个结点时，p就到倒数第k个节点
			q = q->n_Next;
			if (count < k - 1) {
				count++;
			}
			else {
				p = p->n_Next;  // 让p在q走到它前面k-1的位置是开始移动
				count++;
			}
		}
		if ((k > count + 1) || k <= 0) {  // 如果一个n个，但是k大于n就打印error
			cout << "error" << endl;
		}
		else {
			if (k == 1) {
				cout << q->n_Data << endl;
			}
			else {
				cout << p->n_Data << endl;
			}
		}
	}

	// 3. 有序链表的合并
	void combineOrder(Clink& c) {
		// 先指向两个链表的第一个结点
		Node* p = this->head;
		Node* q = c.head->n_Next;
		while (p->n_Next != nullptr) {  // 判断p的下一个结点，方便在p前面插结点
			if (p->n_Next->n_Data >= q->n_Data) {
				// 把q对应的结点插入到p的前面
				Node* p_next = p->n_Next;
				Node* q_next = q->n_Next;

				p->n_Next = q;
				q->n_Next = p_next;

				q = q_next;
			}
			else {
				// p指针往后移动，直到p->n_Data >= q->n_Data
				p = p->n_Next;
			}
		} // 结束后p在主链表的最后一个结点后面，即nullptr,可能次链表剩下的数字都比主最大的大，直接把剩下的接过去
		if (q != nullptr) {
			p->n_Next = q;
		}
		c.head = nullptr;
	}
	void combineOrder2_0(Clink& c) {  // 改成从大到小的
		// 先指向两个链表的第一个结点
		Node* p = this->head->n_Next;  // 遍历主链表
		Node* q = c.head->n_Next;  // 遍历次链表
		Node* last = this->head;   // 遍历整个

		while ((p != nullptr) && (q != nullptr)) {
			// 如果p的大于q的，则让q继续往后找，找到大于p的位置
			if (p->n_Data <= q->n_Data) {  // 把大于等于换成小于等于就是从大到小，当然原来的两个链表也要是从大到小
				last->n_Next = q;
				q = q->n_Next;
			}
			else {  // 找到大于p的后
				last->n_Next = p;  // last跟踪到p上，p上继续找到比q大的
				p = p->n_Next;
			}
			last = last->n_Next;
		}
		if (p == nullptr) {  // 如果p或q在找更大的过程中达到了终点，说明尾结点最大值也比另一个链表剩下的小
			last->n_Next = q;  // 直接把剩下的接过去
		}
		if (q == nullptr) {
			last->n_Next = p;
		}

		c.head = nullptr;
	}

	// 3.5 以第k个结点为入口生成环
	void createCycle(int k) {
		int count = 0;
		Node* node_k = nullptr;  // 记录第k个节点的地址
		Node* node = this->head;
		while (node->n_Next != nullptr) {
			node = node->n_Next;
			count++;
			if (count == k) {
				node_k = node;
			}
		}
		// 此时node抵达最后一个结点
		node->n_Next = node_k;
	}

	// 4. 判断单链表是否存在环以及入口结点
	void findCycle() {
		// 一般思路：一个哈希表存取走过的地址，如果遇到重复的就说明有环
		// 高级思路：快慢指针
		Node* fast = this->head;
		Node* slow = this->head;

		while (fast != nullptr && fast->n_Next != nullptr) {
			// 如果进入环了，那么总会有一个时刻，fast追上slow，不存在快指针直接跨过去的情况
			fast = fast->n_Next->n_Next;  // 快指针一次移动两个单位
			slow = slow->n_Next; // 慢指针一次移动一个单位
			if (fast == slow) {
				cout << "存在环" << endl;
				// 接下来找环的入口，理论得到的公式，虽然推导有点.....
				/*
					相遇后在儿子的起始位置定一个指针，相遇的位置定一个指针，同步移动到相遇，就是入口(公式理论推导得到)
				*/
				Node* first = this->head;
				while (first != slow) {
					first = first->n_Next;
					slow = slow->n_Next;
				}
				cout << "环的入口为: " << first << "\t" << first->n_Data << endl;
				return;
			}
		}
		// 如果循环结束了，说明fast到尾结点或者nullptr去了，即没有环
		cout << "不存在环" << endl;
	}

	// 5. 相交(汇聚)
	void ifIntersect(Clink& c) {
		Node* p = this->head;
		Node* q = c.head;
		int len_p = 0, len_q = 0;
		// 各自计算长度，然后计算差值，让长的那个先走差值，然后一起走就能交汇
		while (p != nullptr && len_p++ >= 0) {
			p = p->n_Next;
		}
		while (q != nullptr && len_q++ >= 0) {
			q = q->n_Next;
		}
		p = this->head; q = c.head;  // 回到起点
		int offset = 0;
		if (len_p >= len_q) {
			offset = len_p - len_q;
			while (offset-- > 0) {
				p = p->n_Next;
			}
		}
		else {
			offset = len_q - len_p;
			while (offset-- > 0) {
				q = q->n_Next;
			}
		}
		while (p != nullptr) {
			if (p == q) {
				cout << "相交，交点为: " << p << "\t" << p->n_Data << endl;
				return;
			}
			p = p->n_Next;
			q = q->n_Next;
		}
		cout << "不相交" << endl;
	}

	~Clink() {
		// 把所有的节点都删除掉
		Node* node = this->head;
		while (node->n_Next != nullptr) {  // 这种最后一个结点删不掉
			Node* p = node->n_Next;  // 先记录下一个结点
			cout << "已删除: " << node->n_Data << endl;
			delete node;  // 删除当前节点
			node = p;  // 定位到下一个节点
		}
		delete node;  // 删除最后一个结点
	}
private:
	Node* head; // 指向头结点的指针
	/*
		创建一个头结点，然后指针指向头结点，为何不直接创建一个指针指向第一个结点？
	*/
};
