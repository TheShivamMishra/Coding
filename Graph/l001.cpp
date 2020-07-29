#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Edge
{
public:
    int v;
    int w;
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
    Edge e1(u, w);
    Edge e2(v, w);
    gp[v].push_back(e1);
    gp[u].push_back(e2);
}

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
    addEdge(graph, 0, 3, 20);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 40);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 3);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 4, 6, 8);

    // addEdge(graph, 2, 5, 2);
    display(graph);
}

int findEdge(int v1, int v2)
{
    int vtx = -1;
    for (int i = 0; i < graph[v1].size(); i++)
    {
        Edge e = graph[v1][i];
        if (e.v == v2)
        {
            vtx = i;
            break;
        }
    }
    return vtx;
}

void removeEdge(int u, int v)
{
    int idx1 = findEdge(u, v);
    int idx2 = findEdge(v, u);
    graph[u].erase(graph[u].begin() + idx1);
    graph[v].erase(graph[v].begin() + idx2);
}

void removeVtx(int vtx)
{
    while (graph[vtx].size() != 0)
    {
        //int vtx2=graph[vtx][graph[vtx].size()-1];

        Edge e = graph[vtx].back();
        removeEdge(vtx, e.v);
    }
}

// questions =============================================================
// Dfs structrue for grpah
bool hasPath(int src, int dest, vector<bool> &vis)
{
    if (src == dest)
    {
        return true;
    }

    vis[src] = true;
    bool res = false;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            res = res || hasPath(e.v, dest, vis);
    }

    return res;
}

int allPath(int src, int dest, vector<bool> &vis, int w, string ans)
{
    if (src == dest)
    {
        cout << ans << dest << " @ " << w << endl;
        return 1;
    }

    vis[src] = true;
    int count = 0;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            count += allPath(e.v, dest, vis, w + e.w, ans + to_string(src) + " ");
    }

    vis[src] = false;
    return count;
}

class allSolutionPair
{

public:
    int lightW = 1e7;
    int heavyW = 0;
    int ceil = 1e7;
    int floor = 0;
};

void allSolution(int src, int dest, vector<bool> &vis, int w, allSolutionPair &pair, int data, string ans)
{
    if (src == dest)
    {
        pair.heavyW = max(w, pair.heavyW);
        pair.lightW = min(w, pair.lightW);
        if (w < data)
            pair.floor = max(pair.floor, w);
        if (w > data)
            pair.ceil = min(pair.ceil, w);
        return;
    }

    vis[src] = true;
    int count = 0;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            allSolution(e.v, dest, vis, w + e.w, pair, data, ans + to_string(src) + " ");
    }

    vis[src] = false;
}

//all Hamilton Path and cycle in a Graph ================================

void hamintonianPath(int src, int osrc, vector<bool> &vis, int count, string ans)
{
    if (count == vis.size() - 1)
    {
        int idx = findEdge(osrc, src);
        if (idx != -1)
            cout << "cycle :-> " << ans + to_string(src) << endl;
        else
            cout << "path :-> " << ans + to_string(src) << endl;
    }

    vis[src] = true;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            hamintonianPath(e.v, osrc, vis, count + 1, ans + to_string(src) + " ");
    }
    vis[src] = false;
}

// Get Common Component =================================================

void gccDfs(int src, vector<bool> &vis)
{
    vis[src] = true;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
            gccDfs(e.v, vis);
    }
}

void Gcc()
{
    vector<bool> vis(N, false);
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            count++;
            gccDfs(i, vis);
        }
    }

    cout << count << endl;
}

// Bfs traversal in graph using queue and a pair ======================================
// method first for bfs storing the path of string of each vrtx
void BFS(int src, vector<bool> &vis)
{
    queue<pair<int, string>> que;
    int dest = 6;
    que.push({src, to_string(src) + ""});

    while (!que.empty())
    {
        pair<int, string> rvtx = que.front(); // removing form que.
        que.pop();

        if (vis[rvtx.first])
        { // the work of this loop is to detect cycle
            cout << "Cycle: " << rvtx.second << endl;
            continue;
        }

        if (rvtx.first == dest)
        {
            cout << "Destination: " << rvtx.second << endl;
        }

        vis[rvtx.first] = true; // marking true

        for (Edge e : graph[rvtx.first]) // traversing all the unvisited nebighours
        {
            if (!vis[e.v])
            {
                que.push({e.v, rvtx.second + to_string(e.v)});
            }
        }
    }
}

//bfs with count of cycles in it
void BFS_02(int src, vector<bool> &vis)
{
    queue<int> que;
    que.push(src);

    int level = 0;
    int dest = 6;
    int cycle = 0;

    while (que.size() != 0)
    {
        int size = que.size();

        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            if (vis[rvtx])
            {
                cout << "Cycle: " << rvtx << endl;
                cycle++;
                continue;
            }

            if (rvtx == dest)
            {
                cout << "Destination: " << rvtx << endl;
            }

            vis[rvtx] = true;

            for (Edge e : graph[rvtx])
            {
                if (!vis[e.v])
                {
                    que.push(e.v);
                }
            }
        }

        level++;
    }

    cout << "total cycle: " << cycle << endl;
}

