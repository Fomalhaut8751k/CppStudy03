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

	struct Node;

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

	// 插入(递归)
	void insertRecursion(const T& val)
	{
		/*if (empty())
		{
			_root = new Node(val);
			return;
		}
		_insertRecursion(_root, val);*/
		_root = _insertRecursion2(_root, val);
	}

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
			else  // 找到了对应的结点
			{
				// 如果当前节点有两个子节点
				if (it->_leftChild != nullptr && it->_rightChild != nullptr)
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
				// 如果当前节点没有子节点
				else if(it->_leftChild == nullptr && it->_rightChild == nullptr)
				{
					if (it == itbefore)  // 说明是根结点
					{
						delete it;
						_root = nullptr;
						return;
					}
					delete it;
					// 确认是写到父节点的左地址还是右地址
					if (itbeforedirection == "left")
						itbefore->_leftChild = nullptr;
					else
						itbefore->_rightChild = nullptr;
				}
				// 如果只有左子节点
				else if (it->_leftChild != nullptr)
				{
					if (it == itbefore)  // 说明是根结点
					{	// 直接让root指向根结点的左子节点
						_root = it->_leftChild;
						delete it;
						return;
					}
					// 把它存放的左子节点的地址给到它的父节点的？
					if (itbeforedirection == "right")
						itbefore->_rightChild = it->_leftChild;
					else
						itbefore->_leftChild = it->_leftChild;
					delete it;
				}
				// 如果只有右子节点
				else
				{	
					if (it == itbefore)  // 说明是根结点
					{	// 直接让root指向根结点的右子节点
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
		cout << "找不到待删除的值" << endl;
	}

	// 删除(递归)
	void removeRecursion(const T& val)
	{
		_root = _removeRecursion(_root, val);
	}
	
	// 查询(非递归)
	bool find(const T& val) const
	{
		auto it = _root;
		while (it != nullptr)
		{
			if (comp(val, it->_nodeVal))  // 小于
				it = it->_leftChild;
			else if (comp(it->_nodeVal, val))  // 大于
				it = it->_rightChild;
			else
				return true;
		}
		return false;
	}

	// 查询(递归)
	bool findRecursion(const T& val)
	{
		return _findRecursion(_root, val);
	}

	// 返回树高
	int level() 
	{
		return _level(_root);
	}

	// 返回节点数
	int number() 
	{
		return _number(_root);
	}

	/*
		二叉树的遍历：
		前序遍历，中序遍历，后序遍历，层序遍历
		把每一个结点看成V，它的左子节点看成L，右子节点看成R
		默认L出现在R的前面，就有三种组合：
			VLR, LVR, LRV
		看V的位置，V在前就是前序，在中间就是中序，在后面就是后序
		对于每个结点，按VLR这样的顺序去执行
						58
				24				67
			0		34		62		69
			  5        41      64      78
		前序遍历：VLR(输出自己，遍历左子节点，遍历右子节点)
			打印58，向左下，打印24，向左下，打印0，没有左下，右下，打印5，
			结点0执行完毕，回到24,24已经向左过了，遂向右，打印34.......
			于是结果为：
			58 24 0 5 34 41 67 62 64 69 78

		中序遍历：LVR
			0 5 24 34 41 58 62 64 67 69 78

		后序遍历：LRV
			5 0 41 34 24 64 62 78 69 67 58

		层序遍历：
			58 24 67 0 34 62 69 5 41 64 78
	*/
	
	// 前序遍历
	void foreachPreorder() const
	{
		cout << "前序遍历: ";
		_foreachPreorder(_root);
		cout << endl;
	}
	// 中序遍历
	void foreachInorder() const
	{
		cout << "中序遍历: ";
		_foreachInorder(_root);
		cout << endl;
	}
	// 后序遍历
	void foreachPostorder() const
	{
		cout << "后序遍历: ";
		_foreachPostorder(_root);
		cout << endl;
	}
	// 层序遍历
	void foreachSequence() 
	{
		/*  一次遍历是无法完成的，需要多次遍历，同时控制遍历到的层数  */
		cout << "层序遍历: ";
		int lev = level();
		for (int i = 0; i < lev; ++i)
		{
			_foreachSequence(_root, i);
		}
		cout << endl;
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
		if(it == nullptr)
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

	bool _insertRecursion(Node* it, const T& val)
	{
		if (it == nullptr)
		{
			return true;
		}
		if (comp(val, it->_nodeVal))
		{
			if (_insertRecursion(it->_leftChild, val))
			{
				it->_leftChild = new Node(val);
			}
		}
		else if (comp(it->_nodeVal, val))
		{
			if (_insertRecursion(it->_rightChild, val))
			{
				it->_rightChild = new Node(val);
			}
		}
		else
		{
			return false;
		}
		return false;
	}

	Node* _insertRecursion2(Node* it, const T& val)
	{
		if (it == nullptr)  // 新结点应该放在这里
		{
			return new Node(val);  // 地址返回给到上一个结点存放
		}
		if (it->_nodeVal == val)  // 如果相等，就不插入
		{
			return it;
		}
		else if (comp(it->_nodeVal, val))  // val > it->_nodeVal  往右
		{	
			// 如果是递归到nullptr返回新结点，则正好填入it->_rightChild中
			// 如果不是，return it相当于it->_rightChild = it->_rightChild，没有任何影响
			it->_rightChild = _insertRecursion2(it->_rightChild, val);
			return it;
		}
		else
		{
			it->_leftChild = _insertRecursion2(it->_leftChild, val);
			return it;
		}
		return it;
	}

	bool _findRecursion(Node* it, const T& val)
	{
		bool findout = false;

		if (it == nullptr)
		{
			return false;
		}

		if (comp(val, it->_nodeVal))
		{
			findout = _findRecursion(it->_leftChild, val);
			
		}
		else if (comp(it->_nodeVal, val))
		{
			findout = _findRecursion(it->_rightChild, val);
		}
		else
		{
			return true;
		}
		return findout;
	}

	Node* _findRecursion2(Node* it, const T& val)
	{
		if (it == nullptr)
		{
			return nullptr;
		}
		if (it->_nodeVal == val)
		{
			return it;
		}
		else if (comp(it->_nodeVal), val)
		{
			return _findRecursion2(it->_rightChild, val);
		}
		else
		{
			return _findRecursion2(it->leftChild, val);
		}
		return nullptr;
	}

	Node* _removeRecursion(Node* it, const T& val)
	{
		if (it == nullptr)  // 找不到
		{
			return nullptr;
		}
		if (it->_nodeVal == val)  // 找到了
		{
			// 没有任何子节点
			if (it->_leftChild == nullptr && it->_rightChild == nullptr)
			{
				delete it;
				return nullptr;
			}
			// 左右子节点皆有
			else if (it->_leftChild != nullptr && it->_rightChild != nullptr)
			{
				// 找前继节点，这里用循环即可
				Node* pre = it->_leftChild;
				while (pre->_rightChild != nullptr)
				{
					pre = pre->_rightChild;
				}
				it->_nodeVal = pre->_nodeVal;
				// 更新它的左子树
				it->_leftChild = _removeRecursion(it->_leftChild, pre->_nodeVal);
			}
			// 只有一个结点
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
		// 如果还非指向nullptr
		if (it == nullptr)  
		{   // 此时不是最后一个结点，回溯后才是
			return 0;
		}
		int left = _level(it->_leftChild);
		int right = _level(it->_rightChild);
		return left > right ? left + 1 : right + 1;  // 加1是加上当前节点
	}

	int _number(Node* it)
	{
		if (it == nullptr)
		{
			return 0;
		}
		int left = _number(it->_leftChild);
		int right = _number(it->_rightChild);
		return left + right + 1;  // 加1是加上当前节点
	}



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

	int arr[] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
	BinarySearchTree<int> bst2;
	for (int i = 0; i < 11; i++)
	{
		bst2.insert(arr[i]);
	}

	bst2.foreachPreorder();
	bst2.foreachInorder();
	bst2.foreachPostorder();
	bst2.foreachSequence();

	cout << "---------------------------" << endl;
	BinarySearchTree<int> bst3;
	for (int i = 0; i < 11; i++)
	{
		bst3.insertRecursion(arr[i]);
	}
	cout << "pdchelloworld" << endl;
	bst3.foreachPreorder();

	cout << "\n树的层数: " << bst2.level() << endl;
	cout << "\n树的节点个数: " << bst2.number() << endl;

	bst2.removeRecursion(58);
	bst2.remove(78);
	bst2.remove(24);

	cout << "---------------------------" << endl;
	bst2.foreachPreorder();
	cout << "---------------------------" << endl;
	cout << "5是否存在: " << bst2.find(5) << endl;
	cout << "24是否存在: " << bst2.find(24) << endl;

	cout << "---------------------------" << endl;
	cout << "5是否存在: " << bst3.findRecursion(5) << endl;
	cout << "26是否存在: " << bst3.findRecursion(26) << endl;
	bst3.remove(5);
	bst3.insertRecursion(26);
	cout << "5是否存在: " << bst3.findRecursion(5) << endl;
	cout << "26是否存在: " << bst3.findRecursion(26) << endl;

	return 0;
}