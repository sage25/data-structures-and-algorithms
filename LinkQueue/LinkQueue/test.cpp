#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class LinkQueue
{
private:
	struct Node
	{
		Node(int data = 0)
			: next_(nullptr)
			, pre_(nullptr)
			, data_(data)
		{
		}
		Node* next_;
		Node* pre_;
		int data_;
	};
	Node* head_;
public:
	LinkQueue()
	{
		head_ = new Node();
		head_->next_ = head_;
		head_->pre_ = head_;
	}
	~LinkQueue()
	{
		Node* p = head_->next_;
		while (head_->next_ != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
	}
public:
	// 入队
	void push(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head_->pre_;
		node->pre_->next_ = node;
		head_->pre_ = node;
		node->next_ = head_;
	}
	// 出队
	void pop()
	{
		if (head_->next_ == head_)
			throw "Queue is empty!";
		Node* p = head_->next_;
		head_->next_ = p->next_;
		p->next_->pre_ = head_;
		delete p;
	}
	// 获取队头元素
	int front() const
	{
		if (head_->next_ == head_)
			throw "Queue is empty!";
		return head_->next_->data_;
	}
	// 获取队尾元素
	int back() const
	{
		if (head_->next_ == head_)
			throw "Queue is empty!";
		return head_->pre_->data_;
	}
	// 队是否为空
	bool empty() { return head_->next_ == head_; }
};

int main()
{
	srand((unsigned)time(0));
	LinkQueue link;
	for (int i = 0; i < 10; i++)
	{
		int j = rand() % 100;
		link.push(j);
		cout << j << ' ';
	}
	cout << endl;
	cout << link.front() << ' ' << link.back() << endl;
	while (!link.empty())
	{
		cout << link.front() << ' ' << link.back() << endl;
		link.pop();
	}
	return 0;
}