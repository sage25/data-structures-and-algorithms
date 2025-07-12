#include<algorithm>

template<class T>
class BSTree
{
public:
	BSTree()
		:root_(nullptr)
	{ }
	//����
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
	//������ɫ
	enum Color
	{
		BLACK,
		RED
	};
	//����ڵ�
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
	//ָ����ڵ�
	Node* root_;
	//������ɫ
	Color color(Node* node)
	{
		return node == nullptr ? BLACK : node->color_;
	}
	//������ɫ
	void setColor(Node* node, Color color)
	{
		node->color_ = color;
	}
	//��������
	Node* left(Node* node)
	{
		return node->left_;
	}
	//�����Һ���
	Node* right(Node* node)
	{
		return node->right_;
	}
	//���ظ���
	Node* parent(Node* node)
	{
		return node->parent_;
	}
	//����
	Node* leftRotate(Node* node)
	{
		//��childΪ���������
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
			//node������Ǹ��ڵ�
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
	//����
	Node* rightRotate(Node* node)
	{
		//��childΪ���������
		Node* child = node->left_;
		child->parent_ = node->parent_;
		//node���Ǹ��ڵ�
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
			//node�Ǹ��ڵ�
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
	//�޸������Ľڵ���ɫ
	void fixAfterInsert(Node* node)
	{
		while (color(node->parent_) == RED)
		{
			if (left(parent(parent(node))) == parent(node))
			{
				//����ڵ���үү�ڵ�����
				Node* uncle = left(parent(parent(node)));
				//�������1
				if (color(uncle) = BLACK)
				{
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					setColor(uncle, BLACK);
					node = parent(parent(node));
				}
				else
				{
					//�������3
					if (right(parent(node)) == node)
					{
						node = parent(node);
						leftRotate(node);
					}
					//�������2
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break;
				}
			}
			else
			{
				//����ڵ���үү�ڵ���ұ�
				Node* uncle = right(parent(parent(node)));
				//�������1
				if (color(uncle) = BLACK)
				{
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					setColor(uncle, BLACK);
					node = parent(parent(node));
				}
				else
				{
					//�������3
					if (left(parent(node)) == node)
					{
						node = parent(node);
						rightRotate(node);
					}
					//�������2
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