#include<iostream>
#include<algorithm>

using namespace std;

template<typename T, typename Compare=less<T>>
class BinarySearchTree
{                           
public:   
	// 默认构造
	BinarySearchTree()
		:_root(nullptr){}

	// 判空
	bool empty() const
	{
		return _root == nullptr;
	}

	// 插入(非递归)
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
				// 比较待插入值和当前节点的值
				// if (val > it->_nodeVal)  // 如果插入值更大，那应该往右下找
				if(comp(it->_nodeVal, val))
				{
					if (it->_rightChild == nullptr)  // 如果右下没有结点
					{
						it->_rightChild = new Node(val); // 就直接放在右下
						break;
					}
					else
					{
						it = it->_rightChild; // 否则往下找
					}
				}
				// else 
				else if(comp(val, it->_nodeVal))// 如果插入值更小，那应该往左下找
				{
					if (it->_leftChild == nullptr)   // 如果左下没有结点
					{
						it->_leftChild = new Node(val);  // 就直接放在左下
						break;
					}
					else
					{
						it = it->_leftChild; // 否则往下找
					}
				}
				else  // 相同的元素？
				{
					cout << "树中存在相同的元素，无法插入" << endl;
					return;
				}
			}
		}
	}/*
		但是这种方法得到的BST不够平衡 
		当第一次插入的值大概是所有树的中位数时会相对平衡
	*/

	// 删除(非递归)
	/*
		1. 没有孩子的结点，父节点地址置为nulllptr
		2. 有一个孩子，孩子写入父节点地址
		3. 有两个孩子，找待删除节点的前驱节点或后继节点，用前驱节点或后继节点将其覆盖掉，然后
		   删除前驱结点或后继节点
		   前驱结点：当前节点左子树中值最大的结点/最靠右的结点
		   后继结点：当前节点右子树中值最小的结点/最靠左的结点
	*/
	void remove(const T& val)
	{
		if (empty())
		{
			cout << "找不到待删除的值" << endl;
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
			else  // 找到了对应的结点
			{
				// 如果当前节点只有一个子节点或者干脆没有
				if (!(it->_leftChild != nullptr && it->_rightChild != nullptr))
				{
					delete it;
					it->_leftChild = it->_rightChild = nullptr;
				}
				// 如果当前节点有两个子节点
				else
				{
					// 找前置节点
					auto itfront = it->_leftChild;
					itbefore = it;
					while (itfront->_rightChild != nullptr)
					{
						itbefore = itfront;
						itfront = itfront->_rightChild;
					}
					// 此时的itfront就是前置节点
					it->_nodeVal = itfront->_nodeVal;
					delete itfront;
					itbefore->_leftChild = itbefore->_rightChild = nullptr;
				}
				return;
			}
		}
		cout << "找不到待删除的值" << endl;
	}
	

	// 遍历(递归)  也可以调试的时候看
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
				cout << "第" << layer << "层(左): " << it->_nodeVal << endl;
			}
			else
			{
				cout << "第" << layer << "层(右): " << it->_nodeVal << endl;
			}
			
			_foreach(it->_leftChild, layer + 1, 0);
			_foreach(it->_rightChild, layer + 1, 1);
		}
	}

private:    
	struct Node
	{
		// Node(T val = 0)
		Node(T val = T())  // 零构造
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