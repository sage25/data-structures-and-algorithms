#include<iostream>
using namespace std;

// 顺序栈(数组实现) 
class SeqStack
{
private:
	int mtop; // 栈顶位置
	int mcap; // 栈空间大小
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
	// 入栈
	void push(int val_)
	{
		if (mtop == mcap)
		{
			// 栈扩容
			expand(2 * mcap);
		}
		mpStack[mtop++] = val_;
	}
	// 出栈
	void pop()
	{
		if (mtop == 0)
			throw "stack is empty!";
		mtop--;
	}
	// 获取栈顶元素
	int top()
	{
		if (mtop == 0)
			throw "stack is empty!";
		return mpStack[mtop - 1];
	}
	// 获取元素个数
	int size() const { return mtop; }
	// 判断栈是否为空
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

// 链式栈(链表实现)
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
	// 入栈
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		size_++;
	}
	// 出栈
	void pop()
	{
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		size_--;
	}
	// 获取栈顶元素
	int top() const 
	{ 
		if(head_->next_ == nullptr)
			throw "stack is empty!";
		return head_->next_->val_; 
	}
	// 获取元素个数
	int size() const { return size_; }
	//栈空
	bool empty() { return head_->next_ == nullptr; }
};

//测试顺序栈
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


//测试链式栈
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