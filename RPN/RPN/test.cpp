#include<iostream>
#include<stack>
using namespace std;
// 中缀表达式转后缀表达式(逆波兰表达式)
// 1 + (2 - 3) * 4 / 5


bool priority(char ch, char topch)
{
	// 当ch 优先级高于topch 时，true
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
		// 处理数字
		if ('0' <= ch && ch <= '9')
			result.push_back(ch);
		// 处理运算符
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