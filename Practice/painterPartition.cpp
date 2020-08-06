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

// binary search didn't produce the correct result for some testcases;
bool isCanPaint(vi& arr, int mid, int p)
{
    int sum = 0, reqp=1;
    for (int i=0;i<arr.size();i++)
    {
        if (sum>mid)
        {
            sum = 0;
            reqp++;
            if (reqp>p)
                return false;
        }
        sum+=arr[i];
    }
    return true;
}

int painterPartition(vi& arr, int n, int p)
{
    int si = 0, ei = 0;
    loop(n) ei +=arr[i];
    int ans = 0;
    while (si<=ei)
    {
        int mid = (si+ei)/2;

        if (isCanPaint(arr, mid, p))
        {
            ei = mid - 1;
            ans = mid;
        }
        else
            si = mid+1;
    }

    return ans;
}

int solve()
{
    int k, n;
    cin>>k>>n;
    vi arr(n);
    loop(n) cin>>arr[i];
    
    vvi dp(k+1, vi(n+1, 0)); //using dp method to get correct ans;

    for (int i=1;i<=n;i++)
        dp[1][i] = dp[1][i-1] + arr[i-1];
    for (int j =1;j<=k;j++)
        dp[j][1] = arr[0];

    for(int i=2;i<=k;i++)    
    { 
        for(int j = 2;j<=n;j++)
        { 
            int ans = 1e8;
            int sum = 0;
            for(int z = j;z>=1;z--)
            { 
                sum +=arr[z-1];
                ans = min(ans, max(dp[i-1][z-1], sum));
            }

            dp[i][j] = ans;
        }
    }

    // for(vi& ar:dp)
    // { 
    //     for (int ele : ar)
    //         cout<<ele<<" ";
    //     cout<<endl;
    // }
    return dp[k][n];
    // return painterPartition(arr, n, p);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cout << solve() << endl;
    }
    return 0;
}