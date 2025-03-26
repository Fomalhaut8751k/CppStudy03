#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template<typename T, typename Compare = less<T>>
class BinarySearchTree
{
public:
	// Ĭ�Ϲ���
	BinarySearchTree()
		:_root(nullptr) {}

	struct Node;

	// �п�
	bool empty() const
	{
		return _root == nullptr;
	}

	// ����(�ǵݹ�)
	void insert(const T& val)
	{
		if (empty())
		{
			_root = new Node(val);
		}
		else
		{
			Node* it = _root;
			while (it != nullptr)
			{
				// �Ƚϴ�����ֵ�͵�ǰ�ڵ��ֵ
				// if (val > it->_nodeVal)  // �������ֵ������Ӧ����������
				if (comp(it->_nodeVal, val))
				{
					if (it->_rightChild == nullptr)  // �������û�н��
					{
						it->_rightChild = new Node(val); // ��ֱ�ӷ�������
						break;
					}
					else
					{
						it = it->_rightChild; // ����������
					}
				}
				// else 
				else if (comp(val, it->_nodeVal))// �������ֵ��С����Ӧ����������
				{
					if (it->_leftChild == nullptr)   // �������û�н��
					{
						it->_leftChild = new Node(val);  // ��ֱ�ӷ�������
						break;
					}
					else
					{
						it = it->_leftChild; // ����������
					}
				}
				else  // ��ͬ��Ԫ�أ�
				{
					cout << "���д�����ͬ��Ԫ�أ��޷�����" << endl;
					return;
				}
			}
		}
	}

	// ����(�ݹ�)
	void insertRecursion(const T& val)
	{
		_root = _insertRecursion(_root, val);
	}

	// ɾ��(�ǵݹ�)
	void remove(const T& val)
	{
		if (empty())
		{
			cout << "�Ҳ�����ɾ����ֵ" << endl;
			return;
		}
		auto it = _root;
		auto itbefore = it;
		auto itbeforedirection = "left";
		while (it != nullptr)
		{
			if (comp(it->_nodeVal, val))
			{
				itbefore = it;
				it = it->_rightChild;
				itbeforedirection = "right";
			}
			else if (comp(val, it->_nodeVal))
			{
				itbefore = it;
				it = it->_leftChild;
				itbeforedirection = "left";
			}
			else  // �ҵ��˶�Ӧ�Ľ��
			{
				// �����ǰ�ڵ��������ӽڵ�
				if (it->_leftChild != nullptr && it->_rightChild != nullptr)
				{
					// ��ǰ�ýڵ�
					auto itfront = it->_leftChild;
					itbefore = it;
					while (itfront->_rightChild != nullptr)
					{
						itbefore = itfront;
						itfront = itfront->_rightChild;
					}
					// ��ʱ��itfront����ǰ�ýڵ�
					it->_nodeVal = itfront->_nodeVal;
					delete itfront;
					itbefore->_leftChild = itbefore->_rightChild = nullptr;
				}
				// �����ǰ�ڵ�û���ӽڵ�
				else if (it->_leftChild == nullptr && it->_rightChild == nullptr)
				{
					if (it == itbefore)  // ˵���Ǹ����
					{
						delete it;
						_root = nullptr;
						return;
					}
					delete it;
					// ȷ����д�����ڵ�����ַ�����ҵ�ַ
					if (itbeforedirection == "left")
						itbefore->_leftChild = nullptr;
					else
						itbefore->_rightChild = nullptr;
				}
				// ���ֻ�����ӽڵ�
				else if (it->_leftChild != nullptr)
				{
					if (it == itbefore)  // ˵���Ǹ����
					{	// ֱ����rootָ����������ӽڵ�
						_root = it->_leftChild;
						delete it;
						return;
					}
					// ������ŵ����ӽڵ�ĵ�ַ�������ĸ��ڵ�ģ�
					if (itbeforedirection == "right")
						itbefore->_rightChild = it->_leftChild;
					else
						itbefore->_leftChild = it->_leftChild;
					delete it;
				}
				// ���ֻ�����ӽڵ�
				else
				{
					if (it == itbefore)  // ˵���Ǹ����
					{	// ֱ����rootָ����������ӽڵ�
						_root = it->_rightChild;
						delete it;
						return;
					}
					if (itbeforedirection == "right")
						itbefore->_rightChild = it->_rightChild;
					else
						itbefore->_leftChild = it->_rightChild;
					delete it;
				}
				return;
			}
		}
		cout << "�Ҳ�����ɾ����ֵ" << endl;
	}

