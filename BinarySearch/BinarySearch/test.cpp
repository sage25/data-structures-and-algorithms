#include<iostream>
using namespace std;


// 二分查找算法
int serch(int* arr, int val, int size)
{
	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
 		if (arr[middle] < val)
		{
			left = middle + 1;
		}
		else if(arr[middle] > val)
		{
			right = middle - 1;
		}
		else
		{
			return middle;
		}
	}
	return -1;
}


int Rserch(int* arr, int val, int size)
{
	int left = 0;
	int right = size - 1;
	int middle = (left + right) / 2;
	if (arr[middle] < val)
		return middle + 1 + Rserch(arr + middle + 1, val, size - middle - 1);
	else if (arr[middle] > val)
		return Rserch(arr, val, middle);
	else if (arr[middle] == val)
		return middle;
	else
		throw "waring!";
}


int main()
{

	int arr[10] = {0, 12, 37, 65, 74, 75, 85, 88, 88, 100};
	int size = sizeof(arr) / sizeof(arr[0]);
	cout << Rserch(arr, 37, size) << endl;
	cout << Rserch(arr, 0, size) << endl;
	cout << Rserch(arr, 88, size) << endl;
	cout << Rserch(arr, 85, size) << endl;
	//cout << Rserch(arr, 101, size) << endl;
	return 0;
}