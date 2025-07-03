#include<cmath>
using namespace std;

template<class T>
class AVLTree
{
private:
	//节点定义
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
	//返回节点子树高度
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}
	//以node节点为进行轴右旋
	Node* rightRotate(Node* node)
	{
		//旋转节点
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//更新高度
		node->height_ = max(node->left_, node->right_);
		child->height_ = max(child->left_, child->right_);
		return child;
	}
	//以node节点为进行轴左旋
	Node* leftRotate(Node* node)
	{
		//旋转节点
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//更新高度
		node->height_ = max(node->left_, node->right_);
		child->height_ = max(child->left_, child->right_);
		return child;
	}
	//左平衡操作
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}
	//右平衡操作
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}
public:
	AVLTree()
		: root_(nullptr)
	{ }
	//AVL树插入操作
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
		}
		insert(root_, val);
	}
private:
	//插入操作实现
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
				//左孩子的左子树高度差与左孩子的右子树高度差大于1，执行右旋转
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
				//右孩子的右子树高度差与右孩子的左子树高度差大于1，执行右旋转
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