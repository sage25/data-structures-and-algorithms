#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void quicksort(int* arr, int size)
{
	int left = 0; 
	int right = size - 1;
	int val = arr[left];
	if (size <= 1)
		return;
	else
	{
		while (left < right)
		{
			while (left < right && arr[right] >= val)
				right--;
			if (arr[right] < val)
				arr[left++] = arr[right];

			while (left < right && arr[left] <= val)
				left++;
			if (arr[left] > val)
				arr[right--] = arr[left];
		}
		arr[left] = val;
	}
	quicksort(arr, left);
	quicksort(arr + left + 1, size - left - 1);
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

	quicksort(arr, 10);

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}