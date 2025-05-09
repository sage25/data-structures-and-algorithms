#include<iostream>
#include<stack>
using namespace std;
// ��׺���ʽת��׺���ʽ(�沨�����ʽ)
// 1 + (2 - 3) * 4 / 5


bool priority(char ch, char topch)
{
	// ��ch ���ȼ�����topch ʱ��true
	if ((ch == '*' || ch == '/') && topch == '+' || ch == '-')
		return true;
	return false;
}


string RPN(string s)
{
	string result = "";
	stack<char>oper;
	for (char ch : s)
	{
		// ��������
		if ('0' <= ch && ch <= '9')
			result.push_back(ch);
		// ���������
		else
		{
			if (ch == '(' || oper.empty())
				oper.push(ch);
			else if (ch == ')')
			{
				while (oper.top() != '(')
				{
					result.push_back(oper.top());
					oper.pop();
				}
				oper.pop();
			}
			else
			{
				char topch = oper.top();
				if (priority(ch, topch))
				{
					oper.push(ch);
				}
				else
				{
					result.push_back(topch);
					oper.pop();
					oper.push(ch);
				}
			}		
		}	
	}
	while (!oper.empty())
	{
		result.push_back(oper.top());
		oper.pop();
	}
	return result;
}

int main()
{
	string s = "1+(2-3)*4/5";
	cout << RPN(s) << endl;
	return 0;
}