	// ɾ��(�ݹ�)
	void removeRecursion(const T& val)
	{
		_root = _removeRecursion(_root, val);
	}

	// ��ѯ(�ǵݹ�)
	bool find(const T& val) const
	{
		auto it = _root;
		while (it != nullptr)
		{
			if (comp(val, it->_nodeVal))  // С��
				it = it->_leftChild;
			else if (comp(it->_nodeVal, val))  // ����
				it = it->_rightChild;
			else
				return true;
		}
		return false;
	}

	// ��ѯ(�ݹ�)
	bool findRecursion(const T& val)
	{
		return _findRecursion(_root, val);
	}

	// ��������
	int level()
	{
		return _level(_root);
	}

	// ���ؽڵ���
	int number()
	{
		return _number(_root);
	}

	// ǰ�����
	void foreachPreorder() const
	{
		cout << "ǰ�����: ";
		_foreachPreorder(_root);
		cout << endl;
	}

	// �������
	void foreachInorder() const
	{
		cout << "�������: ";
		_foreachInorder(_root);
		cout << endl;
	}

	// �������
	void foreachPostorder() const
	{
		cout << "�������: ";
		_foreachPostorder(_root);
		cout << endl;
	}

	// �������
	void foreachSequence()
	{
		/*  һ�α������޷���ɵģ���Ҫ��α�����ͬʱ���Ʊ������Ĳ���  */
		cout << "�������: ";
		int lev = level();
		for (int i = 0; i < lev; ++i)
		{
			_foreachSequence(_root, i);
		}
		cout << endl;
	}

	// �����ѯ
	void findRange(vector<T>& vec, int left, int right)
	{
		_findRange(_root, vec, left, right);
	}

	// �Ƿ���BST�����ж�
	bool isBinarySearchTree()
	{
		// ��Ȼ���������������������У������ǰ��ֵС��ǰ���ֵ���ǾͲ���BST��
		Node* node = nullptr;
		return _isBinarySearchTree(_root, node);
	}

	// �Ƿ����������ж�
	bool isChildTree(BinarySearchTree<T,Compare>& bst)
	{
		// ����bst�ĸ����
		Node* it = _root;
		while (it != nullptr)
		{
			if (comp(it->_nodeVal, bst._root->_nodeVal))  // ����
			{
				it = it->_rightChild;
			}
			else if (comp(bst._root->_nodeVal, it->_nodeVal)) // С��
			{
				it = it->_leftChild;
			}
			else  // �ҵ��˸����
			{
				// �õ�ǰ������bst����
				return _isChildTree(it, bst._root);
			}
		}
		return false;  // ������㶼û�ҵ����϶�����
	}

	// �����������
	int getLowestCommonAncestor(int L, int R)
	{
		// ���ж��Ƿ�������
		if (find(L) && find(R))
		{
			return _getLowestCommonAncestor(_root, L, R);
		}
		else
		{
			//throw "L��Rû�й�������";
			cout << "L��Rû�й�������" << endl;
			return -1;
		}
	}

	// ����ת
	void mirrorInverse()
	{
		// ǰ�����
		_mirrorInverse(_root);
	}

	// ����Գ��ж�
	bool mirrorSymmetry()
	{
		return _mirrorSymmetry(_root, _root);
	}

	// ��ǰ����������������ԭ������
	void restoreByPreorderandInOrder(int pre[], int i, int j, int in[], int m, int n)
	{
		_root = _restoreByPreorderandInOrder(pre, i, j, in, m, n);

	}
private:
	struct Node
	{
		// Node(T val = 0)
		Node(T val = T())  // �㹹��
			:_nodeVal(val),
			_leftChild(nullptr),
			_rightChild(nullptr) {};

		T _nodeVal;
		Node* _leftChild;
		Node* _rightChild;
	};

	void _foreachPreorder(Node* it) const
	{
		if (it != nullptr)
		{
			cout << it->_nodeVal << " ";
			_foreachPreorder(it->_leftChild);
			_foreachPreorder(it->_rightChild);
		}
	}

	void _foreachInorder(Node* it) const
	{
		if (it != nullptr)
		{
			_foreachInorder(it->_leftChild);
			cout << it->_nodeVal << " ";
			_foreachInorder(it->_rightChild);
		}
	}

