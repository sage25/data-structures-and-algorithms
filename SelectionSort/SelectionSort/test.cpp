#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void sort(int* arr, int size)
{
	int tmp;
	for (int begin = 0, end = size - 1; begin < end; begin++, end--)
	{
		int maxpos = end;
		int minpos = begin;
		for (int i = begin; i <= end; i++)
		{
			if (arr[i] < arr[minpos])
			{
				minpos = i;
			}
			if (arr[i] > arr[maxpos])
			{
				maxpos = i;
			}
		}
		if (begin != minpos)
			swap(arr[begin], arr[minpos]);
		if (maxpos == begin)
			maxpos = minpos;
		if (maxpos != end)
			swap(arr[end], arr[maxpos]);
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
	cout << endl;
	sort(arr, 10);
	for (int i : arr)
		cout << i << ' ';
	cout << endl;
	return 0;
}