#include<iostream>
#include<algorithm>

using namespace std;

template<typename T, typename Compare=less<T>>
class BinarySearchTree
{                           
public:   
	// Ĭ�Ϲ���
	BinarySearchTree()
		:_root(nullptr){}

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
				if(comp(it->_nodeVal, val))
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
				else if(comp(val, it->_nodeVal))// �������ֵ��С����Ӧ����������
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
	}/*
		�������ַ����õ���BST����ƽ�� 
		����һ�β����ֵ���������������λ��ʱ�����ƽ��
	*/

	// ɾ��(�ǵݹ�)
	/*
		1. û�к��ӵĽ�㣬���ڵ��ַ��Ϊnulllptr
		2. ��һ�����ӣ�����д�븸�ڵ��ַ
		3. ���������ӣ��Ҵ�ɾ���ڵ��ǰ���ڵ���̽ڵ㣬��ǰ���ڵ���̽ڵ㽫�串�ǵ���Ȼ��
		   ɾ��ǰ�������̽ڵ�
		   ǰ����㣺��ǰ�ڵ���������ֵ���Ľ��/��ҵĽ��
		   ��̽�㣺��ǰ�ڵ���������ֵ��С�Ľ��/���Ľ��
	*/
	void remove(const T& val)
	{
		if (empty())
		{
			cout << "�Ҳ�����ɾ����ֵ" << endl;
			return;
		}
		auto it = _root;
		auto itbefore = it;
		while (it != nullptr)
		{
			if (comp(it->_nodeVal, val))
			{
				itbefore = it;
				it = it->_rightChild;
			}
			else if (comp(val, it->_nodeVal))
			{
				itbefore = it;
				it = it->_leftChild;
			}
			else  // �ҵ��˶�Ӧ�Ľ��
			{
				// �����ǰ�ڵ�ֻ��һ���ӽڵ���߸ɴ�û��
				if (!(it->_leftChild != nullptr && it->_rightChild != nullptr))
				{
					delete it;
					it->_leftChild = it->_rightChild = nullptr;
				}
				// �����ǰ�ڵ��������ӽڵ�
				else
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
				return;
			}
		}
		cout << "�Ҳ�����ɾ����ֵ" << endl;
	}
	

	// ����(�ݹ�)  Ҳ���Ե��Ե�ʱ��
	struct Node;
	void foreach() const
	{
		_foreach(_root, 0);
	}

	void _foreach(Node* it, int layer, int direction = 0) const
	{
		if (it != nullptr)
		{
			if (direction==0)
			{
				cout << "��" << layer << "��(��): " << it->_nodeVal << endl;
			}
			else
			{
				cout << "��" << layer << "��(��): " << it->_nodeVal << endl;
			}
			
			_foreach(it->_leftChild, layer + 1, 0);
			_foreach(it->_rightChild, layer + 1, 1);
		}
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

	Node* _root;
	Compare comp;
};

int main()
{
	/*srand((unsigned int)time(NULL));
	BinarySearchTree<int> bst1;
	bst1.insert(5);
	for (int i = 0; i < 10; i++)
	{
		bst1.insert(rand()%10 + 1);
	}

	bst1.foreach();*/

	int arr[] = { 58, 24, 67, 0, 34,62, 69,5,41,64, 78 };
	BinarySearchTree<int> bst2;
	for (int i = 0; i < 11; i++)
	{
		bst2.insert(arr[i]);
	}

	bst2.foreach();

	bst2.remove(67);

	cout << "---------------------------" << endl;
	bst2.foreach();

	return 0;
}