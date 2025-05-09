#include<iostream>
using namespace std;

class Queue
{
private:
	int* pQue_;
	int cap_;  // 容量
	int front_;  // 队头
	int rear_;  // 队尾
	int size;
private:
	void expand(int size)
	{
		int* p = new int[size];
		if (front_ > rear_)
		{
			memcpy(&p[front_], &pQue_[front_], (size / 2 - front_) * sizeof(int));
			memcpy(&p[size / 2], pQue_, rear_ * sizeof(int));
		}
		else
			memcpy(p, pQue_, size / 2 * sizeof(int));
		delete[] pQue_;
		pQue_ = p;
		cap_ = size;
	}
public:
	Queue(int size = 10)
		: front_(0)
		, rear_(0)
		, cap_(size)
		, size(0)
	{
		pQue_ = new int[size];
	}
	~Queue()
	{
		delete[] pQue_;
		pQue_ = nullptr;
	}
public:
	void push(int val_)
	{
		if ((rear_ + 1) % cap_ == front_)
		{
			// 扩容
			expand(cap_ * 2);
		}
		pQue_[rear_] = val_;
		rear_ = (rear_ + 1) % cap_;
		size++;
	}
	void pop()
	{
		if (front_ == rear_)
			throw "Queue is empty!";
		front_ = (front_ + 1) % cap_;
		size--;
	}
	int front() const
	{
		if (front_ == rear_)
			throw "Queue is empty!";
		return pQue_[front_];
	}
	int back() const
	{
		if (front_ == rear_)
			throw "Queue is empty!";
		return pQue_[(rear_ - 1 + cap_) % cap_];
	}
	int empty() { return front_ == rear_; }
};

int main()
{
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Queue que;
	for (int i : arr)
	{
		que.push(i);
	}
	cout << que.front() << ' ' << que.back() << endl;
	que.push(100);
	que.push(200);
	que.push(300);
	cout << que.front() << ' ' << que.back() << endl;
	return 0;
}