#include<iostream>
#include<functional>
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
	Node* root;
	//比较对象
	Comp comp_;
public:
	BSTree()
		: root(nullptr)
	{ }
	~BSTree() { }
	//非递归插入
	void insert(const T& data)
	{
		Node* node = new Node(data);
		if (root == nullptr)
		{
			root = node;
			return;
		}
		Node* cur = root;
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
	//非递归删除
	void remove(const T& data)
	{
		if (root == nullptr)
		{
			return;
		}
		Node* cur = root;
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
			root = child;
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
};


int main()
{
	int arr[] = { 58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78 };
	BSTree<int> bst;
	for (int i = 0; i < 11; i++)
	{
		bst.insert(arr[i]);
	}
	bst.remove(5);
	bst.remove(67);
	bst.remove(58);
	return 0;
}