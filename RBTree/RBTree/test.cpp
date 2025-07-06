#include<algorithm>

template<class T>
class BSTree
{
private:
	//定义颜色
	enum color
	{
		BLACK,
		RED
	};
	//定义节点
	struct Node
	{
		T data_;
		Node* left_;
		Node* right_;
		Node* parent_;
		color color_;
		int height_;
	};
	Node* root_;
	int height(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return max(height(node->left_), height(node->right_) + 1;
	}
	//左旋
	Node* leftRotate(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//以child为轴进行左旋
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//更新节点高度
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	//右旋
	Node* rightRotate(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//以child为轴进行右旋
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//更新节点高度
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	};
};

int main()
{
	return 0;
}