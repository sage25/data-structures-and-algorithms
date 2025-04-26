#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

struct Node
{
	Node(int data_) : data(data_), next(nullptr) {}
	int data;
	Node* next;
};

class Clink
{
private:
	Node* head;
public:
	Clink(int data_ = 0)
	{
		head = new Node(data_);
	}
	~Clink()
	{
		while (head != nullptr)
		{
			Node* tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	// β��
	void inserttail(int data_)
	{
		Node* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		p->next = new Node(data_);
	}
	// ͷ��
	void inserthead(int data_)
	{
		Node* node = new Node(data_);
		node->next = head->next;
		head->next = node;
	}
	// ɾ���ڵ�
	void remove(int data_)
	{
		Node* p = head->next;
		Node* q = head;	//ָ��p��ָ�����һ���ڵ㡣
		while (p != nullptr)
		{
			if (p->data != data_)
			{
				q = p;
				p = p->next;
			}
			else
			{
				q->next = p->next;
				delete p;
				return;
			}
		}
	}
	// ɾ������ڵ�
	void removeall(int data_)
	{
		Node* p = head->next;
		Node* q = head;	//q��pǰһ���ڵ��ָ��
		while (p != nullptr)
		{
			if (p->data != data_)
			{
				q = p;
				p = p->next;
			}
			else
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
		}
	}
	// ����
	bool find(int data_)
	{
		Node* p = head->next;
		while (p != nullptr)
		{
			if (p->data == data_)
			{
				return true;
			}
			else
			{
				p = p->next;
			}
		}
		return false;
	}
	// ��ӡ����
	void show()
	{
		Node* p = head->next;
		while (p != nullptr)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
public:
	friend void reverse(Clink& link);
	friend bool countdown(int k, Clink& link, int& val);
};

// ����
void reverse(Clink& link)
{
	Node* head_ = link.head;
	if (head_->next == nullptr)
	{
		return;
	}
	Node* p = head_->next;
	head_->next = nullptr;
	while (p != nullptr)
	{
		Node* q = p->next; // ��һ�ڵ�
		p->next = head_->next;
		head_->next = p;
		p = q;
	}
}

// ������k���ڵ��ֵ
bool countdown(int k ,Clink& link, int& val)
{
	if (k < 1)
	{
		return false;
	}
	Node* head_ = link.head;
	Node* p = head_->next;
	while (k--)
	{
		p = p->next;
		if (p == nullptr)
		{
			return false;
		}
	}
	Node* q = head_->next;
	while (p != nullptr)
	{
		p = p->next;
		q = q->next;
	}
	val = q->data;
	return true;
}


int main()
{
	srand((unsigned)time(0));
	Clink link(0);
	for (int i = 0; i < 10; i++)
	{
		int num = rand() % 100;
		link.inserthead(num);
	}
	link.show();
	//link.inserthead(8);
	//link.show();
	//link.remove(8);
	//link.show();
	//link.inserttail(999);
	//link.inserttail(999);
	//link.inserttail(999);
	//link.inserttail(999);
	//link.show();
	//link.removeall(999);
	//link.show();
	//link.inserttail(666);
	//link.show();
	//cout << link.find(666) << endl;
	//cout << link.find(888) << endl;
	//reverse(link);
	//link.show();
	
	int kval;
	int k = 5;

	if (countdown(k, link, kval))
	{
		cout << "����" << k << "��ֵΪ��" << kval << endl;
	}
	return 0;
}
