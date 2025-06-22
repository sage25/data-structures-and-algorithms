#include<unordered_set>
#include<unordered_map>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<string>
#include<memory>
using namespace std;

int main()
{
	//srand((unsigned)time(0));
	//1.哈希表，查找哪些数据重复
	//unordered_set<int> set_;
	//vector<int>vecs{ 12,65,74,12,58,21 };
	//cout << "重复的数据有：";
	//for (int i = 0; i < vecs.size(); i++)
	//{
	//	//int key = rand() / 200 + 1;
	//	int key = vecs[i];
	//	if (set_.find(key) == set_.end())
	//	{
	//		set_.insert(key);
	//	}
	//	else
	//	{
	//		cout << key << " ";
	//	}
	//}
	
	//2.哈希表，查找第一个不重复的数据
	//unordered_map<char, int>map_;
	//const string str = "jjggjakfgu";
	//for (char ch : str)
	//{
	//	map_[ch]++;
	//}
	//for (char ch : str)
	//{
	//	if (map_[ch] == 1)
	//	{
	//		cout << "第一个不重复的数据是：" << ch << endl;
	//		break;
	//	}
	//}

	//3.位图，查找重复的数据
	vector<int>vecs{ 12,65,74,12,58,21 };
	//开辟位图数组
	int size = 74 / 8 + 1;
	shared_ptr<char>BitArr(new char[size]);
	memset(BitArr.get(), 0, size);
	for (int i : vecs)
	{
		int idx = i / 8;
		int bit = i % 8;
		if (BitArr.get()[idx] & (0x01 << bit))
		{
			cout << i << ' ';
		}
		else
		{
			BitArr.get()[idx] |= (0x01 << bit);
		}
	}
	return 0;
}