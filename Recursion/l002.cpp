#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

void display2D(vector<vector<int>> &board)
{
    for (auto ele : board)
    {
        for (auto item : ele)
            cout << item << " ";
        cout << endl;
    }
}

// Nqueen Optimized using 4 Arrays

vector<bool> rowA(4, false);
vector<bool> colA(4, false);
vector<bool> diagA(4, false);
vector<bool> adiagA(4, false);

int Nqueen2D_01(int n, int m, int idx, int tnq, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / m;
        int y = i % m;
        if (!rowA[x] && !colA[y] && !diagA[x - y + (m - 1)] && !adiagA[x + y])
        {
            rowA[x] = true;
            colA[y] = true;
            diagA[x - y + (m - 1)] = true;
            adiagA[x + y] = true;

            count += Nqueen2D_01(n, m, i + 1, tnq - 1, ans + "(" + to_string(x) + "," + to_string(y) + ")");

            rowA[x] = false;
            colA[y] = false;
            diagA[x - y + (m - 1)] = false;
            adiagA[x + y] = false;
        }
    }

    return count;
}

// Nqueens using bits ====================================

int rowA_ = 0;
int colA_ = 0;
int diagA_ = 0;
int adiagA_ = 0;

int Nqueen2D_02(int n, int m, int idx, int tnq, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / m;
        int y = i % m;
        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diagA_ & (1 << (x - y + (m - 1)))) && !(adiagA_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diagA_ ^= (1 << (x - y + (m - 1)));
            adiagA_ ^= (1 << (x + y));

            count += Nqueen2D_02(n, m, i + 1, tnq - 1, ans + "(" + to_string(x) + "," + to_string(y) + ")");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diagA_ ^= (1 << (x - y + (m - 1)));
            adiagA_ ^= (1 << (x + y));
        }
    }

    return count;
}

// Nqueen more optimized by placing one queen per row
//i.e one queen can sit at any place in that row
// next queen will have next row;
int Nqueen2D_03(int n, int m, int r, int tnq, string ans)
{
    if (r == n || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    for (int i = r; i < m; i++)
    {
        int x = r;
        int y = 0;
        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diagA_ & (1 << (x - y + (m - 1)))) && !(adiagA_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diagA_ ^= (1 << (x - y + (m - 1)));
            adiagA_ ^= (1 << (x + y));

            count += Nqueen2D_03(n, m, r + 1, tnq - 1, ans + "(" + to_string(x) + "," + to_string(y) + ")");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diagA_ ^= (1 << (x - y + (m - 1)));
            adiagA_ ^= (1 << (x + y));
        }
    }

    return count;
}

void NqueenSet()
{
    int n = 4;
    int m = 4;
    rowA.resize(n, false);
    colA.resize(m, false);
    diagA.resize(n + m - 1, false);
    adiagA.resize(n + m - 1, false);
    // cout << Nqueen2D_01(n, m, 0, n, "") << endl;
    // cout << Nqueen2D_02(n, m, 0, n, "") << endl;
    cout << Nqueen2D_03(n, m, 0, n, "") << endl;
}

// suduko set===================================

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

int suduko_01(vector<vector<int>> &board, int idx)
{
    if (idx == 81)
    {
        display2D(board);
        return 1;
    }

    int r = idx / 9;
    int c = idx % 9;
    int count = 0;

    if (board[r][c] == 0)
    {
        for (int num = 1; num < 10; num++)
        {
            if (isSafeToPlaceNumber(board, r, c, num))
            {
                board[r][c] = num;
                count += suduko_01(board, idx + 1);
                board[r][c] = 0;
            }
        }
    }
    else
    {
        count += suduko_01(board, idx + 1);
    }

    return count;
}

// suduko 2 in this we use a list in which all the zeros of the board are present
// and just call on them hence we save the calls;
int suduko_02(vector<vector<int>> &board, int idx, vector<int> &list)
{
    if (idx == list.size())
    {
        cout << "===========================" << endl;
        display2D(board);
        return 1;
    }

    int r = list.at(idx) / 9;
    int c = list.at(idx) % 9;
    int count = 0;

    for (int num = 1; num < 10; num++)
    {
        if (isSafeToPlaceNumber(board, r, c, num))
        {
            board[r][c] = num;
            count += suduko_02(board, idx + 1, list);
            board[r][c] = 0;
        }
    }

    return count;
}

