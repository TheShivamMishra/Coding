#include "bits/stdc++.h"
#define vi vector<int>
#define vb vector<bool>
#define lli long long int
#define vvi vector<vector<int>>
#define loop(n) for (int i = 0; i < n; i++)
using namespace std;

auto SpeedUp = []() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

// segment tree ane different queries on them.
// at max ST takes O(4n) space ans at max O(4longn) search queries time. used array to represent ST
// they ineffective when we have so many updates on the array.
void constructST(vi &arr, vi &segTree, int low, int high, int pos)
{
    if (low == high)
    {
        segTree[pos] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    constructST(arr, segTree, low, mid, 2 * pos + 1);
    constructST(arr, segTree, mid + 1, high, 2 * pos + 2);
    segTree[pos] = min(segTree[2 * pos + 1], segTree[2 * pos + 2]);
}

int rangeMinQurey(vi &segTree, int l, int r, int low, int high, int pos) // range queries use total overlap, partial overrlap,no overlap method;
{
    if (l <= low && r >= high)
        return segTree[pos]; // total overlap condition;

    if (l > high || r < low)
        return 1e9; // no overlap;

    int mid = (low + high) / 2; //partial overlap condition;
    return min(rangeMinQurey(segTree, l, r, low, mid, 2 * pos + 1), rangeMinQurey(segTree, l, r, mid + 1, high, 2 * pos + 2));
}

void solve()
{
    int n = 4;
    vi arr = {-1, 0, 3, 6};
    //Height of segment tree
    int x = (int)(ceil(log2(n)));

    //Maximum size of segment tree
    int size = 2 * (int)pow(2, x) - 1;

    vi segTree(size, (int)1e9);

    constructST(arr, segTree, 0, n - 1, 0); //function to construct the segment tree;

    int querie;
    cin >> querie;
    int l, r;
    while (querie--)
    {
        cin >> l >> r;
        cout << rangeMinQurey(segTree, l, r, 0, n - 1, 0); // running queries on segtree lakes queries*long(n) time total;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}