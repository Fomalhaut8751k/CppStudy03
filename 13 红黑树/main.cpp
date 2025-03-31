#include<iostream>

using namespace std;

/*  ��������������
	1. ÿһ���ڵ㶼������ɫ�ģ����Ǻ�ɫ�����Ǻ�ɫ
	2. nullptr�Ǻ�ɫ�ģ���Ҷ�ӽڵ��"�����ӽڵ�"nullptr�Ǻ�ɫ��
	3. root�������Ǻ�ɫ��
	4. ���ܳ��������ĺ�ɫ�ڵ�
	5. �Ӹ��ڵ㿪ʼ��������һ��Ҷ�ӽ���·���ϣ���ɫ��������������һ�µ�
*/

template<typename T>
class RedBlackTree
{
public:
	RedBlackTree() :_root(nullptr) {};

	// ����
	void insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return;
		}
		_root = _insert(_root, val, 0);
	}

private:
	struct Node
	{
		Node(T val = val(), bool color = 0) :
			_nodeVal(val),
			_nodeColor(color),
			_leftChild(nullptr),
			_rightChild(nullptr) {}

		T _nodeVal;
		bool _nodeColor;  // 1��ʾ�죬0��ʾ��
		Node* _leftChild;
		Node* _rightChild;  
		Node* _parentChild;  // ���ڵ�
	};

	Node* _root;

	Node* _insert(Node* it, const T& val, bool it_color)
	{
		if (it == nullptr)
			return new Node(val);
		if(val < it->_nodeVal)
			it->_leftChild = _insert(it->_leftChild, val, it->_nodeColor);
		if (val > it->_nodeVal)
			it->_rightChild = _insert(it->_rightChild, val, it->_nodeColor);
		return it;
	}
	
	// ����
	Node* leftRotate(Node* it)
	{
		Node* it_right = it->_rightChild;  // ��¼���Һ���
		it->_rightChild = it_right->_leftChild;  // ���Һ��ӵ��������ҵ������ұ�
		it_right->_leftChild = it;  // �Ѹ��ҵ��Һ��ӵ���ߣ��Һ��ӳ�Ϊ�µĸ�
		return it_right;
	}

	// ����
	Node* rightRotate(Node* it)
	{
		Node* it_left = it->_leftChild;  // ��¼������
		it->_leftChild = it_left->_rightChild;  // �����ӵ��������ҵ��������
		it_left->_rightChild = it;  // �Ѹ��ҵ����ӵ��ұߣ����ӳ�Ϊ�µĸ�
		return it_left;
	}
};


int main()
{
	RedBlackTree<int> rbt1;
	rbt1.insert(12);
	rbt1.insert(7);
	rbt1.insert(15);

	return 0;
}