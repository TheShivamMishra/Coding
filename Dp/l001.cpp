#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#define lli long long int
#define vi vector<int>
#define vvi vector<vector<int>>
using namespace std;

void display(vector<int> &dp)
{
    for (int ele : dp)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<int>> &dp)
{
    for (vector<int> &ar : dp)
    {
        for (int ele : ar)
            cout << ele << " ";
        cout << endl;
    }
    cout << endl;
}

// Fibonacci =====================================================
//memoizatio
int fibo(int n, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = n;
    if (dp[n] != 0)
        return dp[n];
    return dp[n] = fibo(n - 1, dp) + fibo(n - 2, dp);
}

//tabulation
int fiboDp(int N, vector<int> &dp)
{

    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = n;
            continue;
        }
        dp[n] = dp[n - 1] + dp[n - 2]; //fibo(n - 1, dp) + fibo(n - 2, dp);
    }
    return dp[N];
}

void set1()
{
    int n = 6;
    vi dp(n + 1, 0);
    cout << fibo(6, dp) << endl;
    cout << fiboDp(6, dp) << endl;
    display(dp);
}

//MazePathSeries.==============================================

int mazePathHV(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    if (sr + 1 <= er)
        count += mazePathHV(sr + 1, sc, er, ec, dp);

    if (sc + 1 <= ec)
        count += mazePathHV(sr, sc + 1, er, ec, dp);

    if (sr + 1 <= er && sc + 1 <= ec)
        count += mazePathHV(sr + 1, sc + 1, er, ec, dp);

    return dp[sr][sc] = count;
}

int mazePathHV_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{

    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if (sr + 1 <= er)
                count += dp[sr + 1][sc]; //mazePathHV(sr + 1, sc, er, ec, dp);

            if (sc + 1 <= ec)
                count += dp[sr][sc + 1]; //mazePathHV(sr, sc + 1, er, ec, dp);

            if (sr + 1 <= er && sc + 1 <= ec)
                count += dp[sr + 1][sc + 1]; //mazePathHV(sr + 1, sc + 1, er, ec, dp);

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int mazePathMulti(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
    {
        return dp[sr][sc] = 1;
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    for (int jump = 1; sr + jump <= er; jump++)
        count += mazePathMulti(sr + jump, sc, er, ec, dp);

    for (int jump = 1; sc + jump <= ec; jump++)
        count += mazePathMulti(sr, sc + jump, er, ec, dp);

    for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
        count += mazePathMulti(sr + jump, sc + jump, er, ec, dp);

    return dp[sr][sc] = count;
}

int mazePathMulti_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{

    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            for (int jump = 1; sr + jump <= er; jump++)
                count += dp[sr + jump][sc]; //mazePathMulti(sr + jump, sc, er, ec, dp);

            for (int jump = 1; sc + jump <= ec; jump++)
                count += dp[sr][sc + jump]; //mazePathMulti(sr, sc + jump, er, ec, dp);

            for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
                count += dp[sr + jump][sc + jump]; //mazePathMulti(sr + jump, sc + jump, er, ec, dp);

            dp[sr][sc] = count;
        }
    }

    return dp[0][0];
}

int boardPath(int sp, int ep, vector<int> &dp)
{
    if (sp == ep)
    {
        return dp[sp] = 1;
    }

    if (dp[sp] != 0)
        return dp[sp];

    int count = 0;
    for (int dice = 1; sp + dice <= ep && dice <= 6; dice++)
        count += boardPath(sp + dice, ep, dp);

    return dp[sp] = count;
}

int boardPathDP(int sp, int ep, vector<int> &dp)
{

    for (sp = ep; sp >= 0; sp--)
    {
        if (sp == ep)
        {
            dp[sp] = 1;
            continue;
        }

        int count = 0;
        for (int dice = 1; sp + dice <= ep && dice <= 6; dice++)
            count += dp[sp + dice]; //boardPath(sp + dice, ep, dp);
        dp[sp] = count;
    }

    return dp[0];
}

int boardPath_best(int sp, int ep)
{
    list<int> ll;
    for (sp = ep; sp >= 0; sp--)
    {
        if (sp > ep - 2)
        {
            ll.push_front(1);
            continue;
        }

        if (ll.size() <= 6)
            ll.push_front(2 * ll.front());
        else
        {
            ll.push_front(2 * ll.front() - ll.back());
            ll.pop_back();
        }
    }

    return ll.front();
}

int boardPathWithDiceArrayDP(int sp, int ep, vector<int> &dp, vector<int> &diceArray)
{

    for (sp = ep; sp >= 0; sp--)
    {
        if (sp == ep)
        {
            dp[sp] = 1;
            continue;
        }

        int count = 0;
        for (int dice = 0; sp + diceArray[dice] <= ep && dice < diceArray.size(); dice++)
            count += dp[sp + diceArray[dice]]; //boardPath(sp + dice, ep, dp);
        dp[sp] = count;
    }

    return dp[0];
}

//Leetcode 70.=================================================================================

int climbStairs_01(int n, vector<int> &dp)
{
    if (n <= 1)
    {
        return dp[n] = 1;
    }

    if (dp[n] != 0)
        return dp[n];

    int ans = climbStairs_01(n - 1, dp) + climbStairs_01(n - 2, dp);
    return dp[n] = ans;
}

int climbStairs_DP(int n, vector<int> &dp)
{
    int N = n;
    for (n = 0; n <= N; n++)
    {

        if (n <= 1)
        {
            dp[n] = 1;
            continue;
        }

        int ans = dp[n - 1] + dp[n - 2]; //climbStairs_01(n - 1, dp) + climbStairs_01(n - 2, dp);
        dp[n] = ans;
    }
    return dp[N];
}

int climbStairs_btr(int n)
{
    int a = 1;
    int b = 1;
    int sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}

int climbStairs(int n)
{
    vector<int> dp(n + 1, 0);
    // return climbStairs_01(n, dp);
    // return climbStairs_DP(n,dp);
    return climbStairs_btr(n);
}

int minCostClimbingStairs(int n, vector<int> &dp, vector<int> &cost)
{
    if (n <= 1)
    {
        return dp[n] = cost[n];
    }

    if (dp[n] != 0)
        return dp[n];

    int ans = min(minCostClimbingStairs(n - 1, dp, cost),
                  minCostClimbingStairs(n - 2, dp, cost));
    return dp[n] = ans + cost[n];
}

