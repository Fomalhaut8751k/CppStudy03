#include<iostream>
#include<queue>
#include<stack>
#include<cmath>

using namespace std;

/*
	��������ƽ������BST��+���ƽ�����(ƽ�⣺���������������ĸ߶Ȳ����1)
	AVL��Ϊ��ά�����ƽ����������ֽ����ת����

	���ʧ���ԭ��
	1. ���ӵ�������̫����(����ת����)
				  40(ʧ��ڵ�)
			 30
		  20    35
	  ������ת
			 30
		 20      40
			   35
		������a) 30��Ϊ����㣬��¼30��������
			  b) 30ԭ�����������ŵ�40����ڵ���
			  c) 40��Ϊ30���ҽڵ�

	2. �Һ��ӵ�������̫����(����ת����)
		  40(ʧ��ڵ�)
			  50
			45    60
		������ת
			  50
		  40      60
			45
		������a) 50��Ϊ���ڵ�
			  b) 50ԭ��������������40���ҽڵ���
			  c) 40��Ϊ50����ڵ�

	3. ���ӵ�������̫����(��-����ת����ƽ�����)
			40(ʧ��ڵ�)
		20
		  30
	   �ȴ�������1
	   ��20Ϊ�������С�������
			40
		  30
		20
	   ������a) 30��Ϊ"���ڵ�"�����40������
			 b) 30������������20���ҽڵ��ϣ�����30û�������������Բ���
			 c) 20��Ϊ30����ڵ�
	   Ȼ��ִ�����1������

	4. �Һ��ӵ�������̫����(��-����ת����ƽ�����)
			40(ʧ��ڵ�)
				 60
			  50
	   �ȴ�������2
	   ��60Ϊ�������С�������

	   ������a) 50���"���ڵ�"�����40���Һ���
			 b) 60������������50����ڵ��ϣ�����60û�������������Բ���
			 c) 60���50���ҽڵ�
	   Ȼ��ִ�����2������
*/

// Adelson-Velsky-Landis Tree
class AVL
{
public:
	AVL():_root(nullptr) {}
	// ����
	void insert(int val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return;
		}
		_root = _insert(_root, val);
	}

	// ɾ��
	void remove(int val)
	{
		if (_root == nullptr)
		{
			return;
		}
		_root = _remove(_root, val);
	}

	// ǰ�����
	void preorder()
	{
		cout << "ǰ�����: ";
		_preorder(_root);
		cout << endl;
	}

	// �������
	void inorder()
	{
		cout << "�������: ";
		_inorder(_root);
		cout << endl;
	}

	// �������
	void postorder()
	{
		cout << "�������: ";
		_postorder(_root);
		cout << endl;
	}

	// �������(�ǵݹ��)
	void levelorder()
	{
		queue<Node*> que;
		Node* it = _root;
		que.push(it);

		cout << "�������: ";
		while (!que.empty())
		{
			it = que.front();
			cout << it->_nodeVal << " ";
			que.pop();

			if (it->_leftChild != nullptr)
				que.push(it->_leftChild);
			if (it->_rightChild != nullptr)
				que.push(it->_rightChild);
		}
		cout << endl;
	}

	void test()
	{
		_root = leftBalance(_root);
	}

private:
	struct Node
	{
		Node(int val) :
			_nodeVal(val),
			_leftChild(nullptr),
			_rightChild(nullptr),
			_height(1){}

		int _nodeVal;
		Node* _leftChild;
		Node* _rightChild;
		int _height;
	};

	int nodeHeight(Node* it)
	{
		return it == nullptr ? 0 : it->_height;
	}

