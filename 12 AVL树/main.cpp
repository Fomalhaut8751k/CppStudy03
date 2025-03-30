#include<iostream>
#include<queue>
#include<stack>
#include<cmath>

using namespace std;

/*
	二叉搜索平衡树：BST树+结点平衡操作(平衡：任意结点左右子树的高度差不超过1)
	AVL树为了维护结点平衡引入的四种结点旋转操作

	结点失衡的原因：
	1. 左孩子的左子树太高了(右旋转操作)
				  40(失衡节点)
			 30
		  20    35
	  向右旋转
			 30
		 20      40
			   35
		操作：a) 30成为根结点，记录30的右子树
			  b) 30原本的右子树放到40的左节点上
			  c) 40成为30的右节点

	2. 右孩子的右子树太高了(左旋转操作)
		  40(失衡节点)
			  50
			45    60
		向左旋转
			  50
		  40      60
			45
		操作：a) 50变为根节点
			  b) 50原来的左子树挂在40的右节点上
			  c) 40成为50的左节点

	3. 左孩子的右子树太高了(左-右旋转，左平衡操作)
			40(失衡节点)
		20
		  30
	   先处理成情况1
	   以20为根结点进行【左旋】
			40
		  30
		20
	   操作：a) 30变为"根节点"，变成40的左孩子
			 b) 30的左子树挂在20的右节点上，但是30没有左子树，所以不管
			 c) 20成为30的左节点
	   然后执行情况1的右旋

	4. 右孩子的左子树太高了(右-左旋转，右平衡操作)
			40(失衡节点)
				 60
			  50
	   先处理成情况2
	   以60为根结点进行【右旋】

	   操作：a) 50变成"根节点"，变成40的右孩子
			 b) 60的右子树挂在50的左节点上，但是60没有右子树，所以不管
			 c) 60变成50的右节点
	   然后执行情况2的左旋
*/

