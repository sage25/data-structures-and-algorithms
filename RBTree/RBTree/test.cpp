#include<algorithm>

template<class T>
class BSTree
{
public:
	BSTree()
		:root_(nullptr)
	{ }
	//插入
	void insert(T data)
	{

	}

private:
	//定义颜色
	enum Color
	{
		BLACK,
		RED
	};
	//定义节点
	struct Node
	{
		Node(T data= T(), Node* left = nullptr
		, Node* right = nullptr, Node* parent = nullptr
		, Color color = BLACK, int height = 0)
			: data_(data)
			, left_(left)
			, right_(right)
			, color_(color)
			, parent_(parent)
		{ }
		T data_;
		Node* left_;
		Node* right_;
		Node* parent_;
		Color color_;
	};
	//指向根节点
	Node* root_;
	int height(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return max(height(node->left_), height(node->right_) + 1;
	}
	//返回颜色
	Color color(Node* node)
	{
		return node == nullptr ? BLACK : node->color_;
	}
	//设置颜色
	void setColor(Node* node, Color color)
	{
		node->color_ = color;
	}
	//返回左孩子
	Node* left(Node* node)
	{
		return node->left_;
	}
	//返回右孩子
	Node* right(Node* node)
	{
		return node->right_;
	}
	//返回父亲
	Node* parent(Node* node)
	{
		return node->parent_;
	}
	//左旋
	Node* leftRotate(Node* node)
	{
		//以child为轴进行左旋
		Node* child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ != nullptr)
		{
			if (node->->parent_->left_ == node)
			{
				node->->parent_->left_ = child;
			}
			else
			{
				node->->parent_->right_ = child;
			}
		}
		else
		{
			//node本身就是根节点
			root_ = child;
		}
		if (child->left_ != nullptr)
		{
			child->left_->parent_ = node;
		}
		node->right_ = child->left_;
		child->left_ = node;
		node->parent_ = child;
	}
	//右旋
	Node* rightRotate(Node* node)
	{
		//以child为轴进行右旋
		Node* child = node->left_;
		child->parent_ = node->parent_;
		//node不是根节点
		if (node->parent_ != nullptr)
		{
			if (node->parent_->right_ == node)
			{
				node->parent_->right_ = child;
			}
			else
			{
				node->parent_->left_ = child;
			}
		}
		else
		{	
			//node是根节点
			root_ = child;
		}
		node->left_ = child->right_;
		if (node->left_ != nullptr)
		{
			node->left_->parent_ = node;
		}
		child->right_ = node;
		node->parent_ = child;
	};
};

int main()
{
	return 0;
}