int minCostClimbingStairsDP(int n, vector<int> &dp, vector<int> &cost)
{
    int N = n;
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = cost[n];
            continue;
        }

        int ans = min(dp[n - 1], dp[n - 2]);
        dp[n] = ans + cost[n];
    }
    return dp[N];
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();

    cost.push_back(0);
    vector<int> dp(n + 1, 0);

    // return minCostClimbingStairs(n, dp, cost);
    return minCostClimbingStairsDP(n, dp, cost);
}

void pathSet()
{
    // int n = 3, m = 3;
    // vector<vector<int>> dp(n, vector<int>(m, 0));
    // cout << mazePathHV(0, 0, n - 1, m - 1, dp) << endl;
    // cout << mazePathHV_DP(0, 0, n - 1, m - 1, dp) << endl;
    // cout << mazePathMulti(0, 0, n - 1, m - 1, dp) << endl;
    // cout << mazePathMulti(0, 0, n - 1, m - 1, dp) << endl;

    // int sp = 0, ep = 10;
    // vector<int> dp(ep + 1, 0);
    // vector<int> diceArray{1, 2, 3, 4, 5, 6};
    // cout << boardPathDP(sp, ep, dp) << endl;
    // cout << boardPathWithDiceArrayDP(sp, ep, dp, diceArray) << endl;
    // cout << boardPath_best(sp, ep);

    // vector<vector<int>> grid = {{1, 3, 1, 5},
    //                             {2, 2, 4, 1},
    //                             {5, 0, 2, 3},
    //                             {0, 6, 1, 2}};
    // int n = grid.size(), m = grid[0].size();
    // vector<vector<int>> dp(n, vector<int>(m, 0));

    // int maxCoin = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     maxCoin = max(maxCoin, goldMin(i, 0, grid, dp));
    // }
    // maxCoin = goldMin_DP(grid, dp);
    // cout << maxCoin << endl;

    // count_of_ways(7, 3);

    // display(dp);
    // display2D(dp);
}

// friends pairing problme gfg ==================================================
int friends_pairing_problem(int n, vi &dp)
{

    if (n <= 1)
        return 1;
    if (!dp[n])
        return dp[n];
    int single = friends_pairing_problem(n - 1, dp);
    int pairUp = friends_pairing_problem(n - 2, dp) * (n - 1);
    return dp[n] = single + pairUp;
}

int friends_pairing_problem_DP(int n, vector<int> &dp)
{
    int N = n;
    for (int n = 0; n <= N; n++)
    {
        if (n <= 1)
        {
            dp[n] = 1;
            continue;
        }

        int single = dp[n - 1];           //friends_pairing_problem(n - 1, dp);
        int pairUp = dp[n - 2] * (n - 1); //friends_pairing_problem(n - 2, dp) * (n - 1);

        dp[n] = (single + pairUp);
    }
    return dp[N];
}

void set2()
{
    int n = 10;
    vector<int> dp(n + 1, 0);
    // cout << friends_pairing_problem(n, dp) << endl;
    cout << friends_pairing_problem_DP(n, dp) << endl;

    display(dp);
}

// Leetcode 64 minpath sum ===================================
int minPathSum(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (sr == grid.size() - 1 && sc == grid[0].size() - 1)
    {
        return dp[sr][sc] = grid[sr][sc];
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int minCost = 1e8;
    if (sr + 1 < grid.size())
        minCost = min(minCost, minPathSum(sr + 1, sc, grid, dp));
    if (sc + 1 < grid[0].size())
        minCost = min(minCost, minPathSum(sr, sc + 1, grid, dp));

    return dp[sr][sc] = minCost + grid[sr][sc];
}

int minPathSum_DP(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    for (sr = grid.size() - 1; sr >= 0; sr--)
    {
        for (sc = grid[0].size() - 1; sc >= 0; sc--)
        {

            if (sr == grid.size() - 1 && sc == grid[0].size() - 1)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int minCost = 1e8;
            if (sr + 1 < grid.size())
                minCost = min(minCost, dp[sr + 1][sc]);
            if (sc + 1 < grid[0].size())
                minCost = min(minCost, dp[sr][sc + 1]);

            dp[sr][sc] = minCost + grid[sr][sc];
        }
    }
    return dp[0][0];
}

int minPathSum(vector<vector<int>> &grid)
{
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
    return minPathSum(0, 0, grid, dp);
}

// Gold Mine problem gfg ====================================================
int goldMin(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    if (sc == grid[0].size() - 1)
    {
        return dp[sr][sc] = grid[sr][sc];
    }

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};
    int maxCoins = 0;
    for (int d = 0; d < 3; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];
        if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size())
        {
            maxCoins = max(maxCoins, goldMin(x, y, grid, dp));
        }
    }

    return dp[sr][sc] = maxCoins + grid[sr][sc];
}

int goldMin_DP(vector<vector<int>> &grid, vector<vector<int>> &dp)
{

    for (int sc = grid[0].size() - 1; sc >= 0; sc--)
    {
        for (int sr = grid.size() - 1; sr >= 0; sr--)
        {
            if (sc == grid[0].size() - 1)
            {
                dp[sr][sc] = grid[sr][sc];
                continue;
            }

            int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};
            int maxCoins = 0;
            for (int d = 0; d < 3; d++)
            {
                int x = sr + dir[d][0];
                int y = sc + dir[d][1];
                if (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size())
                    maxCoins = max(maxCoins, dp[x][y]);
            }

            dp[sr][sc] = maxCoins + grid[sr][sc];
        }
    }

    int maxCoin = 0;
    for (int i = 0; i < grid.size(); i++)
        maxCoin = max(maxCoin, dp[i][0]);
    return maxCoin;
}

// https://www.geeksforgeeks.org/count-number-of-ways-to-partition-a-set-into-k-subsets/

int count_of_ways(int n, int k, vector<vector<int>> &dp)
{
    if (n < k)
        return 0;
    if (n == k || k == 1)
        return dp[k][n] = 1;

    if (dp[k][n] != 0)
        return dp[k][n];

    int newGroup = count_of_ways(n - 1, k - 1, dp);
    int ExistingGroup = count_of_ways(n - 1, k, dp) * k;

    return dp[k][n] = newGroup + ExistingGroup;
}

int count_of_ways_DP(int n, int k, vector<vector<int>> &dp)
{

    int K = k, N = n;
    for (k = 1; k <= K; k++)
    {
        for (n = 0; n <= N; n++)
        {
            if (n < k)
                continue;

            if (n == k || k == 1)
            {
                dp[k][n] = 1;
                continue;
            }

            int newGroup = dp[k - 1][n - 1];
            int ExistingGroup = dp[k][n - 1] * k;

            dp[k][n] = newGroup + ExistingGroup;
        }
    }

    return dp[K][N];
}

