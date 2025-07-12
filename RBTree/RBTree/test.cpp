#include<algorithm>

template<class T>
class BSTree
{
public:
	BSTree()
		:root_(nullptr)
	{ }
	//插入
	void insert(const T& val)
	{
		if (root_ = nullptr)
		{
			root_ = new Node(val);
		}
		Node* cur = root_;
		Node* parent = nullptr;
		while (cur != nullptr)
		{
			parent = cur;
			if (val > cur->data_)
			{
				cur = cur->right_;
			}
			else if (val < cur->left_)
			{
				cur = cur->left_;
			}
			else
			{
				return;
			}
		}
		cur = new Node(val, nullptr, nullptr, parent, RED);
		fixAfterInsert(cur);
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
		, Color color = BLACK)
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
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
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
private:
	//修复插入后的节点颜色
	void fixAfterInsert(Node* node)
	{
		while (color(node->parent_) == RED)
		{
			if (left(parent(parent(node))) == parent(node))
			{
				//插入节点在爷爷节点的左边
				Node* uncle = left(parent(parent(node)));
				//处理情况1
				if (color(uncle) = BLACK)
				{
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					setColor(uncle, BLACK);
					node = parent(parent(node));
				}
				else
				{
					//处理情况3
					if (right(parent(node)) == node)
					{
						node = parent(node);
						leftRotate(node);
					}
					//处理情况2
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break;
				}
			}
			else
			{
				//插入节点在爷爷节点的右边
				Node* uncle = right(parent(parent(node)));
				//处理情况1
				if (color(uncle) = BLACK)
				{
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					setColor(uncle, BLACK);
					node = parent(parent(node));
				}
				else
				{
					//处理情况3
					if (left(parent(node)) == node)
					{
						node = parent(node);
						rightRotate(node);
					}
					//处理情况2
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break;
				}
			}
		}
		setColor(root_, BLACK);
	}
};

int main()
{
	return 0;
}