	void _foreachPostorder(Node* it) const
	{
		if (it != nullptr)
		{
			_foreachPostorder(it->_leftChild);
			_foreachPostorder(it->_rightChild);
			cout << it->_nodeVal << " ";
		}
	}

	void _foreachSequence(Node* it, int layer) const
	{
		if (it == nullptr)
		{
			return;
		}
		if (layer == 0)
		{
			cout << it->_nodeVal << " ";
			return;
		}
		_foreachSequence(it->_leftChild, layer - 1);
		_foreachSequence(it->_rightChild, layer - 1);
	}

	Node* _insertRecursion(Node* it, const T& val)
	{
		if (it == nullptr)  // �½��Ӧ�÷�������
		{
			return new Node(val);  // ��ַ���ظ�����һ�������
		}
		if (it->_nodeVal == val)  // �����ȣ��Ͳ�����
		{
			return it;
		}
		else if (comp(it->_nodeVal, val))  // val > it->_nodeVal  ����
		{
			// ����ǵݹ鵽nullptr�����½�㣬����������it->_rightChild��
			// ������ǣ�return it�൱��it->_rightChild = it->_rightChild��û���κ�Ӱ��
			it->_rightChild = _insertRecursion(it->_rightChild, val);
			return it;
		}
		else
		{
			it->_leftChild = _insertRecursion(it->_leftChild, val);
			return it;
		}
		return it;
	}

	Node* _findRecursion(Node* it, const T& val)
	{
		if (it == nullptr)
		{
			return nullptr;
		}
		if (it->_nodeVal == val)
		{
			return it;
		}
		else if (comp(it->_nodeVal, val))
		{
			return _findRecursion(it->_rightChild, val);
		}
		else
		{
			return _findRecursion(it->_leftChild, val);
		}
		return nullptr;
	}

	Node* _removeRecursion(Node* it, const T& val)
	{
		if (it == nullptr)  // �Ҳ���
		{
			return nullptr;
		}
		if (it->_nodeVal == val)  // �ҵ���
		{
			// û���κ��ӽڵ�
			if (it->_leftChild == nullptr && it->_rightChild == nullptr)
			{
				delete it;
				return nullptr;
			}
			// �����ӽڵ����
			else if (it->_leftChild != nullptr && it->_rightChild != nullptr)
			{
				// ��ǰ�̽ڵ㣬������ѭ������
				Node* pre = it->_leftChild;
				while (pre->_rightChild != nullptr)
				{
					pre = pre->_rightChild;
				}
				it->_nodeVal = pre->_nodeVal;
				// ��������������
				it->_leftChild = _removeRecursion(it->_leftChild, pre->_nodeVal);
			}
			// ֻ��һ�����
			else
			{
				if (it->_leftChild != nullptr)
				{
					Node* left = it->_leftChild;
					delete it;
					return left;
				}
				else
				{
					Node* right = it->_rightChild;
					delete it;
					return right;
				}
			}
		}
		else if (comp(it->_nodeVal, val))
		{
			it->_rightChild = _removeRecursion(it->_rightChild, val);
			return it;
		}
		else
		{
			it->_leftChild = _removeRecursion(it->_leftChild, val);
			return it;
		}
		return it;
	}

	int _level(Node* it)
	{
		// �������ָ��nullptr
		if (it == nullptr)
		{   // ��ʱ�������һ����㣬���ݺ����
			return 0;
		}
		int left = _level(it->_leftChild);
		int right = _level(it->_rightChild);
		return left > right ? left + 1 : right + 1;  // ��1�Ǽ��ϵ�ǰ�ڵ�
	}

	int _number(Node* it)
	{
		if (it == nullptr)
		{
			return 0;
		}
		int left = _number(it->_leftChild);
		int right = _number(it->_rightChild);
		return left + right + 1;
	}

	void _findRange(Node* it, vector<T>& vec, int _left, int _right)
	{
		if (it != nullptr)
		{
			// �����ǰ�ڵ��ֵС����߽磬���������������н�㶼С����߽磬�������
			if (it->_nodeVal >= _left)
				_findRange(it->_leftChild, vec, _left, _right);
			
			// ����������д�С���������
			if (it->_nodeVal >= _left && it->_nodeVal <= _right)
			{
				vec.push_back(it->_nodeVal);
			}

			// �����ǰ�ڵ��ֵ�����ұ߽磬���������������н�㶼�����ұ߽磬�������
			if (it->_nodeVal <= _right)
				_findRange(it->_rightChild, vec, _left, _right);

		}
	}

