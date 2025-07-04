#include<cmath>
#include<algorithm>
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
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
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
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
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
	//插入操作
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		root_ = insert(root_, val);
	}
	//删除操作
	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}
		root_ = remove(root_, val);
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
				if (height(node->left_->left_) > height(node->left_->right_))
				{
					node = rightRotate(node);
				}
				else
				{
					node = rightBalance(node);
				}
			}
		}
		else if (val > node->data_)
		{
			node->right_ = insert(node->right_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				//右孩子的右子树高度差与右孩子的左子树高度差大于1，执行右旋转
				if (height(node->right_->right_) > height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					node = leftBalance(node);
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
	//删除操作实现
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (val < node->data_)
		{
			node->left_ = remove(node->left_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) > height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					node = rightBalance(node);
				}
			}
		}
		else if (val > node->data_)
		{
			node->right_ = remove(node->right_, val);
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) > height(node->left_->right_))
				{
					node = rightRotate(node);
				}
				else
				{
					node = leftBalance(node);
				}
			}
		}
		//找到了
		else
		{
			//处理所删节点有两个孩子节点情况
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//左子树高度大于右边，前驱节点覆盖
				if (height(node->left_) > height(node->right_))
				{
					Node* pre = node->left_;
					while (pre->right_ != nullptr)
					{
						pre = pre->right_;
					}
					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_);
				}
				//左子树高度小于右边，后继节点覆盖
				else
				{
					Node* post = node->right_;
					while (post->left_ != nullptr)
					{
						post = post->left_;
					}
					node->data_ = post->data_;
					node->right_ = remove(node->right_, post->data_);
				}
			}
			//处理删除节点最多有一个节点情况
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
					return nullptr;
				}
			}
		}
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}
};

int main()
{
	AVLTree<int> avl;
	for (int i = 1; i <= 10; i++)
	{
		avl.insert(i);
	}
	avl.remove(9);
	avl.remove(10);
	return 0;
}