void count_of_ways(int n, int k)
{
    if (n < k)
        return;

    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    // cout << count_of_ways(n, k, dp) << endl;
    cout << count_of_ways_DP(n, k, dp) << endl;

    display2D(dp);
}

// Substirng and Subsequence with palindrome ============================================
vector<vector<bool>> isPlaindromeSubstring(string str)
{
    int n = str.size();
    vector<vector<bool>> dp(n, vector<bool>(n, 0));
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = true;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = true;
            else
                dp[i][j] = str[i] == str[j] && dp[i + 1][j - 1];
        }
    }
    return dp;
}

//Leetcode 005.==================================================================
string longestPlaindromeSubstring(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    int maxLen = 0;
    int si = 0, ei = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = 2;
            else if (str[i] == str[j] && dp[i + 1][j - 1] != 0)
                dp[i][j] = gap + 1;

            if (dp[i][j] > maxLen)
            {
                maxLen = dp[i][j];
                si = i;
                ei = j;
            }
        }
    }

    return str.substr(si, (ei - si + 1));
}

//Leetcode 647.=================================================================================
int countAllPlaindromicSubstring(string str)
{
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    int count = 0;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = 1;
            else if (gap == 1 && str[i] == str[j])
                dp[i][j] = 2;
            else if (str[i] == str[j] && dp[i + 1][j - 1] != 0)
                dp[i][j] = gap + 1;

            count += dp[i][j] != 0 ? 1 : 0;
        }
    }
}

//Leetcode 516.================================================================================================================
int longestPlaindromeSubseq_Rec(string str, int si, int ei, vector<vector<int>> &dp)
{
    if (si > ei)
        return 0;
    if (si == ei)
        return dp[si][ei] = 1;
    if (dp[si][ei] != 0)
        return dp[si][ei];

    int len = 0;
    if (str[si] == str[ei])
        len = longestPlaindromeSubseq_Rec(str, si + 1, ei - 1, dp) + 2;
    else
        len = max(longestPlaindromeSubseq_Rec(str, si + 1, ei, dp), longestPlaindromeSubseq_Rec(str, si, ei - 1, dp));

    return dp[si][ei] = len;
}

int longestPlaindromeSubseq_DP(string &str, vvi &dp, vector<vector<bool>> &isPalin)
{
    int n = str.size();
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (isPalin[i][j])
            {
                dp[i][j] = j - i + 1;
                continue;
            }

            if (str[i] == str[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][n - 1];
}

//Leetcode 115 : distinct-subsequences.=========================================================
int distinct_subsequences(string S, string T, int n, int m, vector<vector<int>> &dp)
{
    if (m == 0)
        return dp[n][m] = 1;
    if (m > n)
        return dp[n][m] = 0;

    if (dp[n][m] != -1)
        return dp[n][m];

    if (S[n - 1] == T[m - 1])
        return dp[n][m] = distinct_subsequences(S, T, n - 1, m - 1, dp) + distinct_subsequences(S, T, n - 1, m, dp);

    return dp[n][m] = distinct_subsequences(S, T, n - 1, m, dp);
}

int distinct_subsequences_02(string S, string T, int i, int j, vector<vector<int>> &dp)
{
    if (T.length() - j == 0)
        return dp[i][j] = 1;
    if (S.length() - i > T.length() - j)
        return dp[i][j] = 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (S[i] == T[j])
        return dp[i][j] = distinct_subsequences_02(S, T, i + 1, j + 1, dp) + distinct_subsequences_02(S, T, i + 1, j, dp);

    return dp[i][j] = distinct_subsequences_02(S, T, i + 1, j, dp);
}

int distinct_subsequences_DP(string S, string T, int n, int m, vector<vector<int>> &dp)
{
    int N = n, M = m;
    for (n = 0; n <= N; n++)
    {
        for (m = 0; m <= M; m++)
        {
            if (m == 0)
            {
                dp[n][m] = 1;
                continue;
            }
            if (m > n)
            {
                dp[n][m] = 0;
                continue;
            }
            if (S[n - 1] == T[m - 1])
                dp[n][m] = dp[n - 1][m - 1] + dp[n - 1][m];
            else
                dp[n][m] = dp[n - 1][m];
        }
    }

    return dp[N][M];
}

int numDistinct(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    // cout << distinct_subsequences(s, t, n, m, dp) << endl;
    cout << distinct_subsequences_DP(s, t, n, m, dp) << endl;

    display2D(dp);
}

//Geeks: https://practice.geeksforgeeks.org/problems/count-palindromic-subsequences/1
int countPS(string &s, int i, int j, vector<vector<int>> &dp)
{
    if (i > j)
        return 0;
    if (i == j)
        return dp[i][j] = 1;
    if (dp[i][j] != 0)
        return dp[i][j];

    int middleString = countPS(s, i + 1, j - 1, dp);
    int excludingLast = countPS(s, i, j - 1, dp);
    int excludingFirst = countPS(s, i + 1, j, dp);

    int ans = excludingFirst + excludingLast;
    return dp[i][j] = (s[i] == s[j]) ? ans + 1 : ans - middleString;
}

int countPS_DP(string &s, int i, int j, vector<vector<int>> &dp)
{

    int n = s.length();
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }

            int middleString = dp[i + 1][j - 1];
            int excludingLast = dp[i][j - 1];
            int excludingFirst = dp[i + 1][j];

            int ans = excludingFirst + excludingLast;
            dp[i][j] = (s[i] == s[j]) ? ans + 1 : ans - middleString;
        }
    }
    return dp[0][n - 1];
}

// LeetCode : 1143 =========================================================
int longestCommonSubsequence(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
    if (i == text1.length() || j == text2.length())
        return 0;
    if (dp[i][j] != 0)
        return dp[i][j];
    int ans = 0;
    if (text1[i] == text2[j])
        ans = longestCommonSubsequence(text1, text2, i + 1, j + 1, dp) + 1;
    else
        ans = max(longestCommonSubsequence(text1, text2, i + 1, j, dp), longestCommonSubsequence(text1, text2, i, j + 1, dp));

    dp[i][j] = ans;
}