//bfs in this we mark true each edge inside the for loop but we can't find the cycle in the graph.
void BFS_03(int src, vector<bool> &vis)
{
    queue<int> que;
    que.push(src);
    vis[src] = true;

    int dest = 6;
    int level = 0;

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            if (rvtx == dest)
            {
                cout << "Destination: " << rvtx << " level: " << level << endl;
            }

            for (Edge e : graph[rvtx])
            {
                if (!vis[e.v])
                {
                    que.push(e.v);
                    vis[e.v] = true;
                }
            }
        }
        level++;
    }
}

//is bipartitie graph

bool isBipartiteBFS(int src, vector<int> &vis)
{
    queue<pair<int, int>> que; //first is src and second is color.
    que.push({src, 0});        // src is red.
    int cycle = 0;

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            pair<int, int> rvtx = que.front();
            que.pop();

            if (vis[rvtx.first] != -1) // already visited(cycle).
            {
                cycle++;
                if (vis[rvtx.first] != rvtx.second) // check for conflict.
                    return false;
            }

            vis[rvtx.first] = rvtx.second;
            for (Edge e : graph[rvtx.first])
            {
                if (vis[e.v] == -1)
                    que.push({e.v, (rvtx.second + 1) % 2});
            }
        }
    }
    cout << cycle << endl;
    return true;
}

void isBipartite()
{
    vector<int> vis(N, -1); // -1 : unvisited, 0 : red, 1 : green
    for (int i = 0; i < N; i++)
    {
        if (vis[i] == -1)
            cout << (boolalpha) << isBipartiteBFS(i, vis) << endl;
    }
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

// Dijkstra Algorithm using simple bfs method ===============================
class dpair
{
public:
    int src;
    int par;
    int w;
    int wsf;

    dpair(int src, int par, int w, int wsf)
    {
        this->src = src;
        this->par = par;
        this->w = w;
        this->wsf = wsf;
    }

    // bool operator < (dpair &o)
    // {
    //     return this->wsf > o.wsf; // default min pq;
    //     //   return o.wsf > this->wsf; // max pq;
    // }
};

struct Dcomp
{ // this - o is replaced by '>' because the pq is default min
public:
    bool operator()(dpair &a, dpair &b)
    {
        return a.wsf > b.wsf; // default min pq
                              //   return b.wsf > a.wsf // max pq;
    }
};

void DijkstraAlgo(int src)
{

    vector<vector<Edge>> DijkstraGraph(N, vector<Edge>());
    priority_queue<dpair, vector<dpair>, Dcomp> pq; // By default min pq
    vector<bool> vis(N, false);
    pq.push(dpair(src, -1, 0, 0));

    while (pq.size() != 0)
    {
        int size = pq.size();
        while (size-- > 0)
        {
            dpair rvtx = pq.top();
            pq.pop();

            if (vis[rvtx.src]) // for cycle
                continue;

            if (rvtx.src != -1) // for creating dijkstras graph
                addEdge(DijkstraGraph, rvtx.src, rvtx.par, rvtx.w);

            vis[rvtx.src] = true;
            for (Edge e : graph[rvtx.src])
                if (!vis[e.v])
                    pq.push(dpair(e.v, rvtx.src, e.w, rvtx.wsf + e.w));
        }
    }

    display(DijkstraGraph);
}

// prims Algo : it's same as dijkstras to find MST in a grpah in a ordered with src
struct Pcomp
{ // this - o is replaced by '>' because the pq is default min
public:
    bool operator()(dpair &a, dpair &b)
    {
        return a.w > b.w; // default min pq;
        //return b.w > a.w; // max pq;
    }
};

void PrimsAlgo(int src)
{

    vector<vector<Edge>> PrimsGraph(N, vector<Edge>());
    priority_queue<dpair, vector<dpair>, Pcomp> pq; // By default min pq
    vector<bool> vis(N, false);
    pq.push(dpair(src, -1, 0, 0));

    while (pq.size() != 0)
    {
        int size = pq.size();
        while (size-- > 0)
        {
            dpair rvtx = pq.top();
            pq.pop();

            if (vis[rvtx.src]) // for cycle
                continue;

            if (rvtx.src != -1) // for creating dijkstras graph
                addEdge(PrimsGraph, rvtx.src, rvtx.par, rvtx.w);

            vis[rvtx.src] = true;
            for (Edge e : graph[rvtx.src])
                if (!vis[e.v])
                    pq.push(dpair(e.v, rvtx.src, e.w, rvtx.wsf + e.w));
        }
    }

    display(PrimsGraph);
}

void set1()
{
    // removeEdge(3, 4);
    // vector<bool> vis(N, false);
    // cout<< hasPath(0, 6, vis);
    // removeVtx(3);
    // display(graph);
    // cout << allPath(0, 6, vis, 0, "") << endl;
    // allSolutionPair pair;
    // allSolution(0, 6, vis, 0, pair, 30, "");
    // cout << pair.ceil << " " << pair.floor << " " << pair.heavyW << " " << pair.lightW;
    // hamintonianPath(2, 2, vis, 0, "");
    // Gcc();
    // BFS(0, vis);
    // BFS_02(0, vis);
    // BFS_03(0, vis);
    // isBipartite();
    // DijkstraAlgo(2);
}

void solve()
{
    constructGraph();
    set1();
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
