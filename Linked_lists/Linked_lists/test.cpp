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
	// 尾插
	void inserttail(int data_)
	{
		Node* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		p->next = new Node(data_);
	}
	// 头插
	void inserthead(int data_)
	{
		Node* node = new Node(data_);
		node->next = head->next;
		head->next = node;
	}
	// 删除节点
	void remove(int data_)
	{
		Node* p = head->next;
		Node* q = head;	//指向p所指向的上一个节点。
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
	// 删除多个节点
	void removeall(int data_)
	{
		Node* p = head->next;
		Node* q = head;	//q是p前一个节点的指针
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
	// 查找
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
	// 打印数据
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
	friend void merge(Clink& C1, Clink& C2);
};

// 逆序
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
		Node* q = p->next; // 下一节点
		p->next = head_->next;
		head_->next = p;
		p = q;
	}
}

// 求倒数第k个节点的值
bool countdown(int k, Clink& link, int& val)
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

// 合并两个有序链表
void merge(Clink& link1, Clink& link2)
{
	Node* p = link1.head->next;
	Node* q = link2.head->next;
	Node* last = link1.head;
	link2.head = nullptr;
	while (p != nullptr && q != nullptr)
	{
		if (p->data > q->data)
		{
			last->next = q;
			q = q->next;
		}
		else
		{
			last->next = p;
			p = p->next;
		}
		last = last->next;
	}
	if (p != nullptr)
	{
		last->next = p;
	}
	else
	{
		last->next = q;
	}
}

// 单链表是否存在环，找出环的入口节点
bool islinkhasecircle(Node* head, int& val)
{
	Node* fast = head;
	Node* slow = head;
	while (fast != nullptr && fast->next != nullptr)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			fast = head;
			while (fast != slow)
			{
				fast = fast->next;
				slow = slow->next;
				if (fast == slow)
				{
					val = fast->data;
					break;
				}
			}
			return true;
		}
	}
	return false;
}

int main()
{
	//srand((unsigned)time(0));
	//Clink link(0);
	//for (int i = 0; i < 10; i++)
	//{
	//	int num = rand() % 100;
	//	link.inserthead(num);
	//}
	//link.show();
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

	//int kval;
	//int k = 5;
	//if (countdown(k, link, kval))
	//{
	//	cout << "倒数" << k << "个值为：" << kval << endl;
	//}

	//int arr1[] = { 4 ,5 ,32 ,48 ,69 ,99 ,100 ,400 };
	//int arr2[] = { 1 ,1 ,13 , 67, 70, 666 };
	//Clink link1;
	//Clink link2;
	//for (int i : arr1)
	//{
	//	link1.inserttail(i);
	//}
	//for (int j : arr2)
	//{
	//	link2.inserttail(j);
	//}
	//merge(link1, link2);
	//link1.show();
	
	Node* head;
	Node n1(23), n2(36), n3(15), n4(86);
	head = &n1;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n4.next = &n2;

	int val;
	if (islinkhasecircle(head, val))
	{
		cout << val << endl;
	}

	return 0;
}
