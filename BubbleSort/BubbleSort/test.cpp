#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void sort(int* arr, int size)
{
	int tmp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

int main()
{
	srand((unsigned)time(0));
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}
	for (int i : arr)
		cout << i << ' ';
	cout << endl;
	sort(arr, 10);
	for (int i : arr)
		cout << i << ' ';
	return 0;
}