// Adelson-Velsky-Landis Tree
class AVL
{
public:
	AVL():_root(nullptr) {}
	// 插入
	void insert(int val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return;
		}
		_root = _insert(_root, val);
	}

	// 删除
	void remove(int val)
	{
		if (_root == nullptr)
		{
			return;
		}
		_root = _remove(_root, val);
	}

	// 前序遍历
	void preorder()
	{
		cout << "前序遍历: ";
		_preorder(_root);
		cout << endl;
	}

	// 中序遍历
	void inorder()
	{
		cout << "中序遍历: ";
		_inorder(_root);
		cout << endl;
	}

	// 后序遍历
	void postorder()
	{
		cout << "后序遍历: ";
		_postorder(_root);
		cout << endl;
	}

	// 层序遍历(非递归版)
	void levelorder()
	{
		queue<Node*> que;
		Node* it = _root;
		que.push(it);

		cout << "层序遍历: ";
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

// ###### AVL的核心——左旋右旋，左平衡右平衡 ################################################
	// 左旋转操作
	Node* leftRotate(Node* it) // 右孩子的右子树太高了
	{
		// 结点旋转
		Node* right_root = it->_rightChild;  // 右子树的根结点
		it->_rightChild = right_root->_leftChild;  // 把当前"根"结点的左子树挂在it的右边
		right_root->_leftChild = it;  // 把it挂在当前"根"结点的左边

		// 高度更新
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
		right_root->_height = max(nodeHeight(right_root->_leftChild), it->_height) + 1;

		return right_root;
	}

	// 右旋转操作
	Node* rightRotate(Node* it) // 左孩子的左子树太高了
	{	
		// 结点旋转
		Node* left_root = it->_leftChild;  // 左子树的根结点
		it->_leftChild = left_root->_rightChild;  // 把当前"根"结点的右子树挂在it的左边
		left_root->_rightChild = it;  // 把it挂在当前"根"结点的右边


		// 高度更新
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
		left_root->_height = max(nodeHeight(left_root->_leftChild), it->_height) + 1;

		return left_root;
	}

	// 左平衡操作
	Node* leftBalance(Node* it)  // 左孩子的右子树太高了
	{
		it->_leftChild = leftRotate(it->_leftChild);  // 以左孩子为根结点进行左旋
		return rightRotate(it);  // 变成右旋转的情况，执行右旋
	}

	// 右平衡操作
	Node* rightBalance(Node* it)  // 右孩子的左子树太高了
	{
		it->_rightChild = rightRotate(it->_rightChild);  // 以右孩子为根结点进行右旋
		return leftRotate(it);  // 变成左旋转的情况，执行左旋
	}
// ############################################################################################

	Node* _insert(Node* it, int val)  // 要更新节点的高度
	{
		if (it == nullptr)
			return new Node(val); 
		
		if (val < it->_nodeVal)
		{
			// 如果是叶子节点，那么它递归的时候，it==nullptr，返回一个创建的新结点
			// 并连接到叶子结点的左/右子树上
			it->_leftChild = _insert(it->_leftChild, val);
			// 添加了左子树的节点，如果失衡，那肯定是左子树高度大于右子树
			if (nodeHeight(it->_leftChild) - nodeHeight(it->_rightChild) > 1)
			{
				if (nodeHeight(it->_leftChild->_leftChild) >=
					nodeHeight(it->_leftChild->_rightChild))
				{	// 节点失衡由左孩子的左子树太高导致
					it = rightRotate(it);
				}
				else
				{   // 节点失衡由左孩子的右子树太高导致
					it = leftBalance(it);
				}
			}
		}
		else if (val > it->_nodeVal)
		{
			it->_rightChild = _insert(it->_rightChild, val);
			// 添加了右子树的节点，如果失衡，那肯定是左子树高度小于右子树
			if (nodeHeight(it->_rightChild) - nodeHeight(it->_leftChild) > 1)
			{
				if (nodeHeight(it->_rightChild->_rightChild) >=
					nodeHeight(it->_rightChild->_rightChild))
				{	// 节点失衡由右孩子的右子树太高导致
					it = leftRotate(it);
				}
				else
				{   // 节点失衡由右孩子的左子树太高导致
					it = rightBalance(it);
				}
			}
		}
		it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;

		return it;  // 回溯时等效于it->_leftChild = it->_leftChild，没有什么效果
	}

	Node* _remove(Node* it, int val)
	{
		if (it == nullptr)
			return nullptr;
		// 判断
		if (val < it->_nodeVal)
		{
			it->_leftChild = _remove(it->_leftChild, val);
			// 删除了左子树的节点，如果失衡，那肯定是右子树高度大于左子树
			if (nodeHeight(it->_leftChild) - nodeHeight(it->_rightChild) < -1)
			{
				if (nodeHeight(it->_rightChild->_leftChild) <=
					nodeHeight(it->_rightChild->_rightChild))
				{	// 节点失衡由右孩子的右子树太高导致
					it = leftRotate(it);
				}
				else
				{   // 节点失衡由右孩子的左子树太高导致
					it = rightBalance(it);
				}
			}
		}
		else if (val > it->_nodeVal)
		{
			it->_rightChild = _remove(it->_rightChild, val);
			// 删除了右子树的节点，如果失衡，那肯定是左子树高度大于右子树
			if (nodeHeight(it->_rightChild) - nodeHeight(it->_leftChild) < -1)
			{
				if (nodeHeight(it->_leftChild->_rightChild) <=
					nodeHeight(it->_leftChild->_leftChild))
				{	// 节点失衡由左孩子的左子树太高导致
					it = rightRotate(it);
				}
				else
				{   // 节点失衡由左孩子的右子树太高导致
					it = leftBalance(it);
				}
			}
		}
		else  // 找到了待删除节点
		{
			// 如果待删除节点没有左右子树
			if (it->_leftChild == nullptr && it->_rightChild == nullptr)
			{
				delete it;
				return nullptr;
			}
			// 如果待删除节点有左和右子树
			//else if (it->_leftChild != nullptr && it->_rightChild != nullptr)
			//{	// 去找前驱结点
			//	Node* front = it->_leftChild;
			//	Node* back_front = it;
			//
			//	while (front->_rightChild != nullptr)
			//	{
			//		back_front = front;  // 跟踪front的父节点
			//		front = front->_rightChild;
			//	}
			//		
			//	// 把待删除节点替换为前驱节点
			//	it->_nodeVal = front->_nodeVal; 
			//	
			//	// 删除前驱节点，和下面的情况一样
			//	Node* front_left = front->_leftChild;
			//	delete front;
			//	back_front->_rightChild = front_left;
			//
			//	// 更新it到front结点的高度，front下面子树的高度不受影响
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
			//		// 从it开始一路找下来找到front都是向右的
			//		Node* itp = st.top();
			//		itp->_height = max(nodeHeight(itp->_leftChild), its->_height) + 1;
			//		its = st.top();
			//		st.pop();
			//	}
			//	it->_height = max(nodeHeight(it->_leftChild), nodeHeight(it->_rightChild)) + 1;
			//	return it;
			//}
			else if (it->_leftChild != nullptr && it->_rightChild != nullptr)
			{   // 为了避免删除前驱或者后继节点造成节点失衡，谁高删除谁
				if (nodeHeight(it->_leftChild) >= nodeHeight(it->_rightChild))
				{   // 删前驱
					Node* pre = it->_leftChild;
					while (pre->_rightChild != nullptr)
						pre = pre->_rightChild;
					it->_nodeVal = pre->_nodeVal;
					// 依然通过递归来删除前驱结点
					it->_leftChild = _remove(it->_leftChild, pre->_nodeVal);
				}
				else
				{   // 删后继
					Node* post = it->_rightChild;
					while (post->_leftChild != nullptr)
						post = post->_leftChild;
					it->_nodeVal = post->_nodeVal;
					// 依然通过递归来删除后继结点
					it->_rightChild = _remove(it->_rightChild, post->_nodeVal);
				}
			}
			// 如果待删除节点有左或右子树
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