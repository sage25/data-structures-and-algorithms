#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

struct Node 
{
	Node(int data_): data(data_),next(nullptr){}
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
	~Clink() {};
	void inserttail(int data_)
	{
		Node* p = head;
		while (p != nullptr)
		{
			p = p->next;
		}
		p->next = new Node(data_);;
	}
	void inserthead(int data_)
	{

	}
};

int main()
{

	return 0;
}