#include <iostream>
#include <vector>

using namespace std;

class Mystack
{
    int sz = 0;
    int *arr;
    int N = 1000;
    int tos = -1;

public:
    Mystack()
    {
        arr = new int[N];
    }

    Mystack(int sz)
    {
        N = sz;
        arr = new int[sz];
    }

    int size()
    {
        return this->sz;
    }

    bool empty()
    {
        return this->sz == 0;
    }

    void push(int val)
    {
        if (sz > N)
            return;
        this->tos++;
        this->arr[tos] = val;
        sz++;
    }

    int top()
    {
        if (sz < 1 || sz > N)
            return -1;
        return this->arr[tos];
    }

    void pop()
    {
        if (sz < 1)
            return;
        int rv = this->arr[tos];
        this->tos--;
        this->sz--;
    }
};

void solve()
{
    Mystack st(10);
    for (int i = 1; i <= 10; i++)
        st.push(i * 10);
    for (int i = 0; i < 10; i++)
    {
        cout << st.top() << endl;
        st.pop();
    }
}

int main()
{
    solve();
    return 0;
}