	bool _isBinarySearchTree(Node* it, Node* &pre)
	{
		// ԭ�������������Ҫ���ϸ����(��Ϊû���ظ���)
		// �жϵ����ǵ����ľͷ���false
		if (it == nullptr)  
		{
			return true;
		}
		if (!_isBinarySearchTree(it->_leftChild, pre))
		{
			return false;
		}
		if (pre != nullptr)  // pre�ж��Ƿ�Ϊ�գ��Ǳ����һ�����ʱû��pre
		{
			if (comp(it->_nodeVal, pre->_nodeVal))
			{
				return false;
			}
		}
		pre = it; // ����ǰһ�����
		return _isBinarySearchTree(it->_rightChild, pre);
	}

	bool _isChildTree(Node* father, Node* child)
	{
		// 
		if (father == nullptr && child == nullptr)
		{
			return true;
		}
		if (father == nullptr)
		{
			return false;
		}
		if (child == nullptr)
		{
			return true;
		}
		//else
		//{
		//	if (!_isChildTree(father->_leftChild, child->_leftChild))
		//	{
		//		return false;
		//	}
		//	if (father->_nodeVal != child->_nodeVal)
		//	{
		//		return false;
		//	}
		//	
		//	if (!_isChildTree(father->_rightChild, child->_rightChild))
		//	{
		//		return false;
		//	}
		//}
		if (father->_nodeVal != child->_nodeVal)
		{
			return false;
		}
		return _isChildTree(father->_leftChild, child->_leftChild)
			&& _isChildTree(father->_rightChild, child->_rightChild);
	}

	int _getLowestCommonAncestor(Node* it, int L, int R)
	{
		if ((!comp(it->_nodeVal, L)) && (!comp(R, it->_nodeVal)))
		{
			return it->_nodeVal;
		}
		if (comp(it->_nodeVal, L))
		{
			return _getLowestCommonAncestor(it->_rightChild, L, R);
		}
		if (comp(R, it->_nodeVal))
		{
			return _getLowestCommonAncestor(it->_leftChild, L, R);
		}
		return it->_nodeVal;
	}
	
	void _mirrorInverse(Node* it)
	{
		if (it == nullptr)
		{
			return;
		}

		Node* _tempChild = it->_leftChild;
		it->_leftChild = it->_rightChild;
		it->_rightChild = _tempChild;

		_mirrorInverse(it->_leftChild);
		_mirrorInverse(it->_rightChild);
	}

	bool _mirrorSymmetry(Node* it1, Node* it2)
	{
		if (it1 == nullptr && it2 == nullptr)
		{
			return true;
		}
		else if (it1 == nullptr || it2 == nullptr)
		{
			return false;
		}
		else
		{
			if (it1->_nodeVal != it2->_nodeVal)
			{
				return false;
			}

			return _mirrorSymmetry(it1->_leftChild, it2->_rightChild)
				&& _mirrorSymmetry(it1->_rightChild, it2->_leftChild);
		}
	}

	Node* _restoreByPreorderandInOrder(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}
		// ������ǰ�����ĸ����
		Node* node = new Node(pre[i]);  // ��ǰ��ĵ�һ�����ִ������������
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k])  // ��������������������ڵ��±�k
			{
				node->_leftChild = _restoreByPreorderandInOrder(
					pre, i + 1, i + k - m, in, m, k - 1);
				node->_rightChild = _restoreByPreorderandInOrder(
					pre, i + k - m + 1, j, in, k + 1, n);
				return node;
			}
		}
		return node;
	}

	Node* _root;
	Compare comp;

	friend void test01();
	friend void test02();
	friend void test03();
	friend void test04(int _preOrder[], int _inOrder[]);
};

// ����һ��һ�������
void test01()
{
	using Node = BinarySearchTree<int>::Node;
	BinarySearchTree<int> bst;

	bst._root = new Node(40);
	Node* node_1 = new Node(20);
	Node* node_2 = new Node(60);
	Node* node_3 = new Node(30);
	Node* node_4 = new Node(80);

	bst._root->_leftChild = node_1;
	bst._root->_rightChild = node_2;
	node_2->_leftChild = node_3;
	node_2->_rightChild = node_4;

	//bst.foreachInorder();
	// �������: 20 40 30 60 80
	// ��Ȼ��������BST���������������

	cout << "bst3�Ƿ��Ƕ��ֲ�����: " << bst.isBinarySearchTree() << endl;
}


