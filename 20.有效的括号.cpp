/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2 == 1)
            return false;
        else
        {
            stack<char>sc;
            for(char ch : s)
            {
                if(ch == '('
                    ||ch == '{'
                    ||ch == '['
                    )
                {
                    sc.push(ch);
                }
                else
                {
                    if(sc.empty())
                    {
                        return false;
                    }
                    if(
                        (ch == ')' && sc.top() == '(')
                        ||(ch == '}' && sc.top() == '{')
                        ||(ch == ']' && sc.top() == '[')
                        )
                    {
                        sc.pop();
                        continue;
                    }
                    else
                        return false;
                }
            }
            return sc.empty();
        }
    }
};
// @lc code=end

