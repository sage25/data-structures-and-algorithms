#include<iostream>
#include<functional>
#include<stack>
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
	BSTree()
		: root_(nullptr)
	{ }
	~BSTree() { }
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
private:
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
		if(node->right_ != nullptr)
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
};


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
	bst.n_postOrder();
	//cout << bst.high() << endl;
	//cout << bst.number() << endl;
	//cout << bst.query(54) << endl;
	//cout << bst.query(41) << endl;
	
	return 0;
}