#include <iostream>
#include <vector>
#include <string>

using namespace std;

// //211
// class Node
// {
// public:
//     int WordEnd = 0;
//     vector<Node *> childs;

//     Node()
//     {
//         this->childs.assign(26, nullptr);
//         this->WordEnd = 0;
//     }
// };

// Node *root = nullptr;

// void addWord(string word)
// {
//     Node *curr = root;
//     int n = word.length();

//     for (int i = 0; i < n; i++)
//     {
//         int idx = word[i] - 'a';
//         if (curr->childs[idx] == nullptr)
//             curr->childs[idx] = new Node();
//         curr = curr->childs[idx];
//     }
//     curr->WordEnd++;
// }

// bool search_(Node *node, int si, string word)
// {
//     if (node == nullptr)
//         return false;

//     if (si == word.length())
//         return node->WordEnd != 0;

//     bool res = false;
//     if (word[si] == '.')
//     {
//         for (int i = 0; i < 26; i++)
//         {
//             if (node->childs[i] != nullptr)
//                 res = res || search_(node->childs[i], si + 1, word);
//         }
//     }
//     else
//     {
//         int idx = word[si] - 'a';
//         if (node->childs[idx] != nullptr)
//             res = res || search_(node->childs[idx], si + 1, word);
//     }
//     return res;
// }

// bool search(string word)
// {
//     return search_(root, 0, word);
// }

//212
class Node
{
public:
    bool WordEnd = 0;
    string word = "";
    vector<Node *> childs;

    Node()
    {
        this->childs.assign(26, nullptr);
        this->WordEnd = false;
        this->word = "";
    }
};

Node *root = nullptr;

void insert(string &word)
{
    
    Node *curr = root;
    int n = word.size();
    for (int i = 0; i < n; i++)
    {
        int idx = word[i] - 'a';
        if (curr->childs[idx] == nullptr)
            curr->childs[idx] = new Node();
        curr = curr->childs[idx];
    }
    curr->WordEnd = true;
    curr->word = word;
}

int dirA[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<string> ans;
int n, m;

void dfs(int r, int c, Node *node, vector<vector<char>> &board)
{
    if (node->WordEnd)
    {
        node->WordEnd = false;
        ans.push_back(node->word);
    }
    char ch = board[r][c];
    board[r][c] = '$';
    for (int d = 0; d < 4; d++)
    {
        int x = r + dirA[d][0];
        int y = c + dirA[d][1];
        if (x >= 0 && y >= 0 && x < n && y < m && board[x][y] != '$' && node->childs[board[x][y] - 'a'] != nullptr)
            dfs(x, y, node->childs[board[x][y] - 'a'], board);
    }
    board[r][c] = ch;
}

vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
{

    if (board.size() == 0 || board[0].size() == 0 || words.size() == 0)
        return {};
    
    root = new Node();

    for (string &word : words)
    {
        insert(word);
    }
    
    n = board.size();
    m = board[0].size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (root->childs[board[i][j] - 'a'] != nullptr)
                dfs(i, j, root->childs[board[i][j] - 'a'], board);
        }
    }

    return ans;
}

int main(int argc, char const *argv[])
{
    vector<vector<char>> board = {{'o', 'a', 'a', 'n'},
                                  {'e', 't', 'a', 'e'},
                                  {'i', 'h', 'k', 'r'},
                                  {'i', 'f', 'l', 'v'}};
    vector<string> words = {"oath",
                             "pea",
                             "eat",
                             "rain"};
    vector<string> ans = findWords(board, words);


    for(string out:ans)
    {
        cout << out << "";
    }
    return 0;
}
