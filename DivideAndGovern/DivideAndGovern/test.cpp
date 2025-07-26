/* 分治算法 */
#include<list>
#include<vector>
#include<iostream>
#include<math.h>
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
int func(int arr[], int i, int j, int brr[], int l, int r, int k)
{
	if (arr[i + 1] > brr[l] && brr[l + 1] > arr[i])
	{
		return max(arr[i], brr[l]);
	}
	else
	{
		if (arr[i + 1] < brr[l]) //arr往右边走，brr往左边走
		{
			return func(arr, (i + j) / 2, j, brr, l, (l + r) / 2, k);
		}
		if (brr[l + 1] < arr[i]) //arr往左边走，brr往右边走
		{
			return func(arr, i, (i + j) / 2, brr, (l + r) / 2, r, k);
		}
	}
}

int main()
{
	int arr[] = { 1,3,5,8,11,17 };
	int brr[] = { 2,5,8,10,11,14,17,20 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int m = sizeof(brr) / sizeof(brr[0]);
	int k = (m + n + 1) / 2;

	int result = func(arr, 0, n - 1, brr, 0, m - 1, k);

	cout << "result:" << result << endl;
	return 0;
}