int longestCommonSubsequence_DP(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
    for (i = text1.length(); i >= 0; i--)
    {
        for (j = text2.length(); j >= 0; j--)
        {
            if (i == text1.length() || j == text2.length())
                continue;

            int ans = 0;
            if (text1[i] == text2[j])
                ans = dp[i + 1][j + 1] + 1;
            else
                ans = max(dp[i + 1][j], dp[i][j + 1]);

            dp[i][j] = ans;
        }
    }
    return dp[0][0];
}

int longestCommonSubsequence(string text1, string text2)
{
    vector<vector<int>> dp(text1.length() + 1, vector<int>(text2.length() + 1, 0));
    int ans = 0;
    ans = longestCommonSubsequence(text1, text2, 0, 0, dp);
    // ans = longestCommonSubsequence_DP(text1, text2, 0, 0, dp);
    display2D(dp);
    return ans;
}

int max_ = 0;
int longestCommonSubstring(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
    if (i == text1.length() || j == text2.length())
        return dp[i][j] = 0;
    if (dp[i][j] != 0)
        return dp[i][j];

    int a = longestCommonSubstring(text1, text2, i + 1, j, dp);
    int b = longestCommonSubstring(text1, text2, i, j + 1, dp);

    if (text1[i] == text2[j])
    {
        int a = longestCommonSubstring(text1, text2, i + 1, j + 1, dp) + 1;
        max_ = max(max_, a);
        return dp[i][j] = a;
    }

    return 0;
}

int longestCommonSubstring_DP(string &text1, string &text2, int i, int j, vector<vector<int>> &dp)
{
    int max_ = 0;
    for (i = text1.length(); i >= 0; i--)
    {
        for (j = text2.length(); j >= 0; j--)
        {
            if (i == text1.length() || j == text2.length())
                continue;

            int ans = 0;
            if (text1[i] == text2[j])
            {
                ans = dp[i + 1][j + 1] + 1;
                max_ = max(max_, ans);
            }
            int a = dp[i + 1][j];
            int b = dp[i][j + 1];

            dp[i][j] = ans;
        }
    }
    return dp[0][0];
}

// Leetcode: 1035
// Same as longest common subsequence ==================================================
int lcs(vector<int> &a, vector<int> &b, int i, int j, vector<vector<int>> &dp)
{
    if (i == a.size() || j == b.size())
        return 0;
    if (dp[i][j] != 0)
        return dp[i][j];
    if (a[i] == b[j])
        return dp[i][j] = lcs(a, b, i + 1, j + 1, dp) + 1;
    return dp[i][j] = max(lcs(a, b, i + 1, j, dp), lcs(a, b, i, j + 1, dp));
}

int lcs_DP(vector<int> &a, vector<int> &b, int n, int m, vector<vector<int>> &dp)
{

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {

            if (a[i] == b[j])
                dp[i][j] = dp[i + 1][j + 1] + 1;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
        }
    }
    return dp[0][0];
}

int maxUncrossedLines(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    int m = B.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    // return lcs(A, B, 0, 0, dp);
    return lcs_DP(A, B, n, m, dp);
}

//leetcode 1458.
int maxDotProduct(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = n; i >= 0; i--)
    {
        for (int j = m; j >= 0; j--)
        {
            if (i == n || m == j)
            {
                dp[i][j] = -1e8;
                continue;
            }

            int val = nums1[i] * nums2[j];
            int a = dp[i + 1][j + 1] + val;
            int b = dp[i + 1][j];
            int c = dp[i][j + 1];

            dp[i][j] = max(max(a, b), max(c, val));
        }
    }

    return dp[0][0];
}

// Leetcode 72 convering str1 -> str2;
int editDistance(string &str1, string &str2, int n, int m, vector<vector<int>> &dp)
{
    if (n == 0 || m == 0)
        return dp[n][m] = (n == 0 ? m : n);
    if (dp[n][m] != 0)
        return dp[n][m];
    if (str1[n - 1] == str2[m - 1])
        return dp[n][m] = editDistance(str1, str2, n - 1, m - 1, dp);
    int insert_ = editDistance(str1, str2, n, m - 1, dp) + 1;
    int replace_ = editDistance(str1, str2, n - 1, m - 1, dp) + 1;
    int delete_ = editDistance(str1, str2, n - 1, m, dp) + 1;
    return dp[n][m] = min({insert_, replace_, delete_});
}

int minDistance(string word1, string word2)
{
    int n = word1.length();
    int m = word2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    return editDistance(word1, word2, n, m, dp);
}

void stringSubstringSet()
{
    // string str = "geeksforgeeks";
    // int n = str.length();
    // int si = 0, ei = n - 1;
    // vector<vector<int>> dp(n, vector<int>(n, 0));

    // vector<vector<bool>> isPlalindrome = isPlaindromeSubstring(str);
    // cout << longestPlaindromeSubstring("abcaacbefgpgf") << endl;

    // cout << longestPlaindromeSubseq_Rec(str, si, ei, dp, isPlalindrome) << endl;
    // cout << longestPlaindromeSubseq_DP(str, dp, isPlalindrome) << endl;

    // display2D(dp);

    // numDistinct("geeksforgeeks", "gks");
    // cout << longestCommonSubsequence("abc", "aab") << endl;
}

// Coin_Change/Target_type =========================================================
int coinChangePermutation(int tar, vi &arr, vi &dp)
{
    if (tar == 0)
        dp[tar] = 1;
    if (dp[tar] != 0)
        dp[tar];
    int count = 0;
    for (auto ele : arr)
        if (tar - ele >= 0)
            count += coinChangePermutation(tar - ele, arr, dp);
    return dp[tar] = count;
}

int coinChangePermutation_DP(int Tar, vi &arr, vi &dp)
{
    int n = arr.size();
    for (int tar = 0; tar <= Tar; tar++)
    {
        if (tar == 0)
        {
            dp[tar] = 0;
            continue;
        }
        int count;
        for (auto ele : arr)
            if (tar - ele >= 0)
                count += dp[tar - ele];
        dp[tar] = count;
    }
    return dp[Tar];
}

// jugad method for finding the it using 1-d array becuase it doesn't overlap in memoization.
int coinChangeCombination_DP(int Tar, vi &arr, vi &dp)
{
    int n = arr.size();
    dp[0] = 1;
    for (auto ele : arr)
        for (int tar = ele; tar <= Tar; tar++)
            dp[tar] += dp[tar - ele];
    return dp[Tar];
}

//https://www.geeksforgeeks.org/find-number-of-solutions-of-a-linear-equation-of-n-variables/

