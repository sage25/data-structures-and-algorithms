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
	//1.��ϣ��������Щ�����ظ�
	//unordered_set<int> set_;
	//vector<int>vecs{ 12,65,74,12,58,21 };
	//cout << "�ظ��������У�";
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
	
	//2.��ϣ�����ҵ�һ�����ظ�������
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
	//		cout << "��һ�����ظ��������ǣ�" << ch << endl;
	//		break;
	//	}
	//}

	//3.λͼ�������ظ�������
	vector<int>vecs{ 12,65,74,12,58,21 };
	//����λͼ����
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