//suduko 3 More optimization of isSafeToPlaceNumber by using bits.
vector<int> row(10, 0);
vector<int> col(10, 0);
vector<vector<int>> mat(4, vector<int>(4, 0));

int suduko_03(vector<vector<int>> &board, int idx, vector<int> &list)
{
    if (idx == list.size())
    {
        cout << "===========================" << endl;
        display2D(board);
        return 1;
    }

    int r = list.at(idx) / 9;
    int c = list.at(idx) % 9;
    int count = 0;

    for (int num = 1; num < 10; num++)
    {
        int mask = 1 << num;
        if ((row[r] & mask) == 0 && (col[c] & mask) == 0 && (mat[r / 3][c / 3] & mask) == 0)
        {
            board[r][c] = num;
            row[r] ^= mask;
            col[c] ^= mask;
            mat[r / 3][c / 3] ^= mask;
            count += suduko_03(board, idx + 1, list);
            board[r][c] = 0;
            row[r] ^= mask;
            col[c] ^= mask;
            mat[r / 3][c / 3] ^= mask;
        }
    }

    return count;
}

void sudukoSet()
{
    vector<vector<int>> board = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                                 {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                 {0, 0, 3, 0, 1, 0, 0, 8, 0},
                                 {9, 0, 0, 8, 6, 3, 0, 0, 5},
                                 {0, 5, 0, 0, 9, 0, 6, 0, 0},
                                 {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 7, 4},
                                 {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    // cout << suduko_01(board, 0) << endl;
    // for suduko 2 ==================================
    vector<int> list;
    // for (int i = 0; i < 9; i++)
    // {
    //     for (int j = 0; j < 9; j++)
    //         if (board[i][j] == 0)
    //             list.push_back(i * 9 + j);
    // }
    // cout << suduko_02(board, 0,list) << endl;
    // for suduko 3 ==================================
    // seting the bits;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
                list.push_back(i * 9 + j);
            else
            {
                int mask = 1 << board[i][j];
                row[i] ^= mask;
                col[j] ^= mask;
                mat[i / 3][j / 3] ^= mask;
            }
        }
    }
    cout << suduko_03(board, 0, list) << endl;

    display2D(board);
}

// Word Break ===========================================
unordered_set<string> map;
int wordBreak_01(string word, string ans)
{
    if (word.length() == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = 1; i <= word.length(); i++)
    {
        string temp = word.substr(0, i);
        if (map.find(temp) != map.end())
        {
            count += wordBreak_01(word.substr(i), ans + temp + " ");
        }
    }

    return count;
}

void wordBreak()
{
    vector<string> words = {"mobile", "samsung", "ilike", "sam", "sung",
                            "man", "mango", "icecream", "and",
                            "go", "i", "like", "ice", "cream"};
    for (string word : words)
        map.insert(word);
    string word = "ilikesamsungandmango";
    cout << wordBreak_01(word, "");
}

// Crypto code =====================================================

string str1 = "send";
string str2 = "more";
string str3 = "money";
vector<int> Charmap(26, 0);
int numused = 0;

int strToNum(string str)
{
    int res = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int temp = Charmap[str[i] - 'a'];
        res = res * 10 + temp;
    }
    return res;
}

// recursive function which check for crypto code correctness
int crypto_(string str, int idx)
{
    if (idx == str.length())
    {
        int num1 = strToNum(str1);
        int num2 = strToNum(str2);
        int num3 = strToNum(str3);

        if (num1 + num2 == num3)
            return 1;
        return 0;
    }

    int count = 0;
    for (int num = 0; num <= 9; num++)
    {
        int mask = 1 << num;
        if ((numused & mask) == 0)
        {
            numused ^= mask;
            Charmap[str[idx] - 'a'] = num;
            count += crypto_(str, idx + 1);
            numused ^= mask;
            Charmap[str[idx] - 'a'] = num;
        }
    }

    return count;
}

