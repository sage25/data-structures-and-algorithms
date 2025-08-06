#include<iostream>
#include<math.h>
#include<vector>
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

#if 0
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
#endif

//LCS:公共子序列问题求解
string X = "helloworld";
string Y = "hlweord";
int len1 = X.size();
int len2 = Y.size();
int** dp = nullptr;
#if 0
int func(const string& X, int n, const string& Y, int m)
{
    if (n < 0 || m < 0)
    {
        return 0;
    }

    if (dp[n][m] != -1)
    {
        return dp[n][m];
    }

    if (X[n] == Y[m])
    {
        dp[n][m] = 1 + func(X, n - 1, Y, m - 1);
        return dp[n][m];
    }
    else
    {
        int l1 = func(X, n - 1, Y, m); //往上面走
        int l2 = func(X, n, Y, m - 1); //往左面走
        dp[n][m] = max(l1, l2);
        return dp[n][m];
    }
}
int main()
{
    dp = new int* [len1];
    for (int i = 0; i < len1; ++i)
    {
        dp[i] = new int[len2];
        for (int j = 0; j < len2; ++j)
        {
            dp[i][j] = 0;
        }
    }

    int result = func1(X, len1 - 1, Y, len2 - 1);
    cout << "result:" << result << endl;

    return 0;
}
#endif

#if 0
int func1(const string& X, int n, const string& Y, int m)
{
    for (int i = 1; i <= n + 1; ++i)
    {
        for (int j = 1; j <= m + 1; ++j)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                int l1 = dp[i - 1][j]; //从上面来
                int l2 = dp[i][j - 1]; //从左边来
                dp[i][j] = max(l1, l2);
            }
        }
    }
    return dp[n + 1][m + 1];
}

int main()
{
    dp = new int* [len1 + 1];
    for (int i = 0; i < len1 + 1; ++i)
    {
        dp[i] = new int[len2 + 1];
        for (int j = 0; j < len2 + 1; ++j)
        {
            dp[i][j] = 0;
        }
    }

    int result = func1(X, len1 - 1, Y, len2 - 1);
    cout << "result:" << result << endl;

    return 0;
}
#endif

/*
三角数组求和问题:求自顶向下数字之和最小的路线
        [2]
       [3,4]
      [6,5,7]
     [4,1,8,3]

dp[i][j]:i表示行数，j表示列数，dp[i][j]表示从顶部到当前数字之和
*/

int func(const vector<vector<int>>& vec, int** dp, int n)
{
    for (int i = 0; i < vec.size() - 1; ++i)
    {
        dp[n][i] = vec[n][i];
    }

    for (int i = vec.size() - 2; i >= 0; --i)
    {
        for (int j = 0; j < vec[i].size(); ++j)
        {
            dp[i][j] = min(vec[i][j] + dp[i + 1][j], vec[i][j] + dp[i + 1][j + 1]);
        }
    }
    return dp[0][0];
}

int main()  
{  
   vector<int> v1{ 2 };  
   vector<int> v2{ 3,4 };  
   vector<int> v3{ 6,5,7 };  
   vector<int> v4{ 4,1,8,3 };  
   vector<vector<int>> vec{ v1,v2,v3,v4 };  
   int** dp = new int* [vec.size()];  
   for (int i = 0; i < vec.size(); ++i)  
   {  
       dp[i] = new int[vec[i].size()];
       for (int j = 0; j < vec[i].size(); ++j)  
       {  
           dp[i][j] = 0;  
       }  
   }  
   dp[0][0] = vec[0][0];  
   int result = func(vec, dp, vec.size() - 1);
   cout << "result:" << result << endl;  

   return 0;  
}
