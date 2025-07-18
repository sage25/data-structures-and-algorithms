#include<algorithm>

template<class T>
class RBTree
{
public:
	RBTree()
		:root_(nullptr)
	{ }
	//����
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
		//ɾ���ڵ�����������
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			//ǰ���ڵ㸲��
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		//ɾ���ڵ������һ������
		Node* child = cur->left_ != nullptr ? cur->left_ : cur->right_;
		//left parent right
		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				//cur�Ǹ��ڵ�
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
	void leftRotate(Node* node)
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
	void rightRotate(Node* node)
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
		while (color(node->parent_) == RED && node != root_)
		{
			if (left(parent(parent(node))) == parent(node))
			{
				//����ڵ���үү�ڵ�����
				Node* uncle = right(parent(parent(node)));
				//�������1
				if (color(uncle) == RED)
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
				Node* uncle = left(parent(parent(node)));
				//�������1
				if (color(uncle) == RED)
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
	//�޸�ɾ����ڵ���ɫ
	void fixAfterRemove(Node* node)
	{
		while (node != root_ && color(node) == BLACK)
		{
			if (left(parent(node)) == node)
			{
				//ɾ���ڵ��ڸ��ڵ����

				Node* brother = right(parent(node));
				if (color(brother) == RED)
				{
					//�����
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}
				if (color(left(brother)) == BLACK 
					&& color(right(brother)) == BLACK)
				{
					//�����
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(left(brother)) == RED)
					{
						//�����
						setColor(left(brother), BLACK);
						setColor(brother, RED);
						rightRotate(brother);
						brother = right(parent(node));
					}
					//���һ
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(right(brother), BLACK);
					leftRotate(parent(node));
					return;
				}
			}
			else
			{
				//ɾ���ڵ��ڸ��ڵ��ұ�

				Node* brother = left(parent(node));
				if (color(brother) == RED)
				{
					//�����
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));
				}
				if (color(left(brother)) == BLACK
					&& color(right(brother)) == BLACK)
				{
					//�����
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					if (color(right(brother)) == RED)
					{
						//�����
						setColor(right(brother), BLACK);
						setColor(brother, RED);
						leftRotate(brother);
						brother = left(parent(node));
					}
					//���һ
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