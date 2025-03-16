#pragma once
#pragma once
#include<iostream>
#include "Node.hpp"

using namespace std;

// ����ÿһ����㶼���ڶ����ڴ��϶���new�����ģ��ڵ��ڴ治����
/*
	�ŵ㣺�ڴ������ʸߣ�����Ҫ����������ڴ�
		  �����ɾ���ڵ㲻��Ҫ�ƶ������ڵ㣬ʱ�临�Ӷ�ΪO(1)
		  ����Ҫר�ŵ����ݲ���
	ȱ�㣺�ڴ�ռ������ÿһ���������ŵ�ַ�Ŀռ�
		  �ڵ��ڴ治�������޷������ڴ���������
		  ��������Ч�ʲ��ߣ�ֻ�ܴ�ͷ�ڵ㿪ʼ��ڵ����
*/

// ������ʵ��
class Clink {
public:
	Clink() {
		this->head = new Node();
	};
	// β�巨
	void insertTail(int val) {
		// ����������next��nullptr���������һ�����
		Node* node = this->head;
		while (node->n_Next != nullptr) {  // �������β���
			node = node->n_Next;  // ָ���ָ����һ���ڵ㣬
		}
		//tail->n_Next = new Node();
		//tail->n_Next->n_Data = val;
		node->n_Next = new Node(val);
	}
	// β�巨2.0
	void insertTail(Node& node_) {  // �����ûᴥ���������죿
		/*
			�������캯���ĵ���ʱ�������ֵ���ݵķ�ʽ������������ֵ
		*/
		// ����������next��nullptr���������һ�����
		Node* node = this->head;
		while (node->n_Next != nullptr) {  // �������β���
			node = node->n_Next;  // ָ���ָ����һ���ڵ㣬
		}
		//tail->n_Next = new Node();
		//tail->n_Next->n_Data = val;
		node->n_Next = &node_;
	}
	// ͷ�巨
	void insertHead(int val) {
		Node* node = new Node(val);
		node->n_Next = this->head->n_Next;  // ��ԭ��headָ��Ŀռ����node
		this->head->n_Next = node;  // ��headָ��node
	}
	// βɾ��
	void deleteTail() {
		// ���ҵ������ڶ������
		if (this->head->n_Next == nullptr) {  // ���ֻ��ͷ��㣬�Ͳ�ִ��
			return;
		}
		Node* node = this->head;
		while (node->n_Next->n_Next != nullptr) {
			node = node->n_Next;
		}
		delete node->n_Next;
		node->n_Next = nullptr;
	}
	// ͷɾ��
	void deleteHead() {
		if (this->head->n_Next == nullptr) {  // ���ֻ��ͷ��㣬�Ͳ�ִ��
			return;
		}
		Node* node = this->head->n_Next;  // ��ɾ���Ľ��
		this->head->n_Next = this->head->n_Next->n_Next;  // �ѵ�һ������next����ͷ����next
		delete node;
	}
	// ��ֵɾ���ڵ㷨
	void remove(int val) {
		//Node* p= this->head->n_Next;
		//while(p!=nullptr){  // p��ʾ��ǰ�ڵ�ĵ�ַ������ʹ��ǰ�ڵ�洢����һ�����ĵ�ַ
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
			if (node->n_Next->n_Data == val) {  // �����һ���ڵ���
				Node* node_delete = node->n_Next;
				node->n_Next = node->n_Next->n_Next;
				delete node_delete;
				break;
			}
			node = node->n_Next;
		} // �����һ�����λ�ã�->next�Ѿ���nullptr��������ִ����
		while (node->n_Next != nullptr);
	}
	// ��ֵɾ������ֵ
	void removeAll(int val) {
		Node* node = this->head->n_Next;
		do {
			if (node->n_Next->n_Data == val) {  // �����һ���ڵ���
				Node* node_delete = node->n_Next;
				node->n_Next = node->n_Next->n_Next;
				delete node_delete;
				// ��ʱ�Ѿ�ɾ����һ����㣬��������һ���ڵ㣬��node->n_Next=nullptr
				if (node->n_Next == nullptr) {
					break;
				}
			}
			node = node->n_Next;
		} // �����һ�����λ�ã�->next�Ѿ���nullptr��������ִ����
		while (node->n_Next != nullptr);
	}

	//����
	void forEach() {
		Node* node = this->head;  // ����ʱ����ͷ���
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

	// ����
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

	// 1. ���б�����
	void reverse() {
		Node* p = this->head->n_Next;  // �ȶ�λ����һ�����
		Node* first = this->head->n_Next;  // ָ���һ���ڵ�
		bool label = false;

		Node* q = p->n_Next;  // �ڶ������
		// ���������ǣ���p�ĵ�ַ����q��next��Ȼ�����
		while (!label) {
			// ��Ϊ������next��nullptr��������Ĳ��������ǣ�����whileͣ�������ᱨ��
			// ��˲���ͨ�� q->n_Next==nullptr����while����
			if (q->n_Next == nullptr) {
				label = true;
			}
			// �ȱ���q��next
			Node* r = q->n_Next;
			q->n_Next = p;
			p = q; // pָ����һ����㼴��ǰq��λ��
			q = r; // qָ����һ�����q->n_Next
		}
		// �ѵ�һ������next��Ϊnullptr
		first->n_Next = nullptr;
		// ����p�ĵ�ַ������head��n_Next
		this->head->n_Next = p;
	}
	void reverse2_0() {  // ͷ���β���γ��෴������ͨ�����˼·��ʵ��
		Node* node = this->head->n_Next;  // ָ���һ���ڵ�
		this->head->n_Next = nullptr;  // �Ͽ�ͷ���͵�һ���ڵ㣬��ʣ�µ�ͷ��㵱�ɿ�����
		while (node != nullptr) {
			this->insertHead(node->n_Data);
			Node* node_delete = node;
			node = node->n_Next;
			delete node_delete;
		}
	}
	void reverse3_0() {  // ���漰�½ڵ�Ŀ���ɾ��,�Լ�ͷ�庯��
		Node* p = this->head->n_Next;  // ��һ�����
		this->head->n_Next = nullptr;  // ��Ϊ���������һ������
		while (p != nullptr) {
			Node* q = p->n_Next;
			p->n_Next = this->head->n_Next;  // p��nextΪ��һ���ڵ�
			this->head->n_Next = p;  // ͷ��㱣��p
			p = q;
		}
	}

	// 2. ������������k���ڵ�
	void backward(int k) {
		// ˫ָ���˼·�����Ϊk-1����λ������ָ��һһ�������ߣ����ǰ��ĵ����һ����㣬��ô������ǵ�����k��
		Node* q = head->n_Next;
		Node* p = head->n_Next;
		int count = 0;  // ��¼
		while (q->n_Next != nullptr) {  // �ȵ�q�����һ�����ʱ��p�͵�������k���ڵ�
			q = q->n_Next;
			if (count < k - 1) {
				count++;
			}
			else {
				p = p->n_Next;  // ��p��q�ߵ���ǰ��k-1��λ���ǿ�ʼ�ƶ�
				count++;
			}
		}
		if ((k > count + 1) || k <= 0) {  // ���һ��n��������k����n�ʹ�ӡerror
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

	// 3. ��������ĺϲ�
	void combineOrder(Clink& c) {
		// ��ָ����������ĵ�һ�����
		Node* p = this->head;
		Node* q = c.head->n_Next;
		while (p->n_Next != nullptr) {  // �ж�p����һ����㣬������pǰ�����
			if (p->n_Next->n_Data >= q->n_Data) {
				// ��q��Ӧ�Ľ����뵽p��ǰ��
				Node* p_next = p->n_Next;
				Node* q_next = q->n_Next;

				p->n_Next = q;
				q->n_Next = p_next;

				q = q_next;
			}
			else {
				// pָ�������ƶ���ֱ��p->n_Data >= q->n_Data
				p = p->n_Next;
			}
		} // ������p������������һ�������棬��nullptr,���ܴ�����ʣ�µ����ֶ��������Ĵ�ֱ�Ӱ�ʣ�µĽӹ�ȥ
		if (q != nullptr) {
			p->n_Next = q;
		}
		c.head = nullptr;
	}
	void combineOrder2_0(Clink& c) {  // �ĳɴӴ�С��
		// ��ָ����������ĵ�һ�����
		Node* p = this->head->n_Next;  // ����������
		Node* q = c.head->n_Next;  // ����������
		Node* last = this->head;   // ��������

		while ((p != nullptr) && (q != nullptr)) {
			// ���p�Ĵ���q�ģ�����q���������ң��ҵ�����p��λ��
			if (p->n_Data <= q->n_Data) {  // �Ѵ��ڵ��ڻ���С�ڵ��ھ��ǴӴ�С����Ȼԭ������������ҲҪ�ǴӴ�С
				last->n_Next = q;
				q = q->n_Next;
			}
			else {  // �ҵ�����p�ĺ�
				last->n_Next = p;  // last���ٵ�p�ϣ�p�ϼ����ҵ���q���
				p = p->n_Next;
			}
			last = last->n_Next;
		}
		if (p == nullptr) {  // ���p��q���Ҹ���Ĺ����дﵽ���յ㣬˵��β������ֵҲ����һ������ʣ�µ�С
			last->n_Next = q;  // ֱ�Ӱ�ʣ�µĽӹ�ȥ
		}
		if (q == nullptr) {
			last->n_Next = p;
		}

		c.head = nullptr;
	}

	// 3.5 �Ե�k�����Ϊ������ɻ�
	void createCycle(int k) {
		int count = 0;
		Node* node_k = nullptr;  // ��¼��k���ڵ�ĵ�ַ
		Node* node = this->head;
		while (node->n_Next != nullptr) {
			node = node->n_Next;
			count++;
			if (count == k) {
				node_k = node;
			}
		}
		// ��ʱnode�ִ����һ�����
		node->n_Next = node_k;
	}

	// 4. �жϵ������Ƿ���ڻ��Լ���ڽ��
	void findCycle() {
		// һ��˼·��һ����ϣ���ȡ�߹��ĵ�ַ����������ظ��ľ�˵���л�
		// �߼�˼·������ָ��
		Node* fast = this->head;
		Node* slow = this->head;

		while (fast != nullptr && fast->n_Next != nullptr) {
			// ������뻷�ˣ���ô�ܻ���һ��ʱ�̣�fast׷��slow�������ڿ�ָ��ֱ�ӿ��ȥ�����
			fast = fast->n_Next->n_Next;  // ��ָ��һ���ƶ�������λ
			slow = slow->n_Next; // ��ָ��һ���ƶ�һ����λ
			if (fast == slow) {
				cout << "���ڻ�" << endl;
				// �������һ�����ڣ����۵õ��Ĺ�ʽ����Ȼ�Ƶ��е�.....
				/*
					�������ڶ��ӵ���ʼλ�ö�һ��ָ�룬������λ�ö�һ��ָ�룬ͬ���ƶ����������������(��ʽ�����Ƶ��õ�)
				*/
				Node* first = this->head;
				while (first != slow) {
					first = first->n_Next;
					slow = slow->n_Next;
				}
				cout << "�������Ϊ: " << first << "\t" << first->n_Data << endl;
				return;
			}
		}
		// ���ѭ�������ˣ�˵��fast��β������nullptrȥ�ˣ���û�л�
		cout << "�����ڻ�" << endl;
	}

	// 5. �ཻ(���)
	void ifIntersect(Clink& c) {
		Node* p = this->head;
		Node* q = c.head;
		int len_p = 0, len_q = 0;
		// ���Լ��㳤�ȣ�Ȼ������ֵ���ó����Ǹ����߲�ֵ��Ȼ��һ���߾��ܽ���
		while (p != nullptr && len_p++ >= 0) {
			p = p->n_Next;
		}
		while (q != nullptr && len_q++ >= 0) {
			q = q->n_Next;
		}
		p = this->head; q = c.head;  // �ص����
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
				cout << "�ཻ������Ϊ: " << p << "\t" << p->n_Data << endl;
				return;
			}
			p = p->n_Next;
			q = q->n_Next;
		}
		cout << "���ཻ" << endl;
	}

	~Clink() {
		// �����еĽڵ㶼ɾ����
		Node* node = this->head;
		while (node->n_Next != nullptr) {  // �������һ�����ɾ����
			Node* p = node->n_Next;  // �ȼ�¼��һ�����
			cout << "��ɾ��: " << node->n_Data << endl;
			delete node;  // ɾ����ǰ�ڵ�
			node = p;  // ��λ����һ���ڵ�
		}
		delete node;  // ɾ�����һ�����
	}
private:
	Node* head; // ָ��ͷ����ָ��
	/*
		����һ��ͷ��㣬Ȼ��ָ��ָ��ͷ��㣬Ϊ�β�ֱ�Ӵ���һ��ָ��ָ���һ����㣿
	*/
};
