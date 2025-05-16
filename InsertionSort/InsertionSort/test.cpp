#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void sort(int* arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int tmp = arr[i];
		int j = i - 1;
		for (; j >= 0; j--)
		{
			if (tmp > arr[j])
				break;
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = tmp;
	}
}

void show(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
		cout << arr[i] << ' ';
	cout << endl;
}

int main()
{
	srand((unsigned)time(nullptr));
	int arr[10];
	int size = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
		
	show(arr, size);
	sort(arr, size);
	show(arr, size);
	return 0;
}