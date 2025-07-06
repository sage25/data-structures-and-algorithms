#include<algorithm>

template<class T>
class BSTree
{
private:
	//������ɫ
	enum color
	{
		BLACK,
		RED
	};
	//����ڵ�
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
	//����
	Node* leftRotate(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//��childΪ���������
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//���½ڵ�߶�
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	//����
	Node* rightRotate(Node* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//��childΪ���������
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//���½ڵ�߶�
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	};
};

int main()
{
	return 0;
}