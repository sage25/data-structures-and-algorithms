#include<iostream>
#include<math.h>
using namespace std;


/*
有面值为1、3、5分的硬币，要组成11分钱，问最少需要多少个硬币
*/
#if 0

int func(int i, int dp[])
{
	if (dp[i] != 0)
	{
		return dp[i];
	}

	if (i == 1 || i == 3 || i == 5)
	{
		dp[i] = 1;
		return 1;
	}
	else if (i == 2 || i == 4)
	{
		dp[i] = 2;
		return 2;
	}
	else
	{
		int ret1 = func(i - 1, dp) + 1;
		int ret2 = func(i - 3, dp) + 1;
		int ret3 = func(i - 5, dp) + 1;

		dp[i] = min({ ret1, ret2, ret3 });
		return dp[i];
	}
}

int main()
{
	const int i = 11;
	int dp[i + 1] = { 0 };
	int result = func(i, dp);

	cout << "result:" << result << endl;
	return 0;
}
#endif


#if 0
/*
状态转移方程：dp[i] = min({dp[i-1]+1, dp[i-3]+1, dp[i-5]+1})
*/
int func(int i, int dp[])
{
	dp[1] = dp[3] = dp[5] = 1;
	dp[2] = dp[4] = 2;
	for (int j = 1; j <= i; j++)
	{
		if (dp[j] == 0)
		{
			dp[j] = min({ dp[j - 1] + 1, dp[j - 3] + 1, dp[j - 5] + 1 });
		}
	}
	return dp[i];
}

int main()
{
	const int i = 18;
	int dp[i + 1] = { 0 };
	int result = func(i, dp);

	cout << "result:" << result << endl;
	return 0;
}

#endif


/*
LIS问题：求最长不降（升序）子数组
状态转移方程：dp[i] = arr[i] >= arr[i - 1] ? dp[i] = dp[i] + 1 : 1
*/
int func(int arr[], int length, int dp[])
{
	dp[0] = 1;
	int max = dp[0];
	for (int i = 1; i < length; ++i)
	{
		dp[i] = arr[i] >= arr[i - 1] ? dp[i] = dp[i - 1] + 1 : 1;
		if (dp[i] > max)
		{
			max = dp[i];
		}
	}
	return max;

}

int main()
{
	int arr[] = { 2,7,6,9,14,2,8 };
	const int length = sizeof(arr) / sizeof(arr[0]);
	int dp[length] = { 0 };
	int result = func(arr, length, dp);
	cout << "result:" << result << endl;
	return 0;
}