int LinearEquation_DP(vector<int> &coeff, int rhs)
{
    vector<int> dp(rhs + 1, 0);
    dp[0] = 1;
    for (int ele : coeff)
        for (int tar = ele; tar <= rhs; tar++)
            dp[tar] += dp[tar - ele];
}

//leetcode 322
int coinChange_(vector<int> &coins, int tar, vector<int> &dp)
{
    if (tar == 0)
        return 0;

    if (dp[tar] != 0)
        return dp[tar];
    int minHeight = 1e8;
    for (int ele : coins)
    {
        if (tar - ele >= 0)
        {
            int rMinHeight = coinChange_(coins, tar, dp);
            if (rMinHeight != 1e8 && rMinHeight + 1 < minHeight)
                minHeight = rMinHeight + 1;
        }
    }
    return dp[tar] = minHeight;
}

int coinChange(vector<int> &coins, int tar)
{
    vector<int> dp(tar + 1, 0);
    return coinChange_(coins, tar, dp);
}

void coinChange()
{
    // vector<int> arr{2, 3, 5, 7};
    // int tar = 10;
    // vector<int> dp(tar + 1, 0);
    // cout << coinChangePermutation(arr, tar, dp) << endl;

    // display(dp);
}

int targetSum(vector<int> &coins, int idx, int tar, vector<vector<int>> &dp)
{
    if (idx == coins.size() || tar == 0)
    {
        if (tar == 0)
            return dp[idx][tar] = 1;
        return 0;
    }

    if (dp[idx][tar] != 0)
        return dp[idx][tar];

    int count = 0;
    if (tar - coins[idx] >= 0)
        count += targetSum(coins, idx + 1, tar - coins[idx], dp);
    count += targetSum(coins, idx + 1, tar, dp);
    return dp[idx][tar] = count;
}

int targetSum_02(vector<int> &coins, int idx, int tar, vector<vector<int>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        if (tar == 0)
            return dp[idx][tar] = 1;
        return dp[idx][tar] = 0;
    }

    if (dp[idx][tar] != 0)
        return dp[idx][tar];

    int count = 0;
    if (tar - coins[idx - 1] >= 0)
        count += targetSum_02(coins, idx - 1, tar - coins[idx - 1], dp);

    count += targetSum_02(coins, idx - 1, tar, dp);
    return dp[idx][tar] = count;
}

int printPathOfTargetSum(vector<int> &coins, int idx, int tar, string ans, vector<vector<bool>> &dp)
{
    if (tar == 0 || idx == 0)
    {
        if (tar == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    if (tar - coins[idx - 1] >= 0 && dp[idx - 1][tar - coins[idx - 1]])
        count += printPathOfTargetSum(coins, idx - 1, tar - coins[idx - 1], ans + to_string(coins[idx - 1]) + " ", dp);

    if (dp[idx - 1][tar])
        count += printPathOfTargetSum(coins, idx - 1, tar, ans, dp);

    return count;
}

void targetSum_02DP(vector<int> &coins, int tar)
{
    int n = coins.size();
    int Tar = tar;
    vector<vector<bool>> dp(n + 1, vector<bool>(tar + 1));

    for (int idx = 0; idx < n + 1; idx++)
    {
        for (tar = 0; tar <= Tar; tar++)
        {
            if (tar == 0 || idx == 0)
            {
                if (tar == 0)
                    dp[idx][tar] = 1;
                continue;
            }

            if (tar - coins[idx - 1] >= 0)
                dp[idx][tar] = dp[idx - 1][tar - coins[idx - 1]];
            dp[idx][tar] = dp[idx][tar] || dp[idx - 1][tar];
        }
    }

    for (vector<bool> &ar : dp)
    {
        for (bool ele : ar)
        {
            cout << ele << " ";
        }
        cout << endl;
    }

    cout << printPathOfTargetSum(coins, coins.size(), Tar, "", dp) << endl; // printing path of dp using back engineering;
}

void targetType()
{
    vi arr = {2, 3, 5, 7};
    int tar = 10;
    // vvi dp(arr.size() + 1, vi(tar + 1, 0));
    // cout << targetSum_02(arr, arr.size(), tar, dp) << endl;
    targetSum_02DP(arr, tar);

    // display2D(dp);
}

int knapsack01(vector<int> &w, vector<int> &p, int weight, int n, vector<vector<int>> &dp)
{
    if (weight == 0 || n == 0)
    {
        return 0;
    }

    if (dp[n][weight] != 0)
        return dp[n][weight];

    int maxProfit = -1e8;
    if (weight - w[n - 1] >= 0)
        maxProfit = max(maxProfit, knapsack01(w, p, weight - w[n - 1], n - 1, dp) + p[n - 1]); // dp[n-1][weight - w[n - 1]]+p[n-1]
    maxProfit = max(maxProfit, knapsack01(w, p, weight, n - 1, dp));                           // dp[n-1][weight]

    return dp[n][weight] = maxProfit;
}

int unbpounded(vector<int> &w, vector<int> &p, int weight)
{
    vector<int> dp(w.size() + 1, -1e8);
    dp[0] = 0;
    for (int i = 0; i < w.size(); i++)
        for (int tar = w[i]; tar <= weight; tar++)
            dp[tar] = max(dp[tar], dp[tar - w[i]] + p[i]);

    return dp[w.size()];
}

void knapsack()
{
    vector<int> p = {100, 280, 120};
    vector<int> w = {10, 40, 20};
    int weight = 60;
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(weight + 1, 0));

    cout << knapsack01(w, p, weight, n, dp) << endl;
}

//Leetcode 416
bool canPartition_(vector<int> &nums, int n, int sum, vector<vector<int>> &dp)
{
    if (sum == 0 || n == 0)
    {
        if (sum == 0)
            return dp[n][sum] = 1;
        return dp[n][sum] = 0;
    }

    if (dp[n][sum] != -1)
        return dp[n][sum];

    bool res = false;
    if (sum - nums[n - 1] >= 0)
        res = res || canPartition_(nums, n - 1, sum - nums[n - 1], dp) == 1;
    res = res || canPartition_(nums, n - 1, sum, dp) == 1;

    return dp[n][sum] = res ? 1 : 0;
}

bool canPartition(vector<int> &nums)
{
    int sum = 0;
    for (int ele : nums)
        sum += ele;
    if (sum % 2 != 0)
        return false;

    sum /= 2;
    vector<vector<int>> dp(nums.size() + 1, vector<int>(sum + 1, -1));

    return canPartition_(nums, nums.size(), sum, dp);
}

//Leetcode 494
int min_;
int sum(vector<int> &nums, int tar, int idx, int s, vector<vector<int>> &dp)
{
    if (idx == nums.size())
    {
        if (tar == s)
            return dp[idx][tar + max_] = 1;
        return dp[idx][tar + max_] = 0;
    }
    if (dp[idx][tar + max_] != -1)
        return dp[idx][tar + max_];
    int count = 0;
    count += sum(nums, tar - nums[idx], idx + 1, s, dp);
    count += sum(nums, tar + nums[idx], idx + 1, s, dp);
    return dp[idx][tar + max_] = count;
}

int findTargetSumWays(vector<int> &nums, int S)
{
    int n = nums.size();
    min_ = 0;
    max_ = 0;
    for (auto ele : nums)
    {
        max_ += ele;
        min_ -= ele;
    }
    vector<vector<int>> dp(n + 1, vector<int>(max_ - min_ + 1, -1));
    // int ans = targetSum(nums, 0, 0, S, dp);
    int ans = sum(nums, 0, 0, S, dp);
    // for (auto ar : dp)
    // {
    //     for (auto ele : ar)
    //         cout << ele << " ";
    //     cout << endl;
    // }
    return ans;
}

//LIS ======================================================================
int LIS_leftToRight(vector<int> &arr, vector<int> &dp)
{
    int N = arr.size();
    int oMax = 0;
    for (int i = 0; i < N; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + 1);
        oMax = max(oMax, dp[i]);
    }
    return oMax;
}

