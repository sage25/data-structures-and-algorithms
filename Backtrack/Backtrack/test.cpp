#include<iostream>
#include<math.h>
using namespace std;

#if 0
//Ѱ�Ҽ������Ӽ�
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

int arr[] = { 12,54,1,9,40 };
const int length = sizeof(arr) / sizeof(arr[0]);
int x[length] = { 0 }; // ��¼�Ƿ�ѡ��
int bestX[length] = { 0 }; // ��¼ѡ��
int sum = 0; // ѡ����֮��
int r = 0; // δѡ����֮��
int min = 0xFFFF; // ��С��ֵ

//��ѡ���Ӽ���δѡ���Ӽ���С�͵Ĳ�ֵ
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