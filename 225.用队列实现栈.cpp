// @before-stub-for-debug-begin
#include <vector>
#include <string>
#include <Queue>
#include "commoncppproblem225.h"

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=225 lang=cpp
 *
 * [225] 用队列实现栈
 */

// @lc code=start
class MyStack {
public:
    MyStack() {
        
    }
    
    void push(int x) {
        s1.push(x);
        while(!s2.empty())
        {
            s1.push(s2.front());
            s2.pop();
        }
        swap(s1,s2);
    }
    
    int pop() {
        int result = s2.front();
        s2.pop();
        return result;
    }
    
    int top() {
        return s2.front();
    }
    
    bool empty() {
        return s2.empty();
    }
private:
    queue<int> s1;
    queue<int> s2;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end

