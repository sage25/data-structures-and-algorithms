//���������͹���������
#include<queue>
#include<string>
#include<unordered_map>
#include<functional>
#include<iostream>
using namespace std;
using uint = unsigned int;



class HuffmanTree
{
private:
	struct Node
	{
		Node(char ch, uint w)
			: data_(ch)
			, weight_(w)
			, left_(nullptr)
			, right_(nullptr)
		{ }
		char data_;
		uint weight_;
		Node* left_;
		Node* right_;
	};
	Node* root_;
	using MinHeap = priority_queue<Node*,vector<Node*>,function<bool(Node*, Node*)>>;
	unordered_map<char, string> codeMap_;
	MinHeap minHeap_;
	
public:
	HuffmanTree()
		: root_(nullptr)
		, minHeap_(
			[](Node* n1, Node* n2) ->bool
			{ return n1->weight_ > n2->weight_; }
		)
	{ }

    ~HuffmanTree()
    {
        function<void(Node*)> deleteNode = [&](Node* node) {
            if (!node) return;
            deleteNode(node->left_);
            deleteNode(node->right_);
            delete node;
        };
        deleteNode(root_);
    }
	//������������
	void creat(const string& s)
	{
		unordered_map<char, int> dataMap_;
		//ͳ����ĸ���ֵĴ���
		for (auto it : s)
		{
			dataMap_[it]++;
		}
		//���μ�����С��
		for (auto pair : dataMap_)
		{
			minHeap_.push(new Node(pair.first, pair.second));
		}
		while (minHeap_.size() > 1)
		{
			Node* n1 = minHeap_.top();
			minHeap_.pop();

			Node* n2 = minHeap_.top();
			minHeap_.pop();

			Node* node = new Node('\0', n1->weight_ + n2->weight_);
			node->left_ = n1;
			node->right_ = n2;

			minHeap_.push(node);
		}

		root_ = minHeap_.top();
		minHeap_.pop();
	}
	//����
	string encode(string str)
	{
		string code;
		getHuffmanCode();
		for (char ch : str)
		{
			code += codeMap_[ch];
		}
		return code;
	}
	//����
	string decode(string code)
	{
		string str;
		Node* cur = root_;
		for (char ch : code)
		{
			if (ch == '0')
			{
				cur = cur->left_;
			}
			else
			{
				cur = cur->right_;
			}

			//����Ҷ�ӽڵ㣬����cur
			if (cur->left_ == nullptr && cur->right_ == nullptr)
			{
				str.push_back(cur->data_);
				cur = root_;
			}
		}
		return str;
	}
private:
	//����������
	void getHuffmanCode()
	{
		getHuffmanCode(root_, "");
		/*for (auto& pair : codeMap_)
		{
			cout << pair.first << ":" << pair.second << endl;
		}*/
	}
	void getHuffmanCode(Node* node, string code)
	{
		if (node->left_ == nullptr && node->right_ == nullptr)
		{
			codeMap_.emplace(node->data_, code);
		}

		if (node->left_ != nullptr)
		{
			getHuffmanCode(node->left_, code + "0");
		}

		if (node->right_ != nullptr)
		{
			getHuffmanCode(node->right_, code + "1");
		}
	}
};

int main()
{
	string str = "ABACDAEFDEG";

	HuffmanTree htree;
	htree.creat(str);
	string s = htree.encode(str);
	cout << s << endl;
	string decode_str = htree.decode(s);
	cout << decode_str << endl;

	return 0;
}