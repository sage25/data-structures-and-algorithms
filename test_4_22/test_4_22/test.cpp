#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;


//��ż���Ƶ���ߣ������Ƶ��ұ�
void sort(int arr[], int size)
{
	int* p = arr;  //��ָ��
	int* q = arr + size - 1;  //��ָ��
	int tmp = 0;
	while (p < q)
	{
		if ((*p & 0x01) == 0) //��������ż��������
		{
			p++;
			continue;
		}
		if ((*q & 0x01) == 1) ////����ұ�������������
		{
			q--;
			continue;
		}
		tmp = *p;
		*p = *q;
		*q = tmp;
		p++;
		q--;
	}

}

int main()
{
	srand((unsigned)time(0));
	int arr[10] = { 0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	for (int &i : arr)
	{
		i = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	sort(arr, size);
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}
