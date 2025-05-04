#include<iostream>
using namespace std;

// ˳��ջ(����ʵ��) 
class SeqStack
{
private:
	int mtop; // ջ��λ��
	int mcap; // ջ�ռ��С
	int* mpStack; 
private:
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpStack, mcap * sizeof(int));
		delete[] mpStack;
		mpStack = p;
	}
public:
	SeqStack(int size = 10)
		: mtop(0)
		, mcap(size)
	{
		mpStack = new int[size];
	}
	~SeqStack()
	{
		delete[] mpStack;
		mpStack = nullptr;
	}
	// ��ջ
	void push(int val_)
	{
		if (mtop == mcap)
		{
			// ջ����
			expand(2 * mcap);
		}
		mpStack[mtop++] = val_;
	}
	// ��ջ
	void pop()
	{
		if (mtop == 0)
			throw "stack is empty!";
		mtop--;
	}
	// ��ȡջ��Ԫ��
	int top()
	{
		if (mtop == 0)
			throw "stack is empty!";
		return mpStack[mtop - 1];
	}
	// ��ȡԪ�ظ���
	int size() const { return mtop; }
	// �ж�ջ�Ƿ�Ϊ��
	bool empty() const { return mtop == 0; }
};


struct Node
{
	Node(int val = 0)
		: val_(val)
		, next_(nullptr)
	{ }
	int val_;
	Node* next_;
};

// ��ʽջ(����ʵ��)
class LinkStack
{
private:
	Node* head_;
	int size_;
public:
	LinkStack(int val) : size_(0)
	{
		head_ = new Node(val);
	}
	~LinkStack()
	{
		
		Node* p = head_;
		while (head_->next_ != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}
	// ��ջ
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		size_++;
	}
	// ��ջ
	void pop()
	{
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		size_--;
	}
	// ��ȡջ��Ԫ��
	int top() const 
	{ 
		if(head_->next_ == nullptr)
			throw "stack is empty!";
		return head_->next_->val_; 
	}
	// ��ȡԪ�ظ���
	int size() const { return size_; }
	//ջ��
	bool empty() { return head_->next_ == nullptr; }
};

//����˳��ջ
//int main()
//{
//	int arr[5] = { 1, 2, 3, 4, 5 };
//	SeqStack stack(5);
//	for (int val : arr)
//	{
//		stack.push(val);
//	}
//	while (!stack.empty())
//	{
//		cout << stack.top() << ' ';
//		stack.pop();
//	}
//	return 0;
//}


//������ʽջ
int main()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	LinkStack stack(5);
	for (int val : arr)
	{
		stack.push(val);
	}
	cout << stack.size() << endl;
	while (!stack.empty())
	{
		cout << stack.top() << ' ';
		stack.pop();
	}
	return 0;
}