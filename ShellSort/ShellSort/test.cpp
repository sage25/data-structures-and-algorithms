#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void shellsort(int* arr, int size)
{
	for (int gap = size / 2; gap != 0; gap /= 2)
	{
		for (int i = gap; i < size; i++)
		{
			int j = i - gap;
			int tmp = arr[i];
			for (; j >= 0; j -= gap)
			{
				if (tmp > arr[j])
					break;
				arr[j + gap] = arr[j];
			}
			arr[j + gap] = tmp;
		}
	}
}

int main()
{
	srand((unsigned)time(nullptr));
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
		cout << arr[i] << ' ';
	}
	cout << endl;
	shellsort(arr, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}