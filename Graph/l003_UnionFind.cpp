#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
class Edge
{
public:
    int v = 0;
    int w = 0;

    Edge(int v, int w)
    {
        this->v = v;
        this->w = w;
    }
};

int N = 7;
vector<vector<Edge>> graph(N, vector<Edge>());

void addEdge(vector<vector<Edge>> &gp, int u, int v, int w)
{
    gp[u].push_back(Edge(v, w));
    gp[v].push_back(Edge(u, w));
}

//unionFind.==============================================

// vector<int> par;
// vector<int> setSize;

// //path compression code =================================
// int findPar(int vtx)
// {
//     if (par[vtx] == vtx)
//         return vtx;
//     return par[vtx] = findPar(par[vtx]);
// }

// void mergeSet(int l1, int l2)
// {
//     if (setSize[l1] < setSize[l2])
//     {
//         par[l1] = l2;
//         setSize[l2] += setSize[l1];
//     }
//     else
//     {
//         par[l2] = l1;
//         setSize[l1] += setSize[l2];
//     }
// }

// void unionFind()
// {
// }

void display(vector<vector<Edge>> &gp)
{
    for (int i = 0; i < gp.size(); i++)
    {
        cout << i << "-> ";
        for (Edge e : gp[i])
        {
            cout << "(" << e.v << "," << e.w << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

void constructGraph()
{
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 3, 10);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 40);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 4, 6, 3);
    addEdge(graph, 5, 6, 8);

    // addEdge(graph, 2, 5, 2);

    // display(graph);
    cout << endl;
}


//Kruskal Algo for finding Minimumm cost Spanning Tree using union find
vector<int> par;
vector<int> setSize;

int findPar(int vtx)
{
    if (par[vtx] == vtx)
        return vtx;
    return par[vtx] = findPar(par[vtx]);
}

void mergeSet(int p1, int p2)
{
    if (setSize[p1] < setSize[p2])
    {
        par[p1] = p2;
        setSize[p2] += setSize[p1];
    }
    else
    {
        par[p2] = p1;
        setSize[p1] += setSize[p2];
    }
}

void Kruskal(vector<vector<int>> &arr)
{
    vector<vector<Edge>> Kruskalgraph(arr.size(), vector<Edge>());

    sort(arr.begin(), arr.end(), [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2]; // this - other,default is Increasing, '-' replace with '<'
    });

    for (vector<int> &ar : arr)
    {
        int u = ar[0];
        int v = ar[1];

        int p1 = findPar(u);
        int p2 = findPar(v);
        if (p1 != p2)
        {
            mergeSet(p1, p2);
            addEdge(Kruskalgraph, u, v, ar[2]);
        }
    }

    display(Kruskalgraph);
}

void solve()
{
    constructGraph();
}

int main()
{
    solve();
    return 0;
}
