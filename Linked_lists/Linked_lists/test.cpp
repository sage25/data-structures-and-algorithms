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

// 两个链表是否存在相交，返回相交数据
bool islinkhasmerge(Node* head1, Node* head2, int& val)
{
	Node* p = head1->next;
	Node* q = head2->next;
	int count1 = 0;
	int count2 = 0;
	while (p != nullptr)
	{
		p = p->next;
		count1++;
	}
	while (q != nullptr)
	{
		q = q->next;
		count2++;
	}
	p = head1;
	q = head2;
	int num;
	if(count1 > count2)
	{ 
		num = count1 - count2;
		while (num--)
		{
			p = p->next;
		}
	}
	else
	{
		num = count2 - count1;
		while (num--)
		{
			q = q->next;
		}
	}
	while (p != nullptr && q != nullptr)
	{
		if (p == q)
		{	
			val = p->data;
			return true;
		}
		p = p->next;
		q = q->next;
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
	
	//Node* head;
	//Node n1(0), n2(36), n3(15), n4(86);
	//head = &n1;
	//n1.next = &n2;
	//n2.next = &n3;
	//n3.next = &n4;
	//n4.next = &n2;
	//int val;
	//if (islinkhasecircle(head, val))
	//{
	//	cout << val << endl;
	//}

	Node* head1;
	Node* head2;
	Node n1(0), n2(83), n3(17), n4(13), n5(71), n6(894);
	Node N1(0), N2(81);
	head1 = &n1;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n4.next = &n5;
	head2 = &N1;
	N1.next = &N2;
	N2.next = &n4;

	int val;
	if (islinkhasmerge(head1, head2, val))
	{
		cout << val << endl;
	}

	return 0;
}
