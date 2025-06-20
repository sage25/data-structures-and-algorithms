#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

void sort(int arr[], int size)
{
	// 最大值的绝对值
	int max = abs(arr[0]);
	for (int i = 1; i < size; i++)
	{
		if (abs(arr[i]) > max)
		{
			max = arr[i];
		}
	}
	// 最大位数
	int len = to_string(max).size();
	vector<vector<int>>bucket;
	int mod = 10;
	int dev = 1;
	for (int i = 0; i < len; i++, mod *= 10, dev *= 10)
	{
		bucket.resize(20);
		for (int j = 0; j < size; j++)
		{
			int index = arr[j] % mod / dev + 10;
			bucket[index].push_back(arr[j]);
		}
		int idx = 0;
		for (int j = 0; j < 20; j++) 
		{
			for (int k = 0; k < bucket[j].size(); k++) 
			{
				arr[idx] = bucket[j][k];
				idx++;
			}
		}
		bucket.clear();
	}
}

int main()
{
	srand((unsigned int)time(0));
	int arr[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
		cout << arr[i] << ' ';
	}
	cout << endl;
	arr[6] = -45;
	arr[9] = -135;
	sort(arr, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}