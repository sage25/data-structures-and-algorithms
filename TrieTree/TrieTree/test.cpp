#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<queue>
using namespace std;

class TrieTree
{
private:
	//节点定义
	struct TrieNode
	{
		TrieNode(char data, int freqs)
			: data_(data)
			, freqs_(freqs)
		{ }
		char data_;
		int freqs_;
		map<char, TrieNode*> nodeMap_;
	};
	TrieNode* root_;
public:
	TrieTree()
		: root_(new TrieNode('\0', 0))
	{ }
	~TrieTree()
	{
		queue<TrieNode*> que;
		que.push(root_);
		while (!que.empty())
		{
			TrieNode* front = que.front();
			que.pop();
			for (auto it : front->nodeMap_)
			{
				que.push(it.second);
			}
			delete front;
		}
	}
	//增加接口
	void add(const string& word)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < word.size(); i++)
		{
			auto it = cur->nodeMap_.find(word[i]);
			if (it == cur->nodeMap_.end())
			{
				//没找到相关节点，创造节点
				cur->nodeMap_.emplace(word[i], new TrieNode(word[i], 0));
			}
			cur = cur->nodeMap_[word[i]];
		}
		cur->freqs_++;
	}
	//查询接口
	int query(const string& word)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < word.size(); i++)
		{
			auto childIt = cur->nodeMap_.find(word[i]);
			if (childIt == cur->nodeMap_.end())
			{
				return 0;
			}
			cur = cur->nodeMap_[word[i]];
		}
		return cur->freqs_;
	}
	//前序遍历
	void preOrder()
	{
		vector<string> wordList;
		string word;
		preOrder(root_, word, wordList);
		for (string str : wordList)
		{
			cout << str << endl;
		}
	}
	//前缀检索
	vector<string> queryPreFix(const string& prefix)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < prefix.size(); i++)
		{
			auto it = cur->nodeMap_.find(prefix[i]);
			if (it == cur->nodeMap_.end())
			{
				return { };
			}
			cur = cur->nodeMap_[prefix[i]];
		}
		vector<string> wordList;
		preOrder(cur, prefix.substr(0, prefix.size() - 1), wordList);
		return wordList;
	}
	//删除接口
	void remove(const string& word)
	{
		TrieNode* del = root_;
		TrieNode* cur = root_;
		char delch = word[0];
		for (int i = 0; i < word.size(); i++)
		{
			auto it = cur->nodeMap_.find(word[i]);
			if (it == cur->nodeMap_.end())
			{
				//找不到
				return;
			}
			if (cur->freqs_ > 0 || cur->nodeMap_.size() > 1)
			{
				//处理特殊情况
				del = cur;
				delch = word[i];
			}
			cur = it->second;
		}

		if (cur->nodeMap_.empty())
		{
			TrieNode* child = del->nodeMap_[delch];
			del->nodeMap_.erase(delch);

			queue<TrieNode*> que;
			que.push(child);
			while (!que.empty())
			{
				TrieNode* front = que.front();
				que.pop();
				for (auto it : front->nodeMap_)
				{
					que.push(it.second);
				}
				delete front;
			}
		}
		else
		{
			cur->freqs_ = 0;
		}
	}
private:
	void preOrder(TrieNode* node, string word, vector<string> & wordList)
	{
		if (node != root_)
		{
			word.push_back(node->data_);
			if (node->freqs_ > 0)
			{
				wordList.emplace_back(word);
			}
		}
		for (auto it : node->nodeMap_)
		{
			preOrder(it.second, word, wordList);
		}
	}
};

int main()
{
	TrieTree tree;
	tree.add("china");
	tree.add("hello");
	tree.add("hello");
	tree.add("helee");
	tree.add("ch");
	tree.add("ch");
	tree.add("chwl");
	tree.add("cwwl");

	cout << tree.query("hel") << endl;
	cout << tree.query("hello") << endl;
	cout << tree.query("ch") << endl;
	cout << tree.query("china") << endl;
	cout << "==========================" << endl;

	tree.preOrder();
	cout << "==========================" << endl;

	vector<string> words = tree.queryPreFix("he");
	for (auto word : words)
	{
		cout << word << endl;
	}
	cout << endl;

	cout << "==========================" << endl;
	tree.remove("china");
	cout << tree.query("china") << endl;

	return 0;
}