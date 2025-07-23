#include<iostream>
#include<math.h>
#include<vector>
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


#if 0
int arr[] = { 12,54,1,9,40 };
const int length = sizeof(arr) / sizeof(arr[0]);
int x[length] = { 0 }; // ��¼�Ƿ�ѡ��
int bestX[length] = { 0 }; // ��¼ѡ��
int sum = 0; // ѡ����֮��
int r = 0; // δѡ����֮��
unsigned int min = 0xFFFFFFFF; // ��С��ֵ

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

#endif


#if 0
//����һ������Ϊ2*n���ȵ����飬ѡ��n�����֣�ʹ����ѡ����֮�ͺ�δѡ����֮�Ͳ�ֵ��С
int arr[] = { 12,54,1,9,40,7,54,20 };
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;	//��¼��ѡ����
vector<int> bestX;	//��¼���Ž�
int sum = 0;	//��¼��ѡ����֮��
int r = 0;	//��¼δѡ������֮��
unsigned int min = 0xFFFFFFFF;	//��¼��ֵ
int cnt = 0;	//��¼�������ڵ����
int l = length;		//��¼���м�������ѡ��Ľڵ�


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

//����һ������arr��һ������number����arr��ѡ��һ�����֣�ʹ����������֮�͵���number
//Ҳ�п����Ҳ���
int arr[] = { 4,8,12,16,7,9,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 40;
vector<int> x; //��¼ѡ�������
vector<int> bestX; //��¼���Ž�
int sum = 0; //��¼ѡ������֮��
int r = 0;	//��¼δ��������֮��
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