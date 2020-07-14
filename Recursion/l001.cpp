#include <iostream>
#include <vector>
#include <string>
#define vi vector<int>
#define vii vector<vector<int>>

using namespace std;

vii dir = {{0, 1}, {1, 1}, {1, 0}};
vector<string> ch = {"H", "D", "V"};

int MazePath_HVD_01(vii &board, int sr, int sc,string ans)
{
   if (sr == board.size() - 1 && sc == board[0].size() - 1)
   {
      cout << ans << endl;
      return 1;
   }
   int count = 0;
   for (int d = 0; d < dir.size(); d++)
   {
      int nr = sr + dir[d][0];
      int nc = sc + dir[d][1];
      if (nr < board.size() && nc < board[0].size())
         count += MazePath_HVD_01(board, nr, nc, ans + ch[d]);
   }
   return count;
}

vector<string> MazePath_HVD_02(int sr, int sc, int er, int ec)
{
   if (sr == er && sc == ec)
   {
      return {""};
   }
   int count = 0;
   vector<string> myans;
   for (int d = 0; d < dir.size(); d++)
   {
      int nr = sr + dir[d][0];
      int nc = sc + dir[d][1];
      if (nr <= er && nc <= ec)
      {
         vector<string> smans = MazePath_HVD_02(nr, nc, er, ec);
         for (string ele : smans)
            myans.push_back(ch[d] + ele);
      }
   }
   return myans;
}

vector<vector<int>> dir = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
vector<string> dirN = {"R", "E", "U", "N", "L", "W", "D", "S"};

// vector<vector<int>> dir = {{0, 1}, {1, 0}, {1, 1}};
// vector<string> dirN = {"H", "V", "D"};

bool isValid(int r, int c, vector<vector<int>> &board)
{
   if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] == 0 || board[r][c] == 2)
      return false;

   return true;
}

int floodFill(int sr, int sc, int er, int ec, vector<vector<int>> &board, int rad, string ans)
{
   if (sr == er && sc == ec)
   {
      cout << ans << endl;
      return 1;
   }

   int count = 0;
   board[sr][sc] = 2;

   for (int d = 0; d < dir.size(); d++)
   {
      for (int mag = 1; mag <= rad; mag++)
      {
         int r = sr + mag * dir[d][0];
         int c = sc + mag * dir[d][1];
         if (isValid(r, c, board))
            count += floodFill(r, c, er, ec, board, rad, ans + dirN[d] + to_string(mag));
      }
   }

   board[sr][sc] = 1;
   return count;
}

//leetcode 200.
// int numIslands(vector<vector<char>> &arr)
// {
//    int count = 0;
//    for (int r = 0; r < arr.size(); r++)
//    {
//       for (int c = 0; c < arr[0].size(); c++)
//       {
//          if (arr[r][c] == '1')
//          {
//             count++;
//             floodFill(r, c, arr, 1);
//          }
//       }
//    }

//    return count;
// }

vector<vector<int>> dir_ = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

bool isValid_(int r, int c, vector<vector<char>> &board)
{
   if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] == '0' || board[r][c] == '2')
      return false;

   return true;
}

int dfs(int sr, int sc, vector<vector<char>> &board, int rad)
{
   int count = 0;
   board[sr][sc] = '2';

   for (int d = 0; d < dir.size(); d++)
   {
      for (int mag = 1; mag <= rad; mag++)
      {
         int r = sr + mag * dir_[d][0];
         int c = sc + mag * dir_[d][1];
         if (isValid_(r, c, board))
            count += dfs(r, c, board, rad);
      }
   }

   // board[sr][sc] = 1;
   return count;
}
void MazePathSet()
{
   vii board(3, vi(3));
   // cout << MazePath_HVD_01(board, 0, 0, "") << endl;
   // vector<string> ans = MazePath_HVD_02(0, 0, 2, 2);
   // for(string ele : ans)
   //    cout << ele << endl;
}

int main(int argc, char const *argv[])
{
   MazePathSet();
   return 0;
}
