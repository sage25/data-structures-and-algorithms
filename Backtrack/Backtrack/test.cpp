#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

#if 0
//寻找集合中子集
void func(int arr[], int i, int length, int x[])
{
	if (length == i)
	{
		for (int j = 0; j < length; j++)
		{
			if (x[j] == 1)
			{
				cout << arr[j] << ' ';
			}
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;
		func(arr, i + 1, length, x);

		x[i] = 0;
		func(arr, i + 1, length, x);
	}
}

int main()
{
	int arr[] = { 1,2,3 };
	const int length = sizeof(arr) / sizeof(arr[0]);
	int x[length] = { 0 };
	func(arr, 0, length, x);
	return 0;
}
#endif


#if 0
int arr[] = { 12,54,1,9,40 };
const int length = sizeof(arr) / sizeof(arr[0]);
int x[length] = { 0 }; // 记录是否选择
int bestX[length] = { 0 }; // 记录选择
int sum = 0; // 选择数之和
int r = 0; // 未选择数之和
unsigned int min = 0xFFFFFFFF; // 最小差值

//已选择子集和未选择子集最小和的差值
void func(int i)
{
	if (length == i)
	{
		if (abs(sum - r) < ::min)
		{
			::min = abs(sum - r);
			for (int j = 0; j < length; j++)
			{
				bestX[j] = x[j];
			}
		}
	}
	else
	{
		x[i] = 1;
		r -= arr[i];
		sum += arr[i];
		func(i + 1);
		sum -= arr[i];
		r += arr[i];

		x[i] = 0;
		func(i + 1);
	}
}

int main()
{
	for (int i = 0; i < length; i++)
	{
		r += arr[i];
	}
	func(0);
	for (int j : bestX)
	{
		cout << j << ' ';
	}
	cout << endl;
	cout << ::min << endl;
	return 0;
}

#endif


#if 0
//给定一个长度为2*n长度的数组，选定n个数字，使得所选数字之和和未选数字之和差值最小
int arr[] = { 12,54,1,9,40,7,54,20 };
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;	//记录所选数字
vector<int> bestX;	//记录最优解
int sum = 0;	//记录所选数字之和
int r = 0;	//记录未选择数字之和
unsigned int min = 0xFFFFFFFF;	//记录差值
int cnt = 0;	//记录到树根节点次数
int l = length;		//记录还有几个可以选择的节点


void func(int i)
{
	if (i == length)
	{
		cnt++;
		if (x.size() == length / 2 && abs(sum - r) < ::min)
		{
			::min = abs(sum - r);
			bestX = x;
		}
	}
	else
	{
		l--;
		if (x.size() < length / 2)
		{
			x.push_back(arr[i]);
			sum += arr[i];
			r -= arr[i];
			func(i + 1);
			x.pop_back();
			sum -= arr[i];
			r += arr[i];
		}

		if (l + x.size() >= length / 2)
		{
			func(i + 1);
		}
		l++;
	}
 }

int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	for (int v : bestX)
	{
		cout << v << ' ';
	}
	cout << endl;
	cout << "min:" << ::min  << ' ' << "cnt:" << cnt << endl;
	return 0;
}

#endif

//给定一个数组arr和一个数字number，从arr中选出一组数字，使得这组数字之和等于number
//也有可能找不到
int arr[] = { 4,8,12,16,7,9,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 40;
vector<int> x; //记录选择的数字
vector<int> bestX; //记录最优解
int sum = 0; //记录选择数字之和
int r = 0;	//记录未处理数字之和
int cnt = 0;

void func(int i)
{
	if (i == length)
	{
		cnt++;
		if (sum == number)
		{
			bestX = x;
		}
	}
	else
	{
		r -= arr[i];
		if (sum + arr[i] <= number)
		{
			sum += arr[i];
			x.push_back(arr[i]);
			func(i + 1);
			sum -= arr[i];
			x.pop_back();
		}

		if (sum + r >= number)
		{
			func(i + 1);
		}
		r += arr[i];
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	for (int v : bestX)
	{
		cout << v << ' ';
	}
	cout << endl;
	cout << "cnt:" << cnt << endl;
	return 0;
}