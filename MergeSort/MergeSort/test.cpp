#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void merge(int* arr, int l, int m, int r)
{
	int* p = new int[r - l + 1];
	int index = 0;
	int i = l;
	int j = m + 1;
	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			p[index++] = arr[i++];
		}
		else
		{
			p[index++] = arr[j++];
		}
	}
	while (i <= m)
	{
		p[index++] = arr[i++];
	}
	while (j <= r)
	{
		p[index++] = arr[j++];
	}
	for (i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}

	delete[] p;
}

void mergesort(int* arr, int begin, int end)
{
	if (begin >= end)
		return;
	else 
	{
		int mid = (begin + end) / 2;
		mergesort(arr, begin, mid);
		mergesort(arr, mid + 1, end);
		merge(arr, begin, mid, end);
	}
}

void mergesort(int* arr, int size)
{
	mergesort(arr, 0, size - 1);
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
	cout << endl;

	mergesort(arr, 10);

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}