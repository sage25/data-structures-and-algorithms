#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

//class Array
//{
//private:
//	void expand(int newsize) 
//	{
//		int* fp = new int[newsize];
//		memcpy(fp, p, sizeof(int)*count);
//		delete[]p;
//		p = fp;
//		size = newsize;
//	}
//private:
//	int size;
//	int* p;
//	int count;
//public:
//	Array(int msize = 10):size(msize),count(0)
//	{
//		p = new int[size]();
//	}
//	//Ä©Î²Ìí¼ÓÔªËØ
//	void endadd(int value)
//	{
//		if (count == size)
//		{
//			expand(2 * size);
//		}
//		p[count++] = value;
//	}
//	//Ä©Î²É¾³ýÔªËØ
//	void enddele()
//	{
//		count--;
//	}
//	//Ìí¼ÓÔªËØ
//	void add(int location, int value)
//	{
//		if (location > size || location < 0)
//		{
//			return;
//		}
//		if (count == size)
//		{
//			expand(2 * size);
//		}
//		for (int i = count; i > location; i--)
//		{
//			p[i] = p[i - 1];
//		}
//		p[location] = value;
//		count++;
//	}
//	//É¾³ýÔªËØ
//	void dele(int location)
//	{
//		if (location < 0 || location > size)
//		{
//			return;
//		}
//		for (int j = location; j < count; j++)
//		{
//			p[j] = p[j+1];
//		}
//		count--;
//	}
//	//²éÑ¯ÔªËØ
//	int find(int value)
//	{
//		for (int i = 0; i < count; i++)
//		{
//			if (p[i] == value)
//			{
//				return i;
//			}
//		}
//		return -1;
//	}
//	void show()
//	{
//		for (int i = 0; i < count; i++)
//		{
//			cout << p[i] << ' ';
//		}
//		cout << endl;
//	}
//
//	//Îö¹¹º¯Êý
//	~Array()
//	{
//		delete[] p;
//		p = nullptr;
//	}
//};
//
//
//
//
//int main()
//{
//	Array arr(15);
//	srand(time(0));
//	for (int i = 0; i < 15; i++)
//	{
//		arr.endadd(rand()%100);
//	}
//
//	arr.show();
//
//	arr.add(8 ,100);
//	arr.show();
//
//	arr.enddele();
//	arr.show();
//
//
//	arr.dele(5);
//	arr.show();
//
//	int n = arr.find(100);
//	if (n != -1)
//	{
//		cout << n << endl;
//	}
//	return 0;
//}

