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

auto SpeedUp = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

void computLps(vi& lps, string p)
{
    int n = p.size();
    lps[0] = 0;
    int i = 1, j=0;
    while (i<n)
    {
        if (p[j]==p[i])
        {
            lps[i] = j+1;
            i++;j++;
        }
        else
        {
            if (j!=0)
                j = lps[j-1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }

    }
}

void KMP()
{
    string text, pattern;
    cin>>text>>pattern;

    int n = text.size(), m =pattern.size();

    vi lps(m, 0);
    computLps(lps, pattern);

    int i=0, j=0;
    while (i<n)
    {
        if (pattern[j]==text[i])
        {
            j++;i++;
        }
        if (j==m)
        {
            cout<<"Found Pattern at"<<(i-j)<<endl;
            j = lps[j-1];
        }
        else if(i<n && pattern[j]!=text[i])
        { 
            if (j!=0)
                j = lps[j-1];
            else
                i++;
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
        KMP();
    return 0;
}