#include "bits/stdc++.h"
#define vi vector<int>
#define vb vector<bool>
#define lli long long int
#define vvi vector<vector<int>>
#define loop(n) for (int i = 0; i < n; i++)
using namespace std;

auto SpeedUp = []() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // std::ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
    return 0;
}();

//  code for 0/1 kanpsack using idx and value to store min weigth req to get that value;
int knapSack(vi &weg, vi &value, int n, int w, int tval, vector<vector<lli>> &dp)
{
    //dp[idx][val] = it will store the min weght to require to get this value;
    dp[0][0] = 0;
    for (int idx = 1; idx <= n; idx++)
    {
        dp[idx][0] = 0; // by not thaking any object thus obtaning 0 value;
        for (int val = 1; val <= tval; val++)
        {
            dp[idx][val] = dp[idx - 1][val]; //not taking current object;

            if (val >= value[idx - 1])
                dp[idx][val] = min(dp[idx][val], dp[idx - 1][val - value[idx - 1]] + weg[idx - 1]);
        }
    }

    for (int val = tval; val >= 0; val--)
        if (dp[n][val] <= w)
            return val;
}

int solve()
{
    int n, w;
    scanf("%d%d", &n, &w);
    vi weg(n, 0), val(n, 0);
    int tval = 0;
    loop(n)
    {
        scanf("%d", &weg[i]);
        scanf("%d", &val[i]);
        tval += val[i];
    }

    vector<vector<lli>> dp(n + 1, vector<lli>(tval + 1, 1e9));
    return knapSack(weg, val, n, w, tval, dp);
}

int main()
{

    printf("%d\n", solve());
    return 0;
}