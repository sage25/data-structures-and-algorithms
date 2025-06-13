#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void siftDown(int arr[], int size, int i)
{
	int val = arr[i];
	int childe = i * 2 + 1;
	while (childe < size)
	{
		if (childe + 1 < size && arr[childe + 1] > arr[childe])
		{
			childe = childe + 1;
		}
		if (arr[childe] > val)
		{
			arr[i] = arr[childe];
			i = childe;
			childe = i * 2 + 1;
		}
		else
		{
			break;
		}
	}
	arr[i] = val;
}

void sort(int arr[], int size)
{
	int n = size - 1;
	// 建堆
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		siftDown(arr, size, i);
	}
	for (int i = n; i > 0; i--)
	{
		// 交换第n个和第一个，
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		// 进行下沉
		siftDown(arr, i, 0);
	}
}


int main()
{
	srand((unsigned)time(0));
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
		cout << arr[i] << ' ';
	}
	cout << '\n';
	sort(arr, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << '\n';
	return 0;
}