// ###### AVL�ĺ��ġ���������������ƽ����ƽ�� ################################################
	// ����ת����
	Node* leftRotate(Node* it) // �Һ��ӵ�������̫����
	{
		// �����ת
		Node* right_root = it->_rightChild;  // �������ĸ����
		it->_rightChild = right_root->_leftChild;  // �ѵ�ǰ"��"��������������it���ұ�
		right_root->_leftChild = it;  // ��it���ڵ�ǰ"��"�������

		// �߶ȸ���
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
		right_root->_height = max(nodeHeight(right_root->_leftChild), it->_height) + 1;

		return right_root;
	}

	// ����ת����
	Node* rightRotate(Node* it) // ���ӵ�������̫����
	{	
		// �����ת
		Node* left_root = it->_leftChild;  // �������ĸ����
		it->_leftChild = left_root->_rightChild;  // �ѵ�ǰ"��"��������������it�����
		left_root->_rightChild = it;  // ��it���ڵ�ǰ"��"�����ұ�


		// �߶ȸ���
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
		left_root->_height = max(nodeHeight(left_root->_leftChild), it->_height) + 1;

		return left_root;
	}

	// ��ƽ�����
	Node* leftBalance(Node* it)  // ���ӵ�������̫����
	{
		it->_leftChild = leftRotate(it->_leftChild);  // ������Ϊ������������
		return rightRotate(it);  // �������ת�������ִ������
	}

	// ��ƽ�����
	Node* rightBalance(Node* it)  // �Һ��ӵ�������̫����
	{
		it->_rightChild = rightRotate(it->_rightChild);  // ���Һ���Ϊ������������
		return leftRotate(it);  // �������ת�������ִ������
	}
