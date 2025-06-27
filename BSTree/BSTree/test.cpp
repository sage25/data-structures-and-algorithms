#include<iostream>
#include<functional>
using namespace std;


template<class T, class Comp = less<T>>
class BSTree
{
private:
	//�ڵ㶨��
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
	//���ڵ�
	Node* root;
	//�Ƚ϶���
	Comp comp_;
public:
	BSTree()
		: root(nullptr)
	{ }
	~BSTree() { }
	//�ǵݹ����
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
	//�ǵݹ�ɾ��
	void remove(const T& data)
	{
		if (root == nullptr)
		{
			return;
		}
		Node* cur = root;
		Node* parent = nullptr;
		//Ѱ��Ҫɾ���Ľڵ�
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
		//û�ҵ�
		if (cur == nullptr)
		{
			cout << "Node dose not exist!";
			return;
		}
		//����Ҫɾ���ڵ��������ӽڵ����(ǰ���ڵ㸲��)
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
		
		//childָ��Ҫɾ���Ľڵ�ĺ��ӽڵ�
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}
		//ͳһ����û���ӽڵ����һ���ӽڵ�
		if (parent == nullptr)	//ɾ���Ľڵ�Ϊ���ڵ�
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