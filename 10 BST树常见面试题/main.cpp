#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template<typename T, typename Compare = less<T>>
class BinarySearchTree
{
public:
	// 默认构造
	BinarySearchTree()
		:_root(nullptr) {}

	struct Node;

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
				if (comp(it->_nodeVal, val))
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
				else if (comp(val, it->_nodeVal))// 如果插入值更小，那应该往左下找
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
	}

	// 插入(递归)
	void insertRecursion(const T& val)
	{
		_root = _insertRecursion(_root, val);
	}

	// 删除(非递归)
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
				else if (it->_leftChild == nullptr && it->_rightChild == nullptr)
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

	// 区间查询
	void findRange(vector<T>& vec, int left, int right)
	{
		_findRange(_root, vec, left, right);
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
		return left + right + 1;
	}

	void _findRange(Node* it, vector<T>& vec, int _left, int _right)
	{
		if (it != nullptr)
		{
			// 如果当前节点的值小于左边界，则其左子树的所有结点都小于左边界，无需遍历
			if (it->_nodeVal >= _left)
				_findRange(it->_leftChild, vec, _left, _right);
			
			// 中序遍历具有从小到大的性质
			if (it->_nodeVal >= _left && it->_nodeVal <= _right)
			{
				vec.push_back(it->_nodeVal);
			}

			// 如果当前节点的值大于右边界，则其右子树的所有结点都大于右边界，无需遍历
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

// ####### 1.插入，查找，删除 #####################################################
	for(int i = 0; i < 11; ++i)
	{
		// 非递归插入
		bst1.insert(arr[i]);
		// 递归插入
		bst2.insertRecursion(arr[i]);
	}
	bst1.foreachPostorder();
	bst2.foreachPostorder();
	// 非递归查找
	cout << "\nbst1是否存在67: " << bst1.find(67) << endl;
	cout << "bst1是否存在5003: " << bst1.find(5003) << endl;
	// 递归查找
	cout << "bst2是否存在67: " << bst2.findRecursion(67) << endl;
	cout << "bst2是否存在5003: " << bst2.findRecursion(5003) << endl;
	
	// 非递归删除
	bst1.remove(67);
	cout << "\n已从bst1中删除67" << endl;
	cout << "bst1是否存在67: " << bst1.find(67) << endl;
	// 递归删除
	bst2.removeRecursion(67);
	cout << "\n已从bst2中删除67" << endl;
	cout << "bst2是否存在67: " << bst2.findRecursion(67) << "\n" << endl;
	
// ####### 2. 前中后序遍历和层序遍历 ###############################################
	// 前序遍历
	bst2.foreachPreorder();
	// 中序遍历
	bst1.foreachInorder();
	// 后序遍历
	bst2.foreachPostorder();
	// 层序遍历
	bst1.foreachSequence();

// ###### 3. 树的高度，结点元素个数 ################################################
	// 树的高度
	cout << "\nbst1的高度为: " << bst1.level() << endl;
	cout << "bst2的高度为: " << bst2.level() << endl;
	// 树的元素个数
	cout << "\nbst1的元素个数为: " << bst1.number() << endl;
	cout << "bst2的元素个数为: " << bst2.number() << endl;

// ###### 4. 区间元素查找 ##########################################################
	/*
		利用中序遍历是升序的的特点
	*/
	vector<int> vec1;
	bst1.findRange(vec1, 10, 70);
	cout << "\nbst1中介于区间[10, 70]的元素有: ";
	for_each(vec1.begin(), vec1.end(), [](int num)->void {cout << num << " "; });
	cout << endl;

	vec1.clear();
	bst2.findRange(vec1, 10, 69);
	cout << "bst1中介于区间[10, 69]的元素有: ";
	for (auto item : vec1) { cout << item << " "; }
	cout << endl;

// ###### 5. 判断一棵二叉树是不是BST树 #############################################
	/*
		BST树
		1. 空树
		2. 不是空树
			a. 若左子树不为空，则左子树上所有结点的值均小于它的根结点的值
			b. 若右子树不为空，则右子树上所有结点的值均大于它的根结点的值
			c. 左右子树也分别满足二叉搜索树性质

			 60
		20         80
				30     110
	*/

	return 0;
}