//LDS
int LIS_rightToLeft(vector<int> &arr, vector<int> &dp)
{
    int N = arr.size();
    int oMax = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        dp[i] = 1;
        for (int j = i + 1; j < N; j++)
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + 1);
        oMax = max(oMax, dp[i]);
    }
    return oMax;
}

//Longest bitonic subsequence
//https://www.geeksforgeeks.org/longest-bitonic-subsequence-dp-15/
int LBS(vector<int> &arr)
{
    int n = arr.size();
    vector<int> LIS(n, 0);
    vector<int> LDS(n, 0);

    LIS_leftToRight(arr, LIS);
    LIS_rightToLeft(arr, LDS);

    int maxLen = 0;
    for (int i = 0; i < n; i++)
    {
        int len = LIS[i] + LDS[i] - 1;
        maxLen = max(maxLen, len);
    }
    return maxLen;
}

// this can also be maximum sum increasing subsequence gfg
// https://practice.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence/0
vi Lis(vi &arr, int n)
{
    vi dp(n, 0);
    for (int i = 0; i < n; i++)
    {
        dp[i] = arr[i];
        for (int j = i - 1; j >= 0; j--)
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + arr[i]);
    }
    return dp;
}

//Lds maximum sum subseqeuence
vi Lbs(vi &arr, int n)
{
    vi dp(n, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = arr[i];
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + arr[i]);
    }
    return dp;
}

int LBS_Sum()
{
    int n;
    cin >> n;
    vi arr(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vi Lis_dp = Lis(arr, n);
    vi Lbs_dp = Lbs(arr, n);

    // for (int i = 0; i < n; i++)
    // {
    //     cout << Lis_dp[i] << " " << Lbs_dp[i] << endl;
    // }

    int max_ = 0;
    for (int i = 0; i < n; i++)
    {
        max_ = max(max_, Lis_dp[i] + Lbs_dp[i] - arr[i]);
    }

    return max_;
}

int findNumberOfLIS(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return n;

    vector<int> dp(n, 0);
    vector<int> count(n, 0);

    int maxLen = 0;
    int maxCount = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        count[i] = 1;

        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[i] > arr[j])
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                }
                else if (dp[j] + 1 == dp[i])
                    count[i] += count[j];
            }
        }

        if (dp[i] > maxLen)
        {
            maxLen = dp[i];
            maxCount = count[i];
        }
        else if (dp[i] == maxLen)
            maxCount += count[i];
    }

    return maxCount;
}

// minimum no of deletion to make array in sorted order in increasing order.
int minDeletion(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 0);

    int oMax = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] <= arr[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }

        oMax = max(oMax, dp[i]);
    }

    return n - oMax;
}

//Leetcode 354
int maxEnvelopes(vector<vector<int>> &arr)
{
    // for Java:
    // Arrays.sort(arr,(int[] a, int[] b)-> {
    //     if (a[0] == b[0])
    //         return b[1] - a[1]; // other - this
    //     return a[0] - b[0];     // this - other. default
    // });

    sort(arr.begin(), arr.end(), [](vector<int> &a, vector<int> &b) {
        if (a[0] == b[0])
            return b[1] < a[1]; // other - this
        return a[0] < b[0];     // this - other., for cpp replace '-' with '<' default
    });

    int n = arr.size();
    vector<int> dp(n, 0);

    int oMax = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j][1] < arr[i][1])
                dp[i] = max(dp[i], dp[j] + 1);
        }

        oMax = max(oMax, dp[i]);
    }

    return oMax;
}

// Leetcode 1235 :

int Next(int cur, vector<vector<int>> &arr)
{
    for (int next = cur + 1; next < arr.size(); next++)
        if (arr[cur][1] <= arr[next][0])
            return next;
    return -1;
}

int dfs(int cur, vector<vector<int>> &arr, unordered_map<int, int> &dp)
{
    if (cur == arr.size())
        return 0;
    if (dp.find(cur) != dp.end())
        return dp[cur];

    int next = Next(cur, arr);
    int include = arr[cur][2] + (next != -1 ? dfs(next, arr, dp) : 0);
    int exclude = dfs(cur + 1, arr, dp);

    dp[cur] = max(include, exclude);
    return max(include, exclude);
}

int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int n = profit.size();
    vector<vector<int>> arr(n, vector<int>(3, 0));
    for (int i = 0; i < n; i++)
        arr[i] = {startTime[i], endTime[i], profit[i]};
    sort(arr.begin(), arr.end());

    unordered_map<int, int> dp;
    return dfs(0, arr, dp);
    // Lis solution giving TLE;
    //         sort(arr.begin(), arr.end(), [](vector<int> &a, vector<int> &b) {
    //             return a[1] < b[1];
    //         });
    //         vector<int> dp(n, 0);
    //         int maxRes = 0;
    //         for (int i = 0; i < n; i++)
    //         {
    //             dp[i] = arr[i][2];
    //             for (int j = i - 1; j >= 0; j--)
    //             {
    //                 if (arr[i][0] >= arr[j][1])
    //                     dp[i] = max(dp[i], dp[j] + arr[i][2]);
    //             }
    //             maxRes = max(maxRes, dp[i]);
    //         }

    //         return maxRes;
}