// ############################################################################################

	Node* _insert(Node* it, int val)  // Ҫ���½ڵ�ĸ߶�
	{
		if (it == nullptr)
			return new Node(val); 
		
		if (val < it->_nodeVal)
		{
			// �����Ҷ�ӽڵ㣬��ô���ݹ��ʱ��it==nullptr������һ���������½��
			// �����ӵ�Ҷ�ӽ�����/��������
			it->_leftChild = _insert(it->_leftChild, val);
			// ������������Ľڵ㣬���ʧ�⣬�ǿ϶����������߶ȴ���������
			if (nodeHeight(it->_leftChild) - nodeHeight(it->_rightChild) > 1)
			{
				if (nodeHeight(it->_leftChild->_leftChild) >=
					nodeHeight(it->_leftChild->_rightChild))
				{	// �ڵ�ʧ�������ӵ�������̫�ߵ���
					it = rightRotate(it);
				}
				else
				{   // �ڵ�ʧ�������ӵ�������̫�ߵ���
					it = leftBalance(it);
				}
			}
		}
		else if (val > it->_nodeVal)
		{
			it->_rightChild = _insert(it->_rightChild, val);
			// ������������Ľڵ㣬���ʧ�⣬�ǿ϶����������߶�С��������
			if (nodeHeight(it->_rightChild) - nodeHeight(it->_leftChild) > 1)
			{
				if (nodeHeight(it->_rightChild->_rightChild) >=
					nodeHeight(it->_rightChild->_rightChild))
				{	// �ڵ�ʧ�����Һ��ӵ�������̫�ߵ���
					it = leftRotate(it);
				}
				else
				{   // �ڵ�ʧ�����Һ��ӵ�������̫�ߵ���
					it = rightBalance(it);
				}
			}
		}
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;

		return it;  // ����ʱ��Ч��it->_leftChild = it->_leftChild��û��ʲôЧ��
	}

	Node* _remove(Node* it, int val)
	{
		if (it == nullptr)
			return nullptr;
		// �ж�
		if (val < it->_nodeVal)
		{
			it->_leftChild = _remove(it->_leftChild, val);
			// ɾ�����������Ľڵ㣬���ʧ�⣬�ǿ϶����������߶ȴ���������
			if (nodeHeight(it->_leftChild) - nodeHeight(it->_rightChild) < -1)
			{
				if (nodeHeight(it->_rightChild->_leftChild) <=
					nodeHeight(it->_rightChild->_rightChild))
				{	// �ڵ�ʧ�����Һ��ӵ�������̫�ߵ���
					it = leftRotate(it);
				}
				else
				{   // �ڵ�ʧ�����Һ��ӵ�������̫�ߵ���
					it = rightBalance(it);
				}
			}
		}
		else if (val > it->_nodeVal)
		{
			it->_rightChild = _remove(it->_rightChild, val);
			// ɾ�����������Ľڵ㣬���ʧ�⣬�ǿ϶����������߶ȴ���������
			if (nodeHeight(it->_rightChild) - nodeHeight(it->_leftChild) < -1)
			{
				if (nodeHeight(it->_leftChild->_rightChild) <=
					nodeHeight(it->_leftChild->_leftChild))
				{	// �ڵ�ʧ�������ӵ�������̫�ߵ���
					it = rightRotate(it);
				}
				else
				{   // �ڵ�ʧ�������ӵ�������̫�ߵ���
					it = leftBalance(it);
				}
			}
		}
		else  // �ҵ��˴�ɾ���ڵ�
		{
			// �����ɾ���ڵ�û����������
			if (it->_leftChild == nullptr && it->_rightChild == nullptr)
			{
				delete it;
				return nullptr;
			}
			// �����ɾ���ڵ������������
			//else if (it->_leftChild != nullptr && it->_rightChild != nullptr)
			//{	// ȥ��ǰ�����
			//	Node* front = it->_leftChild;
			//	Node* back_front = it;
			//
			//	while (front->_rightChild != nullptr)
			//	{
			//		back_front = front;  // ����front�ĸ��ڵ�
			//		front = front->_rightChild;
			//	}
			//		
			//	// �Ѵ�ɾ���ڵ��滻Ϊǰ���ڵ�
			//	it->_nodeVal = front->_nodeVal; 
			//	
			//	// ɾ��ǰ���ڵ㣬����������һ��
			//	Node* front_left = front->_leftChild;
			//	delete front;
			//	back_front->_rightChild = front_left;
			//
			//	// ����it��front���ĸ߶ȣ�front���������ĸ߶Ȳ���Ӱ��
			//	stack<Node*> st;
			//	Node* its = it->_leftChild;
			//	while (its != front_left)
			//	{
			//		cout << its->_nodeVal << endl;
			//		st.push(its);
			//		its = its->_rightChild;
			//	}
			//	cout << st.size() << endl;
			//	while (!st.empty())
			//	{
			//		// ��it��ʼһ·�������ҵ�front�������ҵ�
			//		Node* itp = st.top();
			//		itp->_height = max(nodeHeight(itp->_leftChild), its->_height) + 1;
			//		its = st.top();
			//		st.pop();
			//	}
			//	it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
			//	return it;
			//}
			else if (it->_leftChild != nullptr && it->_rightChild != nullptr)
			{   // Ϊ�˱���ɾ��ǰ�����ߺ�̽ڵ���ɽڵ�ʧ�⣬˭��ɾ��˭
				if (nodeHeight(it->_leftChild) >= nodeHeight(it->_rightChild))
				{   // ɾǰ��
					Node* pre = it->_leftChild;
					while (pre->_rightChild != nullptr)
						pre = pre->_rightChild;
					it->_nodeVal = pre->_nodeVal;
					// ��Ȼͨ���ݹ���ɾ��ǰ�����
					it->_leftChild = _remove(it->_leftChild, pre->_nodeVal);
				}
				else
				{   // ɾ���
					Node* post = it->_rightChild;
					while (post->_leftChild != nullptr)
						post = post->_leftChild;
					it->_nodeVal = post->_nodeVal;
					// ��Ȼͨ���ݹ���ɾ����̽��
					it->_rightChild = _remove(it->_rightChild, post->_nodeVal);
				}
			}
			// �����ɾ���ڵ������������
			else
			{
				Node* it_Child = nullptr;
				if (it->_leftChild != nullptr)
					it_Child = it->_leftChild;
				else
					it_Child = it->_rightChild;
				delete it;

				return it_Child;
			}
		}
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
		return it;
	}

	void _preorder(Node* it)
	{
		if (it == nullptr)
			return;
		cout << it->_nodeVal << " ";
		_preorder(it->_leftChild);
		_preorder(it->_rightChild);
	}

	void _inorder(Node* it)
	{
		if (it == nullptr)
			return;

		_inorder(it->_leftChild);
		cout << it->_nodeVal << " ";
		_inorder(it->_rightChild);
	}

	void _postorder(Node* it)
	{
		if (it == nullptr)
			return;

		_postorder(it->_leftChild);
		_postorder(it->_rightChild);
		cout << it->_nodeVal << " ";
	}

	Node* _root;
};

int main()
{
	AVL avl1;
	for (auto item : { 1,2,3,4,5,6,7,8,9,10 })
	{
		avl1.insert(item);
	}
	avl1.inorder();
	avl1.preorder();
	avl1.postorder();
	avl1.levelorder();

	//avl1.test();
	avl1.remove(1);
	avl1.remove(2);
	avl1.remove(7);
	avl1.remove(10);
	avl1.remove(9);
	avl1.remove(8);
	
	return 0;
}