#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class Circlelink
{
private:
	struct Node
	{
		Node(int data) :data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};
	Node* head_;
	Node* tail_;
public:
	// 构造函数
	Circlelink()
	{
		head_ = new Node(0);
		tail_ = head_;
		head_->next_ = tail_;
	}
	// 析构函数
	~Circlelink()
	{
		Node* p = head_;
		while (p != tail_)
		{
			p = p->next_;
			delete head_;
			head_ = p;
		}
		delete tail_;
	}
	// 尾插	O(1)
	void inserttail(int data)
	{
		tail_->next_ = new Node(data);
		tail_ = tail_->next_;
		tail_->next_ = head_;
	}
	// 头插	O(1)
	void inserthead(int data)
	{
		Node* node = new Node(data);
		node->next_ = head_->next_;
		head_->next_ = node;
		if(node->next_ == head_)
		{ 
			tail_ = node;
		}
	}
	// 删除节点  O(n)
	void remove(int data)
	{
		Node* p = head_->next_;
		Node* q;
		while (p != head_)
		{
			if (data == p->next_->data_)
			{
				q = p->next_;
				p->next_ = p->next_->next_;
				delete q;
				if (p->next_ == head_)
				{
					tail_ = p;
				}
				return;
			}
			p = p->next_;
		}
	}
	// 查找
	bool find(int data)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == data)
			{
				return true;
			}
			p = p->next_;
		}
		return false;
	}

	// 打印
	void show() const
	{
		Node* p = head_->next_;
		while (p != head_)
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
	Circlelink link;
	//for (int i = 0; i < 10; i++)
	//{
	//	link.inserthead(rand() % 100);
	//}
	//link.show();
	//link.inserttail(8);
	//for (int i = 0; i < 10; i++)
	//{
	//	link.inserttail(rand() % 100);
	//}
	//link.show();
	//link.remove(8);
	//link.show();

	for (int i = 0; i < 10; i++)
	{
		link.inserthead(rand() % 100);
	}
	link.inserttail(200);

	link.remove(200);
	link.show();
	return 0;
}