// �����ж�����
void test02() {
	int arr[] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78 };
	BinarySearchTree<int> bst1;
	for (int i = 0; i < 11; ++i)
	{
		bst1.insert(arr[i]);
	}

	using Node = BinarySearchTree<int>::Node;
	BinarySearchTree<int> bst;

	bst._root = new Node(67);
	Node* node_1 = new Node(62);
	Node* node_2 = new Node(69);
	Node* node_3 = new Node(30);

	bst._root->_leftChild = node_1;
	bst._root->_rightChild = node_2;

	cout << "�Ƿ�������: " << bst1.isChildTree(bst) << endl;

	node_2->_leftChild = node_3;

	cout << "�Ƿ�������: " << bst1.isChildTree(bst) << endl;
}

// ����Գ�����
void test03()
{
	using Node = BinarySearchTree<int>::Node;
	BinarySearchTree<int> bst;

	bst._root = new Node(67);
	Node* node_1 = new Node(31);
	Node* node_2 = new Node(31);

	bst._root->_leftChild = node_1;
	bst._root->_rightChild = node_2;

	cout << "\n�Ƿ���Գ�: " << bst.mirrorSymmetry() << endl;

	Node* node_3 = new Node(30);
	node_2->_leftChild = node_3;

	cout << "����Ԫ�غ��Ƿ���Գ�: " << bst.mirrorSymmetry() << endl;

	Node* node_4 = new Node(30);
	node_1->_rightChild = node_4;

	cout << "�ԳƲ�����ͬԪ�غ��Ƿ���Գ�: " << bst.mirrorSymmetry() << endl;

	Node* node_5 = new Node(12);
	Node* node_6 = new Node(17);
	node_1->_leftChild = node_5;
	node_2->_rightChild = node_6;

	cout << "�ԳƲ��벻ͬԪ�غ��Ƿ���Գ�: " << bst.mirrorSymmetry() << endl;
}

// ��ǰ����������������ԭ������
/*
	������Ҫ������ȫ�ֱ�����һ�����Զ�����ຯ����Ȼ���ʼ�������
*/
BinarySearchTree<int>::Node* _restoreByPreorderandInOrder(
	BinarySearchTree<int>::Node* it,
	int _preOrder[], int _inOrder[], int& idxPre, int L, int R)
{
	if (L > R)
	{
		idxPre--;
		return nullptr;
	}
	// ��С���䳤��Ϊ1���򴴽��ڵ�
	if (L == R)
		return new BinarySearchTree<int>::Node(_preOrder[idxPre]);
	

	// Ѱ��ǰ������нڵ�����������ж�Ӧ��λ��
	int idxIn = L;
	for (; idxIn < R; idxIn++)
	{
		if (_inOrder[idxIn] == _preOrder[idxPre])
			break;
	}

	it = new BinarySearchTree<int>::Node(_preOrder[idxPre]);

	// �ݹ�
	idxPre++;
	it->_leftChild = _restoreByPreorderandInOrder(
		it->_leftChild, _preOrder, _inOrder, idxPre, L, idxIn - 1);

	idxPre++;
	it->_rightChild = _restoreByPreorderandInOrder(
		it->_rightChild, _preOrder, _inOrder, idxPre, idxIn + 1, R);

	return it;
}


BinarySearchTree<int>::Node* restoreByPreorderandInOrder(
	BinarySearchTree<int>::Node* it,
	int _preOrder[], int _inOrder[], int idxPre, int L, int R)
{
	return _restoreByPreorderandInOrder(it, _preOrder, _inOrder, idxPre, L, R);
}

void test04(int _preOrder[], int _inOrder[])
{
	cout << "\n";
	/*
	int preorder[11] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78 };
	int inorder[11] = { 0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78 };
	*/
	BinarySearchTree<int> _bst;
	int length = 11;
	_bst._root = restoreByPreorderandInOrder(
		_bst._root, _preOrder, _inOrder, 0, 0, length - 1);
	_bst.foreachPreorder();
	_bst.foreachInorder();
}

int main()
{
	BinarySearchTree<int> bst1;
	BinarySearchTree<int> bst2;
	int arr[] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78 };

