#include<algorithm>

template<class T>
class BSTree
{
public:
	BSTree()
		:root_(nullptr)
	{ }
	//����
	void insert(T data)
	{

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
	//ָ����ڵ�
	Node* root_;
	int height(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return max(height(node->left_), height(node->right_) + 1;
	}
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
};

int main()
{
	return 0;
}