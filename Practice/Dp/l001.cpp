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
using namespace std;

// www.geeksforgeeks.org/dynamic-programming-set-11-egg-dropping-puzzle/
int minSteps(int n, int k, vvi &dp)
{
    if (k == 0 || k == 1)
        return dp[n][k] = k;

    if (n == 1)
        return dp[n][k] = k;

    int myans = -1e9, ans = 1e9;
    for (int i = 1; i <= k; i++)
    {
        myans = max(minSteps(n - 1, k - 1, dp), minSteps(n, k - i, dp));
        if (ans > myans)
            ans = myans;
    }
    dp[n][k] = ans + 1;
}

int EggDops()
{
    int n, k;
    cin >> n >> k;
    vvi dp(n + 1, vi(k + 1, -1));
    return minSteps(n, k, dp);
}

int solve()
{
    return 0;
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