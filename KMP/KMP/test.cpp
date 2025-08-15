#include<iostream>
#include<string>
#include<memory>
using namespace std;

//BFËã·¨±©Á¦ËÑË÷×Ö·û´®
int BF(string s, string t)
{
	int i = 0;
	int j = 0;
	while (i < s.size() && j < t.size())
	{
		if (s[i] == t[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == t.size())
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}

int* getNext(string t)
{
	int* next = new int[t.size()];
	int j = 0;
	int k = -1;
	next[0] = -1;
	while (j < (int)t.size() - 1)
	{
		if (-1 == k || t[j] == t[k])
		{
			++j;
			++k;
			if (t[k] == t[j])
			{
				next[j] = next[k];
			}
			else
			{
				next[j] = k;
			}
		}
		else
		{
			k = next[k];
		}
	}
	return next;
}

int KMP(string s, string t)
{
	int i = 0;
	int j = 0;
	int* next = getNext(t);
	unique_ptr<int> ptr(next);
	while (i < (int)s.size() && j < (int)t.size())
	{
		if (j == -1 || s[i] == t[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == t.size())
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}

int main()
{
	string s = "labcabab";
	string t = "abcab";
	int idx = KMP(s, t);
	cout << idx << endl;

	return 0;
}