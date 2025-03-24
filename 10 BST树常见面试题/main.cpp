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

	Node* _root;
	Compare comp;
};

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
	bst1.foreachPostorder();
	bst2.foreachPostorder();
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

			 60
		20         80
				30     110
	*/

	return 0;
}