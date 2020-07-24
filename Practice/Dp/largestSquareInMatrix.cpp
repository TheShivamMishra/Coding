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

int omax;
int largetSquareInMatrix(int sr, int sc, vvi &board, vvi &dp)
{
    if (sr == board.size() || sc == board[0].size())
        return 0;
    if (dp[sr][sc] != -1)
        return dp[sr][sc];

    int myans = 0;
    int right = largetSquareInMatrix(sr, sc + 1, board, dp);
    int diag = largetSquareInMatrix(sr + 1, sc + 1, board, dp);
    int down = largetSquareInMatrix(sr + 1, sc, board, dp);
    if (board[sr][sc] == 1)
        myans = min({right, down, diag}) + 1;
    omax = max(omax, myans);
    return dp[sr][sc] = myans;
}

int largetSquareInMatrix_DP(vvi &board)
{

    int omax = 0, n = board.size(), m = board[0].size();
    vvi dp(n, vi(m, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {

            if (board[i][j] == 1)
                dp[i][j] = min({dp[i + 1][j], dp[i][j + 1], dp[i + 1][j + 1]}) + 1;
            omax = max(omax, dp[i][j]);
        }
    }
    return omax;
}

int solve()
{
    omax = 0;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];
    // vvi dp(n, vi(m, -1));
    // largetSquareInMatrix(0, 0, board, dp);
    // return omax;
    return largetSquareInMatrix_DP(board);
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