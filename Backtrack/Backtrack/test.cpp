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


#if 0
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

#endif

#if 0
int arr[] = { 4,5,6,7 };
int number = 10;
const int length = sizeof(arr) / sizeof(arr[0]);
int sum = 0; //记录选择的数之和
vector<int> x; //记录选择的数

void func(int i)
{
	if (i == length || sum == number)
	{
		if (sum != number)
		{
			return;
		}
		else
		{
			for (int v : x)
			{
				cout << v << ' ';
			}
			cout << endl;
		}
	}
	else
	{
		for (int j = i; j < length; j++)
		{
			if (sum <= number)
			{
				sum += arr[j];
				x.push_back(arr[j]);
				func(j);
				x.pop_back();
				sum -= arr[j];
			}
			
		}
	}
}

int main()
{
	func(0);

	return 0;
}
#endif

//0-1背包问题：有一组物品，其重量分别是：w1,w2,w3,...,wn，其价值分别是：v1,v2,v3,...,vn
//现在有一个背包，其容量是C，问：怎么把物品装入背包能够使价值最大化？
int w[] = { 12,5,8,9,6 }; // 物品重量
int v[] = { 9,2,4,7,8 }; // 物品价值
const int length = sizeof(w) / sizeof(w[0]);
int c = 20;	// 背包容量
int sumOfW = 0; // 所选物品重量之和
int sumOfV = 0; // 所选物品价值之和
vector<int> x;  // 所选物品
vector<int> bestX;	//最优解
int max = 0;	// 记录最优解的价值
int r = 0; // 未处理物品的价值

void func(int i)
{
	if (i == length)
	{
		if (sumOfW > c)
		{
			return;
		}
		if (::max < sumOfV)
		{
			::max = sumOfV;
			bestX = x;
		}
	}
	else
	{
		r -= v[i];
		if (sumOfW + w[i] <= 20)
		{
			sumOfW += w[i];
			sumOfV += v[i];
			x.push_back(w[i]);
			func(i + 1);
			x.pop_back();
			sumOfW -= w[i];
			sumOfV -= v[i];
		}
		
		if (r + sumOfV >= ::max)
		{
			func(i + 1);
		}
		r += v[i];
	}
}

int main()
{
	for (int i : v)
	{
		r += i;
	}
	func(0);
	for (int i : bestX)
	{
		cout << i << ' ';
	}
	cout << endl;
	return 0;
}