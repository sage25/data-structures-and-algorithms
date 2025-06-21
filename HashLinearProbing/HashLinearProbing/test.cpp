#include <iostream>
using namespace std;

enum State
{
	STATE_UNUSE,
	STATE_USING,
	STATE_DEL,
};

struct Bucket
{
	Bucket(int key = 0, State state = STATE_UNUSE) 
		: key_(key)
		, state_(state)
	{ }
	int key_;
	State state_;
};

// 线性探测哈希表
class HashTable
{
private:
	Bucket* Table_;		//哈希表
	int tableSize_;		//表长度
	int	useBucketNum_;	//有效桶个数
	double loadFactor_;	//负载因子

	static const int PRIME_SIZE = 10;	//素数表长度
	static int prime_[PRIME_SIZE];		//素数表
	int primeIdx;		//当前素数
private:
	//扩容函数
	void expand()
	{
		if (primeIdx == PRIME_SIZE)
			throw "HashTable is too large, can not expand";
		//开辟需要的内存
		primeIdx += 1;
		tableSize_ = prime_[primeIdx];
		Bucket* p = new Bucket[tableSize_];
		//把旧表中的数据重新哈希到新表
		for (int i = 0; i < prime_[primeIdx - 1]; i++)
		{
			if (Table_[i].state_ != STATE_USING)
				continue;
			int idx = Table_[i].key_ % tableSize_;
			int j = idx;
			do
			{
				if (p[j].state_ != STATE_USING)
				{
					p[j] = Table_[i];
					break;
				}
				j = (j + 1) % tableSize_;
			} while (j != idx);
		}
		delete[]Table_;
		Table_ = p;
		p = nullptr;
	}
public:
	HashTable(double factor = 0.75, int size = 3)
		: useBucketNum_(0)
		, loadFactor_(factor)
		, primeIdx(0)
	{
		//表长度
		if (size != prime_[0])
		{
			for (; primeIdx < PRIME_SIZE; primeIdx++)
			{
				if (prime_[primeIdx] >= size)
				{
					break;
				}
			}
			if (primeIdx == PRIME_SIZE)
			{
				primeIdx--;
			}
		}
		tableSize_ = prime_[primeIdx];
		Table_ = new Bucket[tableSize_];
	}
    ~HashTable()  
    {  
       delete[] Table_;
       Table_ = nullptr; 
    }

	//插入元素
	bool insert(int key)
	{
		//达到负载因子进行扩容
		if (useBucketNum_ * 1.0 / tableSize_ >= loadFactor_)
		{
			// 扩容
			expand();
		}
		int idx = key % tableSize_;
		int i = idx;
		do
		{
			if (Table_[i].state_ != STATE_USING)
			{
				Table_[i] = Bucket(key,STATE_USING);
				useBucketNum_++;
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (i != idx);
		return false;
	}

	//删除元素
	void erase(int key)
	{
		int idx = key % tableSize_;
		int i = idx;
		do
		{
			if (Table_[i].key_ == key && Table_[i].state_ == STATE_USING)
			{
				Table_[i].state_ = STATE_DEL;
				useBucketNum_--;
			}
			i = (i + 1) % tableSize_;
		} while (Table_[i].state_ != STATE_UNUSE && i != idx);
	}

	//查找
	bool find(int key)
	{
		int idx = key % tableSize_;
		int i = idx;
		do
		{
			if (Table_[i].key_ == key && Table_[i].state_ == STATE_USING)
			{
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (Table_[i].state_ != STATE_UNUSE && i != idx);
		return false;
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