// ####### 1.���룬���ң�ɾ�� #####################################################
	for(int i = 0; i < 11; ++i)
	{
		// �ǵݹ����
		bst1.insert(arr[i]);
		// �ݹ����
		bst2.insertRecursion(arr[i]);
	}
	bst1.foreachPreorder();
	bst2.foreachInorder();
	// �ǵݹ����
	cout << "\nbst1�Ƿ����67: " << bst1.find(67) << endl;
	cout << "bst1�Ƿ����5003: " << bst1.find(5003) << endl;
	// �ݹ����
	cout << "bst2�Ƿ����67: " << bst2.findRecursion(67) << endl;
	cout << "bst2�Ƿ����5003: " << bst2.findRecursion(5003) << endl;
	
	// �ǵݹ�ɾ��
	bst1.remove(67);
	cout << "\n�Ѵ�bst1��ɾ��67" << endl;
	cout << "bst1�Ƿ����67: " << bst1.find(67) << endl;
	// �ݹ�ɾ��
	bst2.removeRecursion(67);
	cout << "\n�Ѵ�bst2��ɾ��67" << endl;
	cout << "bst2�Ƿ����67: " << bst2.findRecursion(67) << "\n" << endl;
	
// ####### 2. ǰ�к�������Ͳ������ ###############################################
	// ǰ�����
	bst2.foreachPreorder();
	// �������
	bst1.foreachInorder();
	// �������
	bst2.foreachPostorder();
	// �������
	bst1.foreachSequence();

// ###### 3. ���ĸ߶ȣ����Ԫ�ظ��� ################################################
	// ���ĸ߶�
	cout << "\nbst1�ĸ߶�Ϊ: " << bst1.level() << endl;
	cout << "bst2�ĸ߶�Ϊ: " << bst2.level() << endl;
	// ����Ԫ�ظ���
	cout << "\nbst1��Ԫ�ظ���Ϊ: " << bst1.number() << endl;
	cout << "bst2��Ԫ�ظ���Ϊ: " << bst2.number() << endl;

// ###### 4. ����Ԫ�ز��� ##########################################################
	/*
		�����������������ĵ��ص�
	*/
	vector<int> vec1;
	bst1.findRange(vec1, 10, 70);
	cout << "\nbst1�н�������[10, 70]��Ԫ����: ";
	for_each(vec1.begin(), vec1.end(), [](int num)->void {cout << num << " "; });
	cout << endl;

	vec1.clear();
	bst2.findRange(vec1, 10, 69);
	cout << "bst1�н�������[10, 69]��Ԫ����: ";
	for (auto item : vec1) { cout << item << " "; }
	cout << endl;

// ###### 5. �ж�һ�ö������ǲ���BST�� #############################################
	/*
		BST��
		1. ����
		2. ���ǿ���
			a. ����������Ϊ�գ��������������н���ֵ��С�����ĸ�����ֵ
			b. ����������Ϊ�գ��������������н���ֵ���������ĸ�����ֵ
			c. ��������Ҳ�ֱ������������������

		�ص㣺ÿһ����㶼���㣬ֵ����<���<�ң�����ص����ж�ֻ���жϾֲ�
		�����������Ͳ���һ��bst�������Ƿ�������
			 60
		20         80
				30     110
	*/
	cout << "\n";
	cout << "bst1�Ƿ��Ƕ��ֲ�����: " << bst1.isBinarySearchTree() << endl;
	cout << "bst2�Ƿ��Ƕ��ֲ�����: " << bst2.isBinarySearchTree() << endl;
	test01();

// ###### 6. ���������������� ######################################################
	cout << "\n";
	test02();

// ###### 7. ����������� ##########################################################
	/*                        58 
				 24                       64		
	        0         34            62          69
			   5		  41	                    78
	*/   
	cout << "\n" << bst1.getLowestCommonAncestor(5, 41) << endl; // Ӧ����24
	cout << bst2.getLowestCommonAncestor(62, 64) << endl; // Ӧ����64
	bst1.getLowestCommonAncestor(12, 3);  // û�й�������

// ###### 8. ����ת ##############################################################
	cout << "\n����תǰ��";
	bst2.foreachInorder();
	bst2.mirrorInverse();
	cout << "����ת���";
	bst2.foreachInorder();


// ###### 9. ����Գ��ж� ##########################################################
	test03();

// ###### 10. ��֪��������ǰ�����������������ؽ������� ###########################
	int preorder[11] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78 };
	int inorder[11] = { 0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78 };
	cout << "\n�ҵķ���: ";
	test04(preorder, inorder);
	cout << "\n��Ƶ�ķ���: " << endl;
	BinarySearchTree<int> bst3;
	bst3.restoreByPreorderandInOrder(preorder, 0, 10, inorder, 0, 10);
	bst3.foreachPreorder();
	bst3.foreachInorder();

	return 0;
}