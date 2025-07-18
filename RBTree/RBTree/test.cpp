#include<algorithm>

template<class T>
class RBTree
{
public:
	RBTree()
		:root_(nullptr)
	{ }
	//插入
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val, nullptr, nullptr, nullptr, BLACK);
			return;
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
			else if (val < cur->data_)
			{
				cur = cur->left_;
			}
			else
			{
				return;
			}
		}
		cur = new Node(val, nullptr, nullptr, parent, RED);
		if (val > parent->data_)
		{
			parent->right_ = cur;
		}
		else
		{
			parent->left_ = cur;
		}
		fixAfterInsert(cur);
	}
	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr)
		{
			return;
		}
		//删除节点有两个孩子
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			//前驱节点覆盖
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		//删除节点最多有一个孩子
		Node* child = cur->left_ != nullptr ? cur->left_ : cur->right_;
		//left parent right
		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				//cur是根节点
				root_ = cur;
			}
			else
			{
				if (left(parent(cur)) == cur)
				{
					cur->parent_->left_ = child;
				}
				else
				{
					cur->parent_->right_ = child;
				}
			}

			Color c = color(cur);
			delete cur;
			if (c == BLACK)
			{
				fixAfterRemove(child);
			}
		}
		else // child == nullptr
		{
			if (parent(cur) == nullptr)
			{
				delete cur;
				root_ = nullptr;
				return;
			}
			else
			{
				if (color(cur) == BLACK)
				{
					fixAfterRemove(cur);
				}
				if (left(parent(cur)) == cur)
				{
					cur->parent_->left_ = nullptr;
				}
				else
				{
					cur->parent_->right_ = nullptr;
				}
			}
			delete cur;
		}
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
	void leftRotate(Node* node)
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
	void rightRotate(Node* node)
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
		while (color(node->parent_) == RED && node != root_)
		{
			if (left(parent(parent(node))) == parent(node))
			{
				//插入节点在爷爷节点的左边
				Node* uncle = right(parent(parent(node)));
				//处理情况1
				if (color(uncle) == RED)
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
				Node* uncle = left(parent(parent(node)));
				//处理情况1
				if (color(uncle) == RED)
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
	//修复删除后节点颜色
	void fixAfterRemove(Node* node)
	{
		while (node != root_ && color(node) == BLACK)
		{
			if (left(parent(node)) == node)
			{
				//删除节点在父节点左边

				Node* brother = right(parent(node));
				if (color(brother) == RED)
				{
					//情况四
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}
				if (color(left(brother)) == BLACK 
					&& color(right(brother)) == BLACK)
				{
					//情况三
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(left(brother)) == RED)
					{
						//情况二
						setColor(left(brother), BLACK);
						setColor(brother, RED);
						rightRotate(brother);
						brother = right(parent(node));
					}
					//情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(right(brother), BLACK);
					leftRotate(parent(node));
					return;
				}
			}
			else
			{
				//删除节点在父节点右边

				Node* brother = left(parent(node));
				if (color(brother) == RED)
				{
					//情况四
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));
				}
				if (color(left(brother)) == BLACK
					&& color(right(brother)) == BLACK)
				{
					//情况三
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(right(brother)) == RED)
					{
						//情况二
						setColor(right(brother), BLACK);
						setColor(brother, RED);
						leftRotate(brother);
						brother = left(parent(node));
					}
					//情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(left(brother), BLACK);
					rightRotate(parent(node));
					return;
				}
			}
		}
		setColor(node, BLACK);
	}
};

int main()
{
	RBTree <int>rbt;
	for (int i = 1; i <= 10; i++)
	{
		rbt.insert(i);
	}
	rbt.remove(9);
	rbt.remove(10);
	rbt.remove(5);
	rbt.remove(3);
	return 0;
}