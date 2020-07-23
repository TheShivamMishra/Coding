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

// Leetcode 96.
int numTrees(int n)
{
    //Catlan no solution
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }
    return dp[n];
}

int findLongestRepeatingSubSeq(string &X, int m, int n, vvi &dp)
{

    if (dp[m][n] != -1)
        return dp[m][n];

    // return if we have reached the end of either string
    if (m == 0 || n == 0)
        return dp[m][n] = 0;

    // if characters at index m and n matches
    // and index is different
    if (X[m - 1] == X[n - 1] && m != n)
        return dp[m][n] = findLongestRepeatingSubSeq(X,
                                                     m - 1, n - 1, dp) +
                          1;

    // else if characters at index m and n don't match
    return dp[m][n] = max(findLongestRepeatingSubSeq(X, m, n - 1, dp),
                          findLongestRepeatingSubSeq(X, m - 1, n, dp));
}

int solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    string rstr = string(str.rbegin(), str.rend());
    vvi dp(n + 1, vi(n + 1, -1));
    return findLongestRepeatingSubSeq(str, n, n, dp);
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