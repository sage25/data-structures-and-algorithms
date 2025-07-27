/* 分治算法 */
#include<list>
#include<vector>
#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

#if 0
//合并k个有序链表
list<int>* mergeTwoLink(list<int>* left, list<int>* right)
{
	list<int>* temp = new list<int>;
	auto it = left->begin();
	auto ir = right->begin();
	while (it != left->end() && ir != right->end())
	{
		if (*it >= *ir)
		{
			temp->push_back(*ir++);
		}
		else
		{
			temp->push_back(*it++);
		}
	}

	while (it != left->end())
	{
		temp->push_back(*it++);
	}

	while (ir != right->end())
	{
		temp->push_back(*ir++);
	}

	return temp;
}

list<int>* mergeLink(vector<list<int>*> vec, int low, int high)
{
	if (low == high)
	{
		return vec[low];
	}
	else
	{
		int mid = (low + high) / 2;
		list<int>* left = mergeLink(vec, low, mid);
		list<int>* right = mergeLink(vec, mid + 1, high);

		return mergeTwoLink(left, right);
	}
}

int main()
{
	list<int> x1{ 1,6,10,24,66 };
	list<int> x2{ 7,31,50 };
	list<int> x3{ 0,2,3,40};
	list<int> x4{1,58,66};
	vector<list<int>*> vec{ &x1,&x2,&x3,&x4 };

	list<int>* p = mergeLink(vec, 0, vec.size() - 1);

	for (auto it = p->begin(); it != p->end(); it++)
	{
		cout << *it << ' ';
	}
	
	cout << endl;

	return 0;
}
#endif

//求两个有序数组的中位数，时间复杂度为log(n+m)
double func(int arr[], int brr[], int n, int m)
{
	if (n > m)
	{
		return func(brr, arr, m, n);
	}
	if (n == 0)
	{
		int k = (m - 1) / 2;
		if (m % 2 == 0)
		{
			return (brr[k] + brr[k + 1]) * 1.0 / 2;
		}
		else
		{
			return brr[k];
		}
	}
	

	int k = (n + m + 1) / 2;
	int i = 0;
	int j = 0;
	int begin = 0;
	int end = n;
	while (true)
	{
		i = (begin + end) / 2;
		j = k - i;
		if (i > 0 && j < m && arr[i - 1] > brr[j])
		{
			end = i - 1;
		}
		else if (j > 0 && i < n && brr[j - 1] > arr[i])
		{
			begin = i + 1;
		}
		else
		{
			break;
		}
	}

	int left = 0;
	if (i == 0)
	{
		left = brr[j - 1];
	}
	else if (j == 0)
	{
		left = arr[i - 1];
	}
	else
	{
		left = max(arr[i - 1], brr[j - 1]);
	}

	int right = 0;
	if (i == n)
	{
		right = brr[j];
	}
	else if (j == m)
	{
		right = arr[i];
	}
	else
	{
		right = min(arr[i], brr[j]);
	}

	if ((m + n) % 2 == 0)
	{
		return (left + right) * 1.0 / 2;
	}
	else
	{
		return left;
	}

}


int main()
{
	int arr[] = { 1,3,5,9,11,17 };
	int brr[] = { 2,5,8,10,11,14,17,20 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int m = sizeof(brr) / sizeof(brr[0]);

	double result = func(arr, brr, m, n);

	vector<int> vec;

	for (int i : arr)
	{
		vec.push_back(i);
	}
	for (int j : brr)
	{
		vec.push_back(j);
	}
	sort(vec.begin(), vec.end());
	for (int v : vec)
	{
		cout << v << ' ';
	}
	cout << endl;
	cout << "result:" << result << endl;
	return 0;
}