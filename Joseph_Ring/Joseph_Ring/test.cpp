/*
约瑟夫环问题是一个经典的数学问题，
描述了n个人围坐在一个圆圈中，
从编号为k的人开始报数，每数到m的人就出列，
直到所有人都被排除.
*/

#include<iostream>
using namespace std;

struct Node
{
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// 约瑟夫环
void JosephRing(Node* head, int k, int m)
{
	Node* p = head;
	for (int i = 1; i < k; i++)
	{
		p = p->next_;
	}
	Node* q;
	for (;;)
	{
		if (p->next_ == p)
		{
			cout << p->data_ << endl;
			delete p;
			break;
		}
		for (int i = 0; i < m - 1; i++)
		{
			p = p->next_;
		}
		q = p->next_;
		p->next_ = q->next_;
		cout << q->data_ << ' ';
		delete q;
	}
}

// 用于创建单向循环链表
Node* link(int i_)
{
	Node* head = new Node(1);
	Node* p = head;
	for (int i = 2; i < i_ + 1; i++)
	{
		p->next_ = new Node(i);
		p = p->next_;
	}
	p->next_ = head;
	return head;
}

int main()
{
	Node* head = link(9);
	JosephRing(head ,2 ,5);
	return 0;
}