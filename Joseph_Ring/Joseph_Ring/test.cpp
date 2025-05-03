/*
Լɪ��������һ���������ѧ���⣬
������n����Χ����һ��ԲȦ�У�
�ӱ��Ϊk���˿�ʼ������ÿ����m���˾ͳ��У�
ֱ�������˶����ų�.
*/

#include<iostream>
using namespace std;

struct Node
{
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// Լɪ��
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

// ���ڴ�������ѭ������
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