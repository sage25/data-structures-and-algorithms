/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 */

// @lc code=start
class Solution {
public:
    int oper(char ch, int num1, int num2)
    {
        switch(ch)
        {
            case '+': return num2 + num1;
            case '-': return num2 - num1;
            case '*': return num2 * num1;
            case '/': return num2 / num1;
        }
        throw "";
    }
    int evalRPN(vector<string>& tokens) {
        stack<int>num;
        for(string ch : tokens)
        {
            if(ch.size() == 1 &&
                (ch[0] == '+' 
                || ch[0] == '-' 
                || ch[0] == '*' 
                || ch[0] == '/'))
            {
                int num1 = num.top();
                num.pop();
                int num2 = num.top();
                num.pop();
                int a = oper(ch[0] , num1, num2);
                num.push(a);
            }
            else
            {
                num.push(stoi(ch));
            }
        }
        return num.top();
    }
};
// @lc code=end

