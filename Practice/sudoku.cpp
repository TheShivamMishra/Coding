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

bool isSafeToPlaceNumber(vector<vector<int>> &board, int r, int c, int num)
{
    // for row
    for (int i = 0; i < board[0].size(); i++)
        if (board[r][i] == num)
            return false;

    // for col
    for (int i = 0; i < board.size(); i++)
        if (board[i][c] == num)
            return false;

    //for each sub box 3x3 Matrix
    int x = (r / 3) * 3;
    int y = (c / 3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (board[x + i][y + j] == num)
                return false;
    }

    return true;
}

bool sudoku_02(vector<vector<int>> &board, int idx, vector<int> &list)
{
    if (idx == list.size())
        return 1;

    int r = list.at(idx) / 9;
    int c = list.at(idx) % 9;
    int count = 0;
    bool res = false;

    for (int num = 1; num < 10; num++)
    {
        if (isSafeToPlaceNumber(board, r, c, num))
        {
            board[r][c] = num;
            res = sudoku_02(board, idx + 1, list);
            if (res)
                return true;
            board[r][c] = 0;
        }
    }

    return res;
}

void solve()
{
    vvi mat(9, vi(9, 0));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            cin >> mat[i][j];
    // cout << "hi" << endl;
    vi list;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (mat[i][j] == 0)
                list.push_back(i * 9 + j);
            // else
            // {
            //     int mask = 1 << mat[i][j];
            //     row[i] ^= mask;
            //     col[j] ^= mask;
            //     submat[i / 3][j / 3] ^= mask;
            // }
        }

    if (sudoku_02(mat, 0, list))
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                cout << mat[i][j] << " ";
        cout << endl;
    }
    else
        cout << "-1" << endl;
}

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}