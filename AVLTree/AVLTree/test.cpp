#include<cmath>
#include<algorithm>
using namespace std;

template<class T>
class AVLTree
{
private:
	//�ڵ㶨��
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
	//���ؽڵ������߶�
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}
	//��node�ڵ�Ϊ����������
	Node* rightRotate(Node* node)
	{
		//��ת�ڵ�
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//���¸߶�
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	//��node�ڵ�Ϊ����������
	Node* leftRotate(Node* node)
	{
		//��ת�ڵ�
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//���¸߶�
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	//��ƽ�����
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}
	//��ƽ�����
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}
public:
	AVLTree()
		: root_(nullptr)
	{ }
	//�������
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		root_ = insert(root_, val);
	}
	//ɾ������
	void remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}
		root_ = remove(root_, val);
	}
private:
	//�������ʵ��
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
				//���ӵ��������߶Ȳ������ӵ��������߶Ȳ����1��ִ������ת
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
				//�Һ��ӵ��������߶Ȳ����Һ��ӵ��������߶Ȳ����1��ִ������ת
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
	//ɾ������ʵ��
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
		//�ҵ���
		else
		{
			//������ɾ�ڵ����������ӽڵ����
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//�������߶ȴ����ұߣ�ǰ���ڵ㸲��
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
				//�������߶�С���ұߣ���̽ڵ㸲��
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
			//����ɾ���ڵ������һ���ڵ����
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