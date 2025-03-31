#include<iostream>

using namespace std;

/*  红黑树的五个性质
	1. 每一个节点都是有颜色的，不是黑色，就是红色
	2. nullptr是黑色的，即叶子节点的"左右子节点"nullptr是黑色的
	3. root结点必须是黑色的
	4. 不能出现连续的红色节点
	5. 从根节点开始，到任意一个叶子结点的路径上，黑色结点的数量必须是一致的
*/

template<typename T>
class RedBlackTree
{
public:
	RedBlackTree() :_root(nullptr) {};

	// 插入
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
		bool _nodeColor;  // 1表示红，0表示黑
		Node* _leftChild;
		Node* _rightChild;  
		Node* _parentChild;  // 父节点
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
	
	// 左旋
	Node* leftRotate(Node* it)
	{
		Node* it_right = it->_rightChild;  // 记录其右孩子
		it->_rightChild = it_right->_leftChild;  // 把右孩子的左子树挂到根的右边
		it_right->_leftChild = it;  // 把根挂到右孩子的左边，右孩子成为新的根
		return it_right;
	}

	// 右旋
	Node* rightRotate(Node* it)
	{
		Node* it_left = it->_leftChild;  // 记录其左孩子
		it->_leftChild = it_left->_rightChild;  // 把左孩子的右子树挂到根的左边
		it_left->_rightChild = it;  // 把根挂到左孩子的右边，左孩子成为新的根
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