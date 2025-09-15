#include<iostream>
using std::cout;
using std::cin;
using std::endl;

int parent[] = { 0,1,2,3,4,5,6,7,8 };
const int N = sizeof(parent) / sizeof(parent[0]);
int rank[] = { 1,1,1,1,1,1,1,1,1 };

//find优化
int non_find(int  x)
{
	int pos = x;
	while (x != parent[x])
	{
		x = parent[x];
	}
	parent[pos] = x;
	return x;
}

//递归实现(find优化)
int find(int  x)
{
	if (x == parent[x])
	{
		return x;
	}
	return parent[x] = find(parent[x]);
}

//权值优化
void merge(int x, int y)
{
	int a = find(x);
	int b = find(y);

	if (a != b)
	{
		if (rank[a] > rank[b])
		{
			parent[b] = a;
		}
		else
		{
			if (rank[a] == rank[b])
			{
				rank[a]++;
			}
			parent[a] = b;
		}
	}
}

int main()
{
	int x, y;
	for (int i = 0; i < 6; ++i)
	{
		cin >> x >> y;
		merge(x, y);
	}
	cout << (find(8) == find(7) ? "yes" : "No") << endl;;

	for (int i : parent)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}