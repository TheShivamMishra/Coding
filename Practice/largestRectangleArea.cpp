#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#define vi vector<int>
#define vb vector<bool>
#define lli long long int
#define vvi vector<vector<int>>
#define loop(n) for (int i = 0; i < n; i++)
using namespace std;

int largestAreaInHistogram(vi &arr)
{
    int maxArea = 0;
    stack<int> st;
    st.push(-1);
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        while (st.top() != -1 && arr[st.top()] >= arr[i])
        {
            int h = arr[st.top()];
            st.pop();
            maxArea = max(maxArea, h * (i - st.top() - 1));
        }
        st.push(i);
    }

    while (st.top() != -1)
    {
        int h = arr[st.top()];
        st.pop();
        maxArea = max(maxArea, h * (n - st.top() - 1));
    }
    return maxArea;
}

int solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    for (int i = 1; i < n; i++) // building the board to run maxAreaInHistogram on each.
        for (int j = 0; j < m; j++)
            if (board[i][j] == 1)
                board[i][j] += board[i - 1][j];

    int myans = 0;

    for (vi &arr : board)
        myans = max(myans, largestAreaInHistogram(arr));

    return myans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        cout << solve() << endl;
    }
    return 0;
}