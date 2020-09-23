#include "bits/stdc++.h"
#define lli long long int
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define loop(n) for (int i = 0; i < n; i++)
using namespace std;

// building segment tree using segtree array;

void makeST(vi &arr, vi &segtree, int l, int r, int idx)
{
    if (l == r)
    {
        segtree[idx] = 1;
        return;
    }
    int mid = (l + r) / 2;
    makeST(arr, segtree, l, mid, 2 * idx + 1);
    makeST(arr, segtree, mid + 1, r, 2 * idx + 2);
    int count = 0;
    unordered_set<int> map;
    for (int i = l; i <= r; i++)
    {
        if (map.find(arr[i]) == map.end())
            count++;
        map.insert(arr[i]);
    }
    segtree[idx] = count;
    // cout<<segtree[idx]<<endl;
}

void createSegmentTree(vi &arr, vi &segtree, int n)
{
    int size = 0;
    int x = (int)ceil(log(n));  // height of a compelete binary tree i.e a segmetntree;
    size = 2 * (pow(2, x)) - 1; // size of the segment tree : because their will be exacty n leaves and (n-1){internal nodes in a completer binary tree};
                                // hence total nodes will be n + n-1
    segtree.assign(size, 0);
    makeST(arr, segtree, 0, n - 1, 0);
}

int getQuery(vi &segtree, int l, int r, int low, int high, int pos) // using overlaping structre to get query result;
{
    cout<<low<<" "<<high<<endl;
    if (low >= l && high <= r)
        return segtree[pos]; // total overlap;

    if (high < l || low > r)
        return 0; //no overlap;

    int mid = (low + high) / 2;
    return getQuery(segtree, l, r, low, mid, 2 * pos + 1) + getQuery(segtree, l, r, mid + 1, high, 2 * pos + 1);
}

void solve()
{
    int n;
    cin >> n;
    vi arr(n, 0);
    loop(n) cin >> arr[i];
    int size = 0;
    int x = (int)ceil(log2(n)); // height of a compelete binary tree i.e a segmetntree;
    size = 2 * (pow(2, x)) - 1;
    // cout<<size<<endl;
    vi segtree(size, 0);
    makeST(arr, segtree, 0, n - 1, 0);
    // loop(size) cout << segtree[i] << " ";
    int queries;
    cin >> queries;
    while (queries--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << getQuery(segtree, l, r, 0, n - 1, 0) << "\n";
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
