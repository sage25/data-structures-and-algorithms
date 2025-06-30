#include<iostream>
#include<functional>
#include<stack>
#include<queue>
#include<vector>
#include<math.h>
using namespace std;


template<class T, class Comp = less<T>>
class BSTree
{
private:
	//节点定义
	struct Node
	{
		Node(T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{ }
		T data_;
		Node* left_;
		Node* right_;
	};
	//根节点
	Node* root_;
	//比较对象
	Comp comp_;
public:
	BSTree(Comp comp=Comp())
		: root_(nullptr)
		, comp_(comp)
	{ }
	~BSTree()
	{
		destroy(root_);
	}
	//非递归插入
	void n_insert(const T& data)
	{
		Node* node = new Node(data);
		if (root_ == nullptr)
		{
			root_ = node;
			return;
		}
		Node* cur = root_;
		Node* parent = nullptr;
		while (cur)
		{
			if (data == cur->data_)
			{
				cout << "Node exist!" << endl;
				delete node;
				return;
			}
			else if (comp_(data, cur->data_))
			{
				parent = cur;
				cur = cur->left_;
			}
			else
			{
				parent = cur;
				cur = cur->right_;
			}
		}
		if (comp_(data, parent->data_))
		{
			parent->left_ = node;
		}
		else
		{
			parent->right_ = node;
		}
	}
	//递归插入
	void insert(const T& data)
	{
		root_ = insert(data, root_);
	}
	//非递归删除
	void n_remove(const T& data)
	{
		if (root_ == nullptr)
		{
			return;
		}
		Node* cur = root_;
		Node* parent = nullptr;
		//寻找要删除的节点
		while (cur)
		{
			if (cur->data_ == data)
			{
				break;
			}
			else if (comp_(data, cur->data_))
			{
				parent = cur;
				cur = cur->left_;
			}
			else
			{
				parent = cur;
				cur = cur->right_;
			}	
		}
		//没找到
		if (cur == nullptr)
		{
			cout << "Node dose not exist!";
			return;
		}
		//处理要删除节点有两个子节点情况(前驱节点覆盖)
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		
		//child指向要删除的节点的孩子节点
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}
		//统一处理没有子节点或者一个子节点
		if (parent == nullptr)	//删除的节点为根节点
		{
			root_ = child;
		}
		else
		{
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		delete cur;
	}
	//递归删除
	void remove(const T& data)
	{
		root_ = remove(data, root_);
	}
	//非递归查找
	bool n_query(const T& data)
	{
		Node* cur = root_;
		while (cur)
		{
			if (cur->data_ == data)
			{
				return true;
			}
			else if (comp_(data, cur->data_))
			{
				cur = cur->left_;
			}
			else
			{
				cur = cur->right_;
			}
		}
		return false;
	}
	//递归查找
	bool query(const T& data)
	{
		return query(data, root_) != nullptr;
	}
	//非递归前序遍历
	void n_preOrder()
	{
		cout << "[非递归]前序遍历：";
		if (root_ == nullptr)
			return;
		stack<Node*> s;
		s.push(root_);
		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->data_ << ' ';
			s.pop();

			if (top->right_ != nullptr)
				s.push(top->right_);
			if (top->left_ != nullptr)
				s.push(top->left_);
		}
		cout << endl;
	}
	//递归前序遍历
	void preOrder()
	{
		cout << "[递归]前序遍历：";
		preOrder(root_);
		cout << endl;
	}
	//非递归中序遍历
	void n_inOrder()
	{
		cout << "[非递归]中序遍历：";
		if (root_ == nullptr)
			return;
		stack<Node*> s;
		Node* cur = root_;
		while (!s.empty() || cur != nullptr)
		{
			if (cur != nullptr)
			{
				while (cur != nullptr)
				{
					s.push(cur);
					cur = cur->left_;
				}
			}
			else
			{
				Node* top = s.top();
				s.pop();
				cout << top->data_ << ' ';
				cur = top->right_;
			}
		}
		cout << endl;
	}
	//递归中序遍历
	void inOrder()
	{
		cout << "[递归]中序遍历：";
		inOrder(root_);
		cout << endl;
	}
	//非递归后序遍历
	void n_postOrder()
	{
		cout << "[非递归]后序遍历：";
		if (root_ == nullptr)
			return;
		stack<Node*> s1;
		stack<Node*> s2;
		Node* cur = root_;
		s1.push(cur);
		while (!s1.empty())	//vrl
		{
			Node* top = s1.top();
			s1.pop();
			s2.push(top);
			if (top->left_ != nullptr)
				s1.push(top->left_);
			if (top->right_ != nullptr)
				s1.push(top->right_);
		}
		while(!s2.empty())
		{
			cout << s2.top()->data_ << ' ';
			s2.pop();
		}
		cout << endl;
	}
	//递归后序遍历
	void postOrder()
	{
		cout << "[递归]后序遍历：";
		postOrder(root_);
		cout << endl;
	}
	//非递归层序遍历
	void n_levelOrder()
	{
		if (root_ == nullptr)
			return;
		cout << "[非递归]层序遍历：";
		queue<Node*> q;
		q.push(root_);
		while (!q.empty())
		{
			Node* front = q.front();
			q.pop();
			cout << front->data_ << ' ';
			if (front->left_ != nullptr)
				q.push(front->left_);
			if (front->right_ != nullptr)
				q.push(front->right_);
		}
		cout << endl;
	}
	//递归层序遍历
	void levelOrder()
	{
		cout << "[递归]层序遍历：";
		int h = high();
		for (int i = 0; i < h; i++)
		{
			levelOrder(root_, i);
		}
		cout << endl;
	}
	//递归求层数
	int high()
	{
		return high(root_);
	}
	//递归求节点个数
	int number()
	{
		return number(root_);
	}
	//求满足区间[i, j]之间的元素
	void findValues(vector<T>& vec, const T& i, const T& j)
	{
		if (root_ == nullptr)
			return;
		findValues(root_, vec, i, j);
	}
	//判断二叉树是否BST树
	bool isBSTree()
	{
		Node* cur = nullptr;
		return isBSTree(root_, cur);
	}
	//判断子树问题
	bool isChildBSTree(BSTree<T, Comp>& child)
	{
		if (child.root_ == nullptr)
		{
			return true;
		}
		Node* cur = root_;
		//找子树的根节点
		while (cur != nullptr)
		{
			//找到了
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp_(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		if (cur == nullptr)		//找不到
		{
			return false;
		}
		return isChildBSTree(cur, child.root_);
	}
	//LCA问题
	Node* getLCA(const T& val1, const T& val2)
	{
		if (root_ == nullptr)
		{
			return nullptr;
		}
		return getLCA(root_, val1, val2);
	}
	//镜像反转问题
	void mirror01()
	{
		root_ = mirror01(root_);
	}
	//镜像对称问题
	bool mirror02()
	{
		if (root_ == nullptr)
		{
			return true;
		}
		return mirror02(root_->left_, root_->right_);
	}
	//已知前序中序重建树
	void rebuild(T pre[], int i, int j, T in[], int m, int n)
	{
		root_ = rebuild(root_, pre, i, j, in, m, n);
	}
	//判断是否平衡树
	bool isBalance()
	{
		bool flag = true;
		int l = 0;
		isBalance(root_, l, flag);
		return flag;
	}
	//中序遍历倒数第k个节点
	T& getVal(int k)
	{
		int i = 1;
		return getVal(root_, k)->data_;
	}
private:
	//用于测试
	friend void test1();
	friend void test4();
	//递归析构实现
	void destroy(Node* node)
	{
		if (node == nullptr)
			return;
		if (node->left_ != nullptr)
			destroy(node->left_);
		if (node->right_ != nullptr)
			destroy(node->right_);
		delete node;
	}
	//递归前序实现
	void preOrder(Node* node)
	{
		if (node == nullptr)
			return;
		cout << node->data_ << ' ';
		preOrder(node->left_);
		preOrder(node->right_);
	}
	//递归中序实现
	void inOrder(Node* node)
	{
		if (node == nullptr)
			return;
		inOrder(node->left_);
		cout << node->data_ << ' ';
		inOrder(node->right_);
	}
	//递归后序实现
	void postOrder(Node* node)
	{
		if (node == nullptr)
			return;
		postOrder(node->left_);
		postOrder(node->right_);
		cout << node->data_ << ' ';
	}
	//递归求层数实现
	int high(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = 1 + high(node->left_);
		int right = 1 + high(node->right_);
		return left > right ? left : right;
	}
	//递归求节点个数实现
	int number(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = number(node->left_);
		int right = number(node->right_);
		return 1 + right + left;
	}
	//递归层序实现
	void levelOrder(Node* node, int i)
	{
		if (i == 0)
		{
			cout << node->data_ << ' ';
			return;
		}
		if(node->left_ != nullptr)
			levelOrder(node->left_, i - 1);
		if (node->right_ != nullptr)
			levelOrder(node->right_, i - 1);
	}
	//递归插入实现
	Node* insert(const T& data, Node* node)
	{
		if (node == nullptr)
		{
			return new Node(data);
		}
		if (data == node->data_)
			;
		else if (comp_(data, node->data_))
			node->left_ = insert(data, node->left_);
		else
			node->right_ = insert(data, node->right_);
		return node;

	}
	//递归查找实现
	Node* query(const T& data, Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (data == node->data_)
			return node;
		else if (comp_(data, node->data_))
			return query(data, node->left_);
		else
			return query(data, node->right_);
	}
	//递归删除实现
	Node* remove(const T& data, Node* node)
	{
		if (node == nullptr)
		{
			cout << "Node dose not exist!" << endl;
			return nullptr;
		}
		if (data == node->data_)
		{
			//处理要删除节点有两个子节点情况(前驱节点覆盖)
			if (node->left_ != nullptr
				&& node->right_ != nullptr)
			{
				Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				node->left_ = remove(pre->data_, node->left_);
				return node;
			}
			//统一处理没有子节点或者一个子节点
			else
			{
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (node->right_ != nullptr)
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
				else
				{
					delete node;
					return nullptr;
				}
			}
		}
		else if (comp_(data, node->data_))
			node->left_ = remove(data, node->left_);
		else
			node->right_ = remove(data, node->right_);
		return node;
	}
	//求满足区间[i, j]之间的元素实现
	void findValues(Node* node, vector<T>& vec, const T& i, const T& j)
	{
		if (node == nullptr)
		{
			return;
		}
		if (node->data_ > i)
		{
			findValues(node->left_, vec, i, j);
		}
		if (i <= node->data_ && node->data_ <= j)
		{
			vec.push_back(node->data_);
		}
		if (node->data_ < j)
		{
			findValues(node->right_, vec, i, j);
		}
	}
	//判断二叉树是否BST树实现
	bool isBSTree(Node* node, Node*& pre)
	{
		if (node == nullptr)
		{
			return true;
		}
		if (!isBSTree(node->left_, pre))
		{
			return false;
		}
		if (pre != nullptr)
		{
			if (comp_(node->data_, pre->data_))
			{
				return false;
			}
		}
		pre = node;
		return isBSTree(node->right_ ,pre);
	}
	//判断是否子树问题实现
	bool isChildBSTree(Node* f, Node* c)
	{
		if ((f == nullptr && c == nullptr)
			|| c == nullptr)
		{
			return true;
		}
		if ((f == nullptr && c != nullptr) 
			|| (f->data_ != c->data_))
		{
			return false;
		}
		return isChildBSTree(f->right_, c->right_)
			&& isChildBSTree(f->left_, c->left_);
	}
	//LCA问题实现
	Node* getLCA(Node* node, const T& val1, const T& val2)
	{
		T max = val1 > val2 ? val1 : val2;
		T min = val1 < val2 ? val1 : val2;
		if ((comp_(node->data_, max) && 
			!comp_(node->data_, min)) 
			|| node->data_ == max)
		{
			return node;
		}
		else if (node->data_ > max)
		{
			return getLCA(node->left_, val1, val2);
		}
		else
		{
			return getLCA(node->right_, val1, val2);
		}
	}
	//镜像反转问题实现
	Node* mirror01(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		Node* cur = node->right_;
		node->right_ = mirror01(node->left_);
		node->left_ = mirror01(cur);
		return node;
	}
	//镜像对称问题实现
	bool mirror02(Node* l, Node* r)
	{
		if (l == nullptr && r == nullptr)
		{
			return true;
		}
		if((l == nullptr && r != nullptr)
			|| (l != nullptr && r == nullptr)
			|| l->data_ != r->data_)
		{
			return false;
		}
		return mirror02(l->right_, r->left_)
			&& mirror02(l->left_, r->right_);
	}
	//已知前序中序重建树实现
	Node* rebuild(Node* node, T pre[], int i, int j, T in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}
		node = new Node (pre[i]);
		int pos = 0;
		for (; pre[i] != in[pos]; pos++);
		node->left_ = rebuild(node->left_, pre, i + 1, i + (pos - m), in, m, pos - 1);
		node->right_ = rebuild(node->right_, pre, i + (pos - m) + 1, j, in, pos + 1, n);
		return node;
	}
	//判断是否平衡树实现
	int isBalance(Node* node, int l, bool& flag)
	{
		int left = l;
		int right = l;
		if (!flag)
		{
			return -1;
		}
		if (node->left_ != nullptr)
		{
			left = isBalance(node->left_, l + 1, flag);
		}
		if (node->right_ != nullptr)
		{
			right = isBalance(node->right_, l + 1, flag);
		}
		if (abs(left - right) > 1)
		{
			flag = false;
		}
		return left > right ? left : right;
	}
	////中序遍历倒数第k个节点实现
	int i = 1;
	Node* getVal(Node* node, int k)
	{
		//LVR -> RVL
		if (node == nullptr)
		{
			return nullptr;
		}
		Node* left = getVal(node->right_, k);
		if (left != nullptr)
		{
			return left;
		}
		if (k == i++)
		{
			return node;                   
		}
		return getVal(node->left_, k);
	}
};

void test1()
{
	using Node =BSTree<int>::Node;
	BSTree<int> bst;
	Node* n1 = new BSTree<int>::Node(50);
	Node* n2 = new BSTree<int>::Node(30);
	Node* n3 = new BSTree<int>::Node(80);
	Node* n4 = new BSTree<int>::Node(20);
	Node* n5 = new BSTree<int>::Node(99);
	bst.root_ = n1;			//		50
	n1->left_ = n2;			//	   /  \ 
	n1->right_ = n3;		//    30   80
	n3->left_ = n4;         //        /  \ 
	n3->right_ = n5;		//       20  99
	cout << bst.isBSTree();
}
void test2(BSTree<int>& bst)
{
	BSTree<int> bst1;	//		     58
	bst1.insert(58);	//			  \ 
	bst1.insert(67);	//			  67
	bst1.insert(62);	//			 /	\ 
	bst1.insert(69);	//          62  69
	cout << bst.isChildBSTree(bst1);
}
void test3()
{
	int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	BSTree<int> bst;
	for (int i = 0; i < 11; i++)
	{
		bst.insert(arr[i]);
	}
	cout << bst.getLCA(34,69)->data_ << endl;
}
void test4()
{
	using Node = BSTree<int>::Node;
	BSTree<int> bst;
	Node* n1 = new BSTree<int>::Node(50);
	Node* n2 = new BSTree<int>::Node(70);
	Node* n3 = new BSTree<int>::Node(70);
	Node* n4 = new BSTree<int>::Node(42);
	Node* n5 = new BSTree<int>::Node(42);
	Node* n6 = new BSTree<int>::Node(14);
	Node* n7 = new BSTree<int>::Node(14);
	Node* n8 = new BSTree<int>::Node(23);
	Node* n9 = new BSTree<int>::Node(23);
	bst.root_ = n1;
	n1->left_ = n2;
	n1->right_ = n3;
	n2->left_ = n4;
	n3->right_ = n5;
	n2->right_ = n6;
	n3->left_ = n7;
	n4->right_ = n8;
	n5->left_ = n9;
	cout << bst.mirror02() << endl;
}
void test5()
{
	BSTree<int> bst;
	int pre[] = { 58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78 };
	int in[] = { 0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78 };
	bst.rebuild(pre, 0, 10, in, 0, 10);
	bst.preOrder();
	bst.inOrder();
	bst.postOrder();
}



int main()
{
	int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	BSTree<int> bst;
	for (int i = 0; i < 11; i++)
	{
		//bst.n_insert(arr[i]);
		bst.insert(arr[i]);
	}
	//bst.n_remove(5);
	//bst.n_remove(67);
	//bst.n_remove(58);
	//bst.remove(5);
	//bst.remove(67);
	//bst.remove(58);
	//bst.remove(34);
	//cout << bst.n_query(34) << ' ';
	//cout << bst.n_query(90);
	//bst.preOrder();
	//bst.inOrder();
	//bst.postOrder();
	//bst.levelOrder();
	//bst.n_preOrder();
	//bst.n_inOrder();
	//bst.n_postOrder();
	//bst.n_levelOrder();
	//cout << bst.high() << endl;
	//cout << bst.number() << endl;
	//cout << bst.query(54) << endl;
	//cout << bst.query(41) << endl;

	//vector<int> vec;
	//bst.findValues(vec, 20, 60);
	//for (int i : vec)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	//cout << bst.isBSTree();
	//cout << bst.isBSTree() << endl;
	//test1();
	//test2(bst);
	//test3();

	//bst.mirror01();
	//bst.inOrder();
	//test4();
	//test5();
	//bst.insert(45);
	//cout << bst.isBalance() << endl;
	//cout << bst.getVal(3);
	return 0;
}