void crypto()
{
    string str = str1 + str2 + str3;
    //======= first generate unique char =======
    int freq = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int mask = (1 << (str[i] - 'a'));
        freq |= mask;
    }

    // then generate no from freq ============
    str = "";
    for (int i = 0; i < 26; i++)
    {
        int mask = (1 << i);
        if ((freq & mask) != 0)
        {
            str += (char)(i + 'a');
        }
    }

    // cout << str << endl;

    //====== then calling the recursive function to get unique no for all unique char in the str
    cout << crypto_(str, 0) << endl;
}

// Cross Word puzzel placing horizontal and vertical ============

//crossword.========================================================
vector<vector<char>> board{{'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '-', '-', '-', '-', '-', '-', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '-', '-', '-', '-', '-', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}};
vector<string> words = {"agra", "norway", "england", "gwalior"};

bool canPlaceWordH(int r, int c, string &word)
{
    if (c == 0 && word.length() < board[0].size())
    {
        if (board[r][c + word.length()] != '+')
            return false;
    }
    else if ((c + word.length()) == board[0].size() && word.length() != board[0].size())
    {
        if (board[r][c - 1] != '+')
            return false;
    }
    else
    {
        if (((c - 1) >= 0 && board[r][c - 1] != '+') || ((c + word.length()) < board[0].size() && board[r][c + word.length()] != '+'))
            return false;
    }

    for (int i = 0; i < word.length(); i++)
    {
        if ((c + i) < board[0].size() && board[r][c + i] != '-' && board[r][c + i] != word[i])
        {
            return false;
        }
    }
    return true;
}

vector<bool> placeWordH(int r, int c, string &word)
{
    vector<bool> mark(word.length(), false);
    for (int i = 0; i < word.length(); i++)
    {
        if (board[r][c + i] == '-')
        {
            mark[i] = true;
            board[r][c + i] = word[i];
        }
    }
    return mark;
}

void unPlaceWordH(int r, int c, string &word, vector<bool> &mark)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (mark[i])
            board[r][c + i] = '-';
    }
}

bool canPlaceWordV(int r, int c, string &word)
{
    if (r == 0 && r + word.length() < board.size())
    {
        if (board[r + word.length()][c] != '+')
            return false;
    }
    else if ((r + word.length()) == board.size() && word.length() != board.size())
    {
        if (board[r - 1][c] != '+')
            return false;
    }
    else
    {
        if (((r - 1) >= 0 && board[r - 1][c] != '+') || ((r + word.length()) < board.size() && board[r + word.length()][c] != '+'))
            return false;
    }

    for (int i = 0; i < word.length(); i++)
    {
        if ((r + i) < board.size() && board[r + i][c] != '-' && board[r + i][c] != word[i])
        {
            return false;
        }
    }
    return true;
}

vector<bool> placeWordV(int r, int c, string &word)
{
    vector<bool> mark(word.length(), false);
    for (int i = 0; i < word.length(); i++)
    {
        if (board[r + i][c] == '-')
        {
            mark[i] = true;
            board[r + i][c] = word[i];
        }
    }
    return mark;
}

void unPlaceWordV(int r, int c, string &word, vector<bool> &mark)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (mark[i])
            board[r + i][c] = '-';
    }
}

bool crossWord_(int idx)
{
    if (idx == words.size())
    {
        for (vector<char> &ar : board)
        {
            for (char ch : ar)
                cout << ch << " ";
            cout << endl;
        }
        return true;
    }

    string word = words[idx];
    bool res = false;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == '-' || board[i][j] == word[0])
            {
                if (canPlaceWordH(i, j, word))
                {
                    vector<bool> mark = placeWordH(i, j, word);
                    res = res || crossWord_(idx + 1);
                    unPlaceWordH(i, j, word, mark);
                }

                if (canPlaceWordV(i, j, word))
                {
                    vector<bool> mark = placeWordV(i, j, word);
                    res = res || crossWord_(idx + 1);
                    unPlaceWordV(i, j, word, mark);
                }
            }
        }
    }

    return res;
}

void crossWord()
{
    cout << crossWord_(0) << endl;
}

int main(int argc, char const *argv[])
{
    // NqueenSet();
    // sudukoSet();
    // wordBreak();
    // crypto();
    crossWord();
    return 0;
}
