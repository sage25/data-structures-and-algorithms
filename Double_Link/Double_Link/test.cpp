#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

// �ڵ�
struct Node
{
	Node(int data = 0)
		: pre_(nullptr)
		, data_ (data)
		, next_(nullptr)
	{ }
	Node* pre_;
	int data_;
	Node* next_;
};

// ˫������
class DoubleLink
{
private:
	Node* head_;
public:
	DoubleLink(int data = 0)
	{
		head_ = new Node(data);
	}
	~DoubleLink()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}
public:
	// ͷ��
	void inserthead(int data)
	{
		Node* node = new Node(data);
		node->next_ = head_->next_;
		node->pre_ = head_;
		if (head_->next_ != nullptr)
		{
			node->next_->pre_ = node;
		}
		head_->next_ = node;
	}
	// β��
	void inserttail(int data)
	{
		Node* p = new Node(data);
		Node* q = head_;
		while (q->next_ != nullptr)
		{
			q = q->next_;
		}
		q->next_ = p;
		p->pre_ = q;
	}
	// ɾ���ڵ�
	void remove(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				if (p->next_ != nullptr)
					p->next_->pre_ = p->pre_;
				p->pre_->next_ = p->next_;
				delete p;
				return;
			}
			p = p->next_;
		}
	}
	// ����
	bool find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				return true;
			}
			p = p->next_;
		}
		return false;
	}

	// ��ӡ
	void show()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data_ << ' ';
			p = p->next_;
		}
		cout << endl;
	}
};

int main()
{
	srand((unsigned)time(0));
	DoubleLink link;
	for (int i = 0; i < 10; i++)
	{
		link.inserttail(rand() % 100);
	}
	
	for (int i = 0; i < 10; i++)
	{
		link.inserthead(rand() % 100);
	}
	
	link.inserttail(200);
	link.show();
	link.remove(200);
	link.show();
	return 0;
}