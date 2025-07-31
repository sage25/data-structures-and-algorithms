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

/*
dp[i] = min({dp[i-1]+1, dp[i-3]+1, dp[i-5]+1})
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