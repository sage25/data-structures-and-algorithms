#include<cmath>
using namespace std;

template<class T>
class AVLTree
{
private:
	//�ڵ㶨��
	struct Node
	{
		Node(const T& data)
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height_(1)
		{ }
		T data_;
		Node* left_;
		Node* right_;
		int height_;
	};
	Node* root_;
	//���ؽڵ������߶�
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}
	//��node�ڵ�Ϊ����������
	Node* rightRotate(Node* node)
	{
		//��ת�ڵ�
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//���¸߶�
		node->height_ = max(node->left_, node->right_);
		child->height_ = max(child->left_, child->right_);
		return child;
	}
	//��node�ڵ�Ϊ����������
	Node* leftRotate(Node* node)
	{
		//��ת�ڵ�
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//���¸߶�
		node->height_ = max(node->left_, node->right_);
		child->height_ = max(child->left_, child->right_);
		return child;
	}
	//��ƽ�����
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}
	//��ƽ�����
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}
public:
	AVLTree()
		: root_(nullptr)
	{ }
	//AVL���������
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
		}
		insert(root_, val);
	}
private:
	//�������ʵ��
	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return new Node(val);
		}
		if (val < node->data_)
		{
			node->left_ = insert(node->left_, val);
			if (height(node->left_) - height(node->right_) > 1)
			{
				//���ӵ��������߶Ȳ������ӵ��������߶Ȳ����1��ִ������ת
				if (height(node->left_->left_) - height(node->left_->right_) > 1)
				{
					rightRotate(node);
				}
				else
				{
					rightBalance(node);
				}
			}
		}
		else if (val > node->data_)
		{
			node->right_ = insert(node->right_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				//�Һ��ӵ��������߶Ȳ����Һ��ӵ��������߶Ȳ����1��ִ������ת
				if (height(node->right_->right_) - height(node->right_->left_) > 1)
				{
					leftRotate(node);
				}
				else
				{
					leftBalance(node);
				}
			}
		}
		else
		{
			;
		}
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}
};

int main()
{
	return 0;
}