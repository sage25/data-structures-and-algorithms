#include <vector>
#include <list>
#include <iostream>
using namespace std;

class HashTable
{
private:
	vector<list<int>>Table_;
	int useBucketNum_;
	double loadFactor_;
	static const int PRIME_SIZE = 10;
	static int prime_[PRIME_SIZE];
	int primeIdx;
private:
	//���ݺ���
	void expand()
	{
		vector<list<int>>oldTable_;
		oldTable_.resize(prime_[primeIdx + 1]);
		swap(oldTable_, Table_);
		//���¹�ϣ����
		for (auto list : oldTable_)
		{
			for (auto i : list)
			{
				int idx = i % prime_[primeIdx + 1];
				Table_[idx].emplace_front(i);
			}
		}
		primeIdx++;
	}

public:
	HashTable(double loadFactor = 0.75, int size = 3)
		: loadFactor_(loadFactor)
		, useBucketNum_(0)
		, primeIdx(0)
	{
		if (size != 3)
		{
			for (; prime_[primeIdx] < PRIME_SIZE; primeIdx++)
			{
				if (primeIdx > size)
					break;
			}
			if (primeIdx == PRIME_SIZE)
				primeIdx--;
		}
		Table_.resize(prime_[primeIdx]);
	}
	//����Ԫ��
	void insert(int key)
	{
		//�ҵ������Ͱ
		int idx = key % Table_.size();
		//����
		if (useBucketNum_ * 1.0 / Table_.size()  >= loadFactor_)
			expand();
		Table_[idx].push_front(key);
		useBucketNum_++;
	}
	//���Һ���
	bool find(int key)
	{
		int idx = key % Table_.size();
		auto it = ::find(Table_[idx].begin(), Table_[idx].end(), key);
		if (it != Table_[idx].end())
			return true;
		return false;
	}
	//ɾ������
	void erase(int key)
	{
		int idx = key % Table_.size();
		if (!Table_[idx].empty())
		{
			Table_[idx].remove(key);
			useBucketNum_--;
		}
	}
};
int HashTable::prime_[PRIME_SIZE] = { 3,7,23,47,101,233,557,1039,2251,4871 };

int main()
{
	HashTable table;
	table.insert(67);
	table.insert(21);
	table.insert(32);
	table.insert(45);
	table.insert(84);
	table.erase(45);
	table.erase(21);
	cout << table.find(67) << ' ';
	cout << table.find(54) << ' ';
	return 0;
}