// Cut Type ===================================================================
// Matrix chain multiplication.
int MCM(vi &arr, int si, int ei, vvi &dp)
{
    if (si + 1 == ei)
        return dp[si][ei] = 0;

    if (dp[si][ei] != -1)
        return dp[si][ei];

    int ans = 1e9;
    for (int cut = si + 1; cut < ei; cut++)
    {

        int leftAns = MCM(arr, si, cut, dp);
        int rightAns = MCM(arr, cut, ei, dp);

        int myAns = leftAns + arr[si] * arr[cut] * arr[ei] + rightAns;
        if (ans > myAns)
            ans = myAns;
    }

    dp[si][ei] = ans;
}

int MCM_DP_Ans(vector<int> &arr)
{

    int n = arr.size();
    vector<vector<string>> sdp(n, vector<string>(n, ""));
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int gap = 1; gap < arr.size(); gap++)
    {
        for (int si = 0, ei = gap; ei < arr.size(); si++, ei++)
        {
            if (si + 1 == ei)
            {
                dp[si][ei] = 0;
                sdp[si][ei] = (char)(si + 'A');
                continue;
            }

            int ans = 1e8;
            string sans = "";
            for (int cut = si + 1; cut < ei; cut++)
            {
                int leftCost = dp[si][cut];  //MCM_rec(arr, si, cut, dp);
                int rightCost = dp[cut][ei]; //MCM_rec(arr, cut, ei, dp);

                int myCost = leftCost + arr[si] * arr[cut] * arr[ei] + rightCost;
                if (myCost < ans)
                {
                    ans = myCost;
                    sans = "(" + sdp[si][cut] + sdp[cut][ei] + ")";
                }
            }

            dp[si][ei] = ans;
            sdp[si][ei] = sans;
        }
    }

    cout << sdp[0][arr.size() - 1] << endl;
    cout << dp[0][arr.size() - 1] << endl;
}

int costOfSearching(vector<int> &freq, int si, int ei)
{
    int sum = 0;
    for (int i = si; i <= ei; i++)
        sum += freq[i];
    return sum;
}

int OBST_rec(vector<int> &freq, int si, int ei, vector<vector<int>> &dp)
{
    if (dp[si][ei] != 0)
        return dp[si][ei];

    int ans = 1e8;
    for (int cut = si; cut <= ei; cut++)
    {
        int leftTreeCost = (cut == si) ? 0 : OBST_rec(freq, si, cut - 1, dp);
        int rightTreeCost = (cut == ei) ? 0 : OBST_rec(freq, cut + 1, ei, dp);

        int myCost = leftTreeCost + costOfSearching(freq, si, ei) + rightTreeCost;
        if (myCost < ans)
            ans = myCost;
    }

    return dp[si][ei] = ans;
}

int OBST_DP(vector<int> &freq, int si, int ei, vector<vector<int>> &dp)
{
    vector<int> prefixSum(freq.size() + 1, 0);
    for (int i = 1; i < prefixSum.size(); i++)
        prefixSum[i] = prefixSum[i - 1] + freq[i - 1];

    for (int gap = 0; gap < freq.size(); gap++)
    {
        for (si = 0, ei = gap; ei < freq.size(); si++, ei++)
        {
            int ans = 1e8;
            for (int cut = si; cut <= ei; cut++)
            {
                int leftTreeCost = (cut == si) ? 0 : dp[si][cut - 1];  //OBST_rec(freq, si, cut - 1, dp);
                int rightTreeCost = (cut == ei) ? 0 : dp[si][cut + 1]; //OBST_rec(freq, cut + 1, ei, dp);

                int myCost = leftTreeCost + prefixSum[ei + 1] - prefixSum[si] + rightTreeCost;
                if (myCost < ans)
                    ans = myCost;
            }
            dp[si][ei] = ans;
        }
    }
    return dp[0][freq.size() - 1];
}

int burstBallon(vector<int> &arr, int si, int ei, vector<vector<int>> &dp)
{

    if (dp[si][ei] != 0)
        return dp[si][ei];

    int lVal = (si == 0) ? 1 : arr[si - 1];
    int rVal = (ei == arr.size() - 1) ? 1 : arr[ei + 1];

    int ans = 0;
    for (int cut = si; cut <= ei; cut++)
    {
        int leftTreeCost = (cut == si) ? 0 : burstBallon(arr, si, cut - 1, dp);
        int rightTreeCost = (cut == ei) ? 0 : burstBallon(arr, cut + 1, ei, dp);

        int myCost = leftTreeCost + lVal * arr[cut] * rVal + rightTreeCost;
        if (myCost > ans)
            ans = myCost;
    }

    return dp[si][ei] = ans;
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    cout << burstBallon(nums, 0, n - 1, dp) << endl;
}

void optimalBinarySearchTree()
{
    vector<int> keys{10, 12, 20};
    vector<int> freq{34, 8, 50};

    int n = freq.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    cout << OBST_rec(freq, 0, n - 1, dp) << endl;
    // cout << OBST_DP(freq, 0, n - 1, dp) << endl;

    display2D(dp);
}

void MCM()
{
    vector<int> arr{3, 7, 2, 6, 5, 4};
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    // cout << MCM_rec(arr, 0, n - 1, dp) << endl;
    // cout << MCM_DP(arr, 0, n - 1, dp) << endl;
    // MCM_DP_Ans(arr);

    display2D(dp);
}

//==============================================================================================================

//Leetcode :91. Decode Ways

int numDecodings_(string &s, int vidx, vector<int> &dp)
{
    if (vidx == s.length())
    {
        return dp[vidx] = 1;
    }
    if (dp[vidx] != -1)
        return dp[vidx];

    char ch = s[vidx];
    if (ch == '0')
        return dp[vidx] = 0;

    int count = 0;
    count += numDecodings_(s, vidx + 1, dp);
    if (vidx < s.size() - 1)
    {
        int num = (ch - '0') * 10 + (s[vidx + 1] - '0');
        if (num <= 26)
            count += numDecodings_(s, vidx + 2, dp);
    }

    return dp[vidx] = count;
}

int numDecodings02(string &s)
{

    int a = 0;
    int b = 1;

    int ans = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        char ch = s[i];
        ans = 0;
        if (ch != '0')
        {
            ans = b;
            if (i < s.length() - 1)
            {
                int num = (ch - '0') * 10 + (s[i + 1] - '0');
                if (num <= 26)
                    ans += a;
            }
        }

        a = b;
        b = ans;
    }
}

long mod = 1e9 + 7;
long numDecodingsII_recu(string &str, int idx, vector<long> &dp)
{
    if (idx == str.length())
        return 1;
    if (dp[idx] != 0)
        return dp[idx];

    int count = 0;
    if (str[idx] == '*')
    {
        count = (count % mod + 9 * numDecodingsII_recu(str, idx + 1, dp) % mod) % mod;
        if (idx < str.length() - 1 && str[idx + 1] >= '0' && str[idx + 1] <= '6')
            count = (count % mod + 2 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
        else if (idx < str.length() - 1 && str[idx + 1] >= '7')
            count = (count % mod + numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
        else if (idx < str.length() - 1 && str[idx + 1] == '*')
            count = (count % mod + 15 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
    }
    else if (str[idx] > '0')
    {

        count = (count % mod + numDecodingsII_recu(str, idx + 1, dp) % mod) % mod;
        if (idx < str.length() - 1)
        {
            if (str[idx + 1] != '*')
            {
                int num = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
                if (num <= 26)
                    count = (count % mod + numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
            }
            else if (str[idx] == '1')
                count = (count % mod + 9 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
            else if (str[idx] == '2')
                count = (count % mod + 6 * numDecodingsII_recu(str, idx + 2, dp) % mod) % mod;
        }
    }
    return dp[idx] = count;
}

long numDecodingsII_DP(string &str, int idx, vector<long> &dp)
{
    for (idx = str.length(); idx >= 0; idx--)
    {
        if (idx == str.length())
        {
            dp[idx] = 1;
            continue;
        }

        int count = 0;
        if (str[idx] == '*')
        {
            count = (count % mod + 9 * dp[idx + 1] % mod) % mod;
            if (idx < str.length() - 1 && str[idx + 1] >= '0' && str[idx + 1] <= '6')
                count = (count % mod + 2 * dp[idx + 2] % mod) % mod;
            else if (idx < str.length() - 1 && str[idx + 1] >= '7')
                count = (count % mod + dp[idx + 2] % mod) % mod;
            else if (idx < str.length() - 1 && str[idx + 1] == '*')
                count = (count % mod + 15 * dp[idx + 2] % mod) % mod;
        }
        else if (str[idx] > '0')
        {

            count = (count % mod + dp[idx + 1] % mod) % mod;
            if (idx < str.length() - 1)
            {
                if (str[idx + 1] != '*')
                {
                    int num = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
                    if (num <= 26)
                        count = (count % mod + dp[idx + 2] % mod) % mod;
                }
                else if (str[idx] == '1')
                    count = (count % mod + 9 * dp[idx + 2] % mod) % mod;
                else if (str[idx] == '2')
                    count = (count % mod + 6 * dp[idx + 2]) % mod;
            }
        }
        dp[idx] = count;
    }
    return dp[0];
}

long numDecodingsII_Fast(string &str, int idx, vector<long> &dp)
{
    long a = 0;
    long b = 1;
    long count = 0;
    for (idx = str.length() - 1; idx >= 0; idx--)
    {
        count = 0;
        if (str[idx] == '*')
        {
            count = (count % mod + 9 * b % mod) % mod;
            if (idx < str.length() - 1 && str[idx + 1] >= '0' && str[idx + 1] <= '6')
                count = (count % mod + 2 * a % mod) % mod;
            else if (idx < str.length() - 1 && str[idx + 1] >= '7')
                count = (count % mod + a % mod) % mod;
            else if (idx < str.length() - 1 && str[idx + 1] == '*')
                count = (count % mod + 15 * a % mod) % mod;
        }
        else if (str[idx] > '0')
        {

            count = (count % mod + b % mod) % mod;
            if (idx < str.length() - 1)
            {
                if (str[idx + 1] != '*')
                {
                    int num = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
                    if (num <= 26)
                        count = (count % mod + a % mod) % mod;
                }
                else if (str[idx] == '1')
                    count = (count % mod + 9 * a % mod) % mod;
                else if (str[idx] == '2')
                    count = (count % mod + 6 * a) % mod;
            }
        }

        a = b;
        b = count;
    }
    return count;
}

// DP toDo :
// 1. 132
// 2. 044
// 3. https://www.geeksforgeeks.org/boolean-parenthesization-problem-dp-37/
// 4. 096
// 5. 095

// int numDecodings(string str)
// {
//     vector<long> dp(str.length() + 1, 0);
//     // return (int)numDecodingsII_recu(str, 0, dp);
//     // return (int)numDecodingsII_DP(str, 0, dp);
//     return (int)numDecodingsII_Fast(str, 0, dp);
// }

int numDecodings(string s)
{
    vector<int> dp(s.length() + 1, -1);
    int ans = numDecodings_(s, 0, dp);

    display(dp);
    return ans;
}

void questionSet()
{
    numDecodings("1423101112");
}

// gfg count aibjck subsequence.
int AiBjCk(string str)
{
    int acount = 0;
    int bcount = 0;
    int ccount = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'a')
            acount = acount + (1 + acount);
        else if (str[i] == 'b')
            bcount = bcount + (acount + bcount);
        else
            ccount = ccount + (bcount + ccount);
    }

    return ccount;
}

// https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/tutorial/

// (a+b)%c = (a%c + b%c)%c
// (a-b)%c = (a%c - b%c + c)%c
// (a*b)%c = (a%c * b%c )%c
int distinctSubseqII(string str)
{
    int mod = 1e9 + 7;
    str = '$' + str;
    int n = str.length();
    vector<long> dp(n, 0);
    vector<int> lastOccu(26, -1);

    for (int i = 0; i < n; i++)
    {
        if (i == 0) // empty String.
        {
            dp[i] = 1;
            continue;
        }

        char ch = str[i];
        dp[i] = (dp[i - 1] % mod * 2) % mod;
        if (lastOccu[ch - 'a'] != -1)
            dp[i] = dp[i] % mod - dp[lastOccu[ch - 'a'] - 1] % mod + mod;

        lastOccu[ch - 'a'] = i;
    }
    return dp[n - 1] % mod - 1;
}

void solve()
{
    // set1();
    // pathSet();
    //set2();
    // stringSubstringSet();
    // cutType();
    targetType();
    // MCM();
    // optimalBinarySearchTree();
}

int main()
{
    solve();
    return 0;
}