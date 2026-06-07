// Last updated: 6/7/2026, 11:26:45 PM
class MinStack {
public:
    stack<int> st1,st2;
    MinStack() {
        while(!st1.empty())
        {
            st1.pop();
        }
        while(!st2.empty())
        {
            st2.pop();
        }
    }
    
    void push(int val) {
        if(!st2.empty())
        {
            if(val<=st2.top())
            {
                st2.push(val);
            }
        }
        else
        {
            st2.push(val);
        }
        st1.push(val);
    }
    
    void pop() {
        if(st1.top()==st2.top())
        {
            st1.pop();
            st2.pop();
        }
        else
        {
            st1.pop();
        }
    }
    
    int top() {
        return st1.top();
    }
    
    int getMin() {
        return st2.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */