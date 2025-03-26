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

	// 是否是BST树的判断
	bool isBinarySearchTree()
	{
		// 依然是中序遍历，在中序遍历中，如果当前的值小于前面的值，那就不是BST树
		Node* node = nullptr;
		return _isBinarySearchTree(_root, node);
	}

	// 是否是子树的判断
	bool isChildTree(BinarySearchTree<T,Compare>& bst)
	{
		// 先找bst的根结点
		Node* it = _root;
		while (it != nullptr)
		{
			if (comp(it->_nodeVal, bst._root->_nodeVal))  // 大于
			{
				it = it->_rightChild;
			}
			else if (comp(bst._root->_nodeVal, it->_nodeVal)) // 小于
			{
				it = it->_leftChild;
			}
			else  // 找到了根结点
			{
				// 让当前树跟着bst遍历
				return _isChildTree(it, bst._root);
			}
		}
		return false;  // 连根结点都没找到，肯定不是
	}

	// 最近公共祖先
	int getLowestCommonAncestor(int L, int R)
	{
		// 先判断是否在树上
		if (find(L) && find(R))
		{
			return _getLowestCommonAncestor(_root, L, R);
		}
		else
		{
			//throw "L和R没有公共祖先";
			cout << "L和R没有公共祖先" << endl;
			return -1;
		}
	}

	// 镜像翻转
	void mirrorInverse()
	{
		// 前序遍历
		_mirrorInverse(_root);
	}

	// 镜像对称判断
	bool mirrorSymmetry()
	{
		return _mirrorSymmetry(_root, _root);
	}

	// 由前序遍历和中序遍历复原二叉树
	void restoreByPreorderandInOrder(int pre[], int i, int j, int in[], int m, int n)
	{
		_root = _restoreByPreorderandInOrder(pre, i, j, in, m, n);

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

	bool _isBinarySearchTree(Node* it, Node* &pre)
	{
		// 原理还是中序遍历，要求严格递增(因为没有重复的)
		// 判断到不是递增的就返回false
		if (it == nullptr)  
		{
			return true;
		}
		if (!_isBinarySearchTree(it->_leftChild, pre))
		{
			return false;
		}
		if (pre != nullptr)  // pre判断是否为空，是避免第一个结点时没有pre
		{
			if (comp(it->_nodeVal, pre->_nodeVal))
			{
				return false;
			}
		}
		pre = it; // 更新前一个结点
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
		// 创建当前子树的根结点
		Node* node = new Node(pre[i]);  // 拿前序的第一个数字创建子树根结点
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k])  // 在中序遍历中找子树根节点下标k
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

// 创建一棵一般二叉树
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
	// 中序遍历: 20 40 30 60 80
	// 显然，不符合BST树中序遍历的性质

	cout << "bst3是否是二分查找树: " << bst.isBinarySearchTree() << endl;
}


// 子树判断问题
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

	cout << "是否是子树: " << bst1.isChildTree(bst) << endl;

	node_2->_leftChild = node_3;

	cout << "是否是子树: " << bst1.isChildTree(bst) << endl;
}

// 镜像对称问题
void test03()
{
	using Node = BinarySearchTree<int>::Node;
	BinarySearchTree<int> bst;

	bst._root = new Node(67);
	Node* node_1 = new Node(31);
	Node* node_2 = new Node(31);

	bst._root->_leftChild = node_1;
	bst._root->_rightChild = node_2;

	cout << "\n是否镜像对称: " << bst.mirrorSymmetry() << endl;

	Node* node_3 = new Node(30);
	node_2->_leftChild = node_3;

	cout << "插入元素后，是否镜像对称: " << bst.mirrorSymmetry() << endl;

	Node* node_4 = new Node(30);
	node_1->_rightChild = node_4;

	cout << "对称补充相同元素后，是否镜像对称: " << bst.mirrorSymmetry() << endl;

	Node* node_5 = new Node(12);
	Node* node_6 = new Node(17);
	node_1->_leftChild = node_5;
	node_2->_rightChild = node_6;

	cout << "对称插入不同元素后，是否镜像对称: " << bst.mirrorSymmetry() << endl;
}

// 由前序遍历和中序遍历复原二叉树
/*
	并不需要创建成全局变量，一样可以定义成类函数，然后初始化后调用
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
	// 最小区间长度为1，则创建节点
	if (L == R)
		return new BinarySearchTree<int>::Node(_preOrder[idxPre]);
	

	// 寻找前序遍历中节点在中序遍历中对应的位置
	int idxIn = L;
	for (; idxIn < R; idxIn++)
	{
		if (_inOrder[idxIn] == _preOrder[idxPre])
			break;
	}

	it = new BinarySearchTree<int>::Node(_preOrder[idxPre]);

	// 递归
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

// ####### 1.插入，查找，删除 #####################################################
	for(int i = 0; i < 11; ++i)
	{
		// 非递归插入
		bst1.insert(arr[i]);
		// 递归插入
		bst2.insertRecursion(arr[i]);
	}
	bst1.foreachPreorder();
	bst2.foreachInorder();
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

		特点：每一个结点都满足，值：左<结点<右，这个特点来判断只能判断局部
		如下面的情况就不是一个bst树，但是符合性质
			 60
		20         80
				30     110
	*/
	cout << "\n";
	cout << "bst1是否是二分查找树: " << bst1.isBinarySearchTree() << endl;
	cout << "bst2是否是二分查找树: " << bst2.isBinarySearchTree() << endl;
	test01();

// ###### 6. 二叉树求子树问题 ######################################################
	cout << "\n";
	test02();

// ###### 7. 最近公共祖先 ##########################################################
	/*                        58 
				 24                       64		
	        0         34            62          69
			   5		  41	                    78
	*/   
	cout << "\n" << bst1.getLowestCommonAncestor(5, 41) << endl; // 应该是24
	cout << bst2.getLowestCommonAncestor(62, 64) << endl; // 应该是64
	bst1.getLowestCommonAncestor(12, 3);  // 没有公共祖先

// ###### 8. 镜像翻转 ##############################################################
	cout << "\n镜像翻转前的";
	bst2.foreachInorder();
	bst2.mirrorInverse();
	cout << "镜像翻转后的";
	bst2.foreachInorder();


// ###### 9. 镜像对称判断 ##########################################################
	test03();

// ###### 10. 已知二叉树的前序遍历和中序遍历，重建二叉树 ###########################
	int preorder[11] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78 };
	int inorder[11] = { 0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78 };
	cout << "\n我的方法: ";
	test04(preorder, inorder);
	cout << "\n视频的方法: " << endl;
	BinarySearchTree<int> bst3;
	bst3.restoreByPreorderandInOrder(preorder, 0, 10, inorder, 0, 10);
	bst3.foreachPreorder();
	bst3.foreachInorder();

	return 0;
}