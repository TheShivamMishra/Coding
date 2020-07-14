import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.HashMap;
import java.util.HashSet;

public class l001 {

    public static void main(String[] args) {
        solve();
    }

    public static int N = 7;
    public static ArrayList<Edge>[] graph;

    public static class Edge {
        int v;
        int w;

        Edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }

    public static void addEdge(ArrayList<Edge>[] gp, int u, int v, int w) {
        gp[v].add(new Edge(u, w));
        gp[u].add(new Edge(v, w));
    }

    public static void display(ArrayList<Edge>[] gp) {
        for (int i = 0; i < gp.length; i++) {
            System.out.print(i + "->");
            for (Edge e : gp[i]) {
                System.out.print("(" + e.v + "," + e.w + ") ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void constructGraph() {
        graph = new ArrayList[N];
        for (int i = 0; i < graph.length; i++) {
            graph[i] = new ArrayList<Edge>();
        }
        addEdge(graph, 0, 1, 10);
        addEdge(graph, 0, 3, 20);
        addEdge(graph, 1, 2, 20);
        addEdge(graph, 2, 3, 40);
        addEdge(graph, 3, 4, 2);
        addEdge(graph, 4, 5, 3);
        addEdge(graph, 5, 6, 2);
        addEdge(graph, 4, 6, 8);

        display(graph);
    }

    // bfs of graph using linkedlist of class as queue =============================

    public static class pair {

        int vtx;
        String psf;
        int level = 0;

        pair(int vtx, String psf) {
            this.vtx = vtx;
            this.psf = psf;
        }

        pair(int vtx, String psf, int level) {
            this.vtx = vtx;
            this.psf = psf;
            this.level = level;
        }
    }

    // bfs method to find level we have use delimiter i.e null
    public static void BFS(int src, boolean[] vis) {

        LinkedList<pair> que = new LinkedList<>();

        // LinkedList<int[]> que=new LinkedList<>(); //not using a pair.
        // que.addLast(new int[]{1,0})

        que.addLast(new pair(src, src + ""));
        que.addLast(null); // adding null at the end.
        int dest = 6;
        int level = 0;

        while (que.size() != 1) {
            pair rvtx = que.removeFirst();

            if (vis[rvtx.vtx]) {
                System.out.println("Cycle :" + rvtx.psf);
                continue;
            }

            if (rvtx.vtx == dest) {
                System.out.println("Destination : " + rvtx.psf + "->" + level);
            }

            vis[rvtx.vtx] = true;

            for (Edge e : graph[rvtx.vtx]) {
                if (!vis[e.v]) {
                    que.addLast(new pair(e.v, rvtx.psf + e.v));
                }
            }

            if (que.getFirst() == null) { // updating the level and shifting the null to the end.
                level++;
                que.removeFirst();
                que.addLast(null);
            }
        }

    }

    // bfs method 2 in which we use class pair length to set length of each vtx.
    public static void BFS_02(int src, boolean[] vis) {

        LinkedList<pair> que = new LinkedList<>();
        que.addLast(new pair(src, src + "", 0));
        int dest = 6;

        while (!que.isEmpty()) {
            pair rvtx = que.removeFirst();

            if (vis[rvtx.vtx]) {
                System.out.println("Cycle :" + rvtx.psf);
                continue;
            }

            if (rvtx.vtx == dest) {
                System.out.println("Destination : " + rvtx.psf + "->" + rvtx.level);
            }

            vis[rvtx.vtx] = true;

            for (Edge e : graph[rvtx.vtx]) { // updating the level
                if (!vis[e.v]) {
                    que.addLast(new pair(e.v, rvtx.psf + e.v, rvtx.level + 1));
                }
            }

        }

    }

    // Bipartitie of a graph ===============================================
    public static boolean bipartitelGraph_(int src, int[] vis) {
        LinkedList<int[]> que = new LinkedList<>(); // que with first for vrtx and second;
        que.addLast(new int[] { src, 0 }); // src with color 0 1.e Red;

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int[] rvtx = que.removeFirst();

                if (vis[rvtx[0]] != -1) {
                    if (vis[rvtx[0]] != rvtx[1]) {
                        return false;
                    }
                }

                vis[rvtx[0]] = rvtx[1];

                for (Edge e : graph[rvtx[0]]) {
                    if (vis[e.v] == -1) {
                        que.addLast(new int[] { e.v, (rvtx[1] + 1) % 2 });
                    }
                }
            }
        }

        return true;
    }

    public static void bipartitieGraph() {
        int vis[] = new int[N];
        Arrays.fill(vis, -1);
        boolean res = false;
        for (int i = 0; i < N && !res; i++)
            if (vis[i] == -1)
                System.out.println(bipartitelGraph_(i, vis));
    }

    // leetcode 815.=======================================================
    public int numBusesToDestination(int[][] routes, int S, int T) {
        if (routes.length == 0)
            return -1;
        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();
        for (int i = 0; i < routes.length; i++) {
            for (int ele : routes[i]) {
                map.putIfAbsent(ele, new ArrayList<>());
                map.get(ele).add(i);
            }
        }

        HashSet<Integer> busStandVis = new HashSet();
        boolean[] busVis = new boolean[routes.length];

        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(S);
        int level = 0;
        busStandVis.add(S);

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int stand = que.removeFirst();

                if (stand == T)
                    return level;

                for (int bus : map.get(stand)) {
                    if (busVis[bus])
                        continue;

                    for (int busStand : routes[bus]) {
                        if (!busStandVis.contains(busStand)) {
                            que.addLast(busStand);
                            busStandVis.add(busStand);
                        }
                    }
                    busVis[bus] = true;
                }
            }
            level++;
        }

        return -1;
    }

    // Kruskal Algo for finding Minimumm cost Spanning Tree using union find
    public static int[] par;
    public static int[] setSize;

    public static int findPar(int vtx) {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findPar(par[vtx]);
    }

    public static void mergeSet(int p1, int p2) {
        if (setSize[p1] < setSize[p2]) {
            par[p1] = p2;
            setSize[p2] += setSize[p1];
        } else {
            par[p2] = p1;
            setSize[p1] += setSize[p2];
        }
    }

    public static void Kruskal(int[][] arr) {

        ArrayList<Edge>[] KruskalGraph = new ArrayList[N];

        for (int i = 0; i < N; i++)
            KruskalGraph[i] = new ArrayList<>();

        Arrays.sort(arr, (int[] a, int[] b) -> { // this is a , O is b;
            return a[2] - b[2]; // default behavior i.e (this - O) is increaing;
            // return b[2] - a[2]; // provide decreaing order i.e reverse of default;
        });

        for (int[] ar : arr) {
            int u = ar[0];
            int v = ar[1];

            int p1 = findPar(u);
            int p2 = findPar(v);
            if (p1 != p2) {
                mergeSet(p1, p2);
                addEdge(KruskalGraph, u, v, ar[2]);
            }
        }

        display(KruskalGraph);
    }

    // Dijkstra Algorithm using simple bfs method ===============================
    // public static class pair_ implements Comparable<pair_> {

    // int src;
    // int par;
    // int w;
    // int wsf;

    // pair_(int src, int par, int w, int wsf) {
    // this.src = src;
    // this.par = par;
    // this.w = w;
    // this.wsf = wsf;
    // }

    // public int compareTo(pair_ o)
    // {
    // return this.wsf - o.wsf; // default behaviour min pq;
    // // return o.wsf - this.wsf; // max pq;
    // }
    // }

    public static class pair_ {

        int src;
        int par;
        int w;
        int wsf;

        pair_(int src, int par, int w, int wsf) {
            this.src = src;
            this.par = par;
            this.w = w;
            this.wsf = wsf;
        }
    }

    public static void DijkstraAlgo(int src) {

        ArrayList<Edge>[] dijkstragraph = new ArrayList[N];
        for (int i = 0; i < N; i++)
            dijkstragraph[i] = new ArrayList<Edge>();

        // PriorityQueue<pair_> pq = new PriorityQueue<pair_>(); // using with
        // implements comparable
        PriorityQueue<pair_> pq = new PriorityQueue<pair_>((pair_ a, pair_ b) -> { // this pq is with inside comparator
            return a.wsf - b.wsf; // default behaviour min pq;
            // return b.wsf - a.wsf; // max pq;
        });

        boolean[] vis = new boolean[N];
        pq.add(new pair_(src, -1, 0, 0));

        while (pq.size() != 0) {
            int size = pq.size();
            while (size-- > 0) {
                pair_ rvtx = pq.remove();

                if (vis[rvtx.src]) // for cycle
                    continue;

                if (rvtx.par != -1) // for creating dijkstras graph
                    addEdge(dijkstragraph, rvtx.par, rvtx.src, rvtx.wsf);

                vis[rvtx.src] = true;
                for (Edge e : graph[rvtx.src])
                    if (!vis[e.v])
                        pq.add(new pair_(e.v, rvtx.src, e.w, rvtx.wsf + e.w));
            }
        }

        display(dijkstragraph);
    }

    // Prims Algo using BFS : use this when we need to find MST with creating graph
    public static void PrimsAlgo(int src) {

        ArrayList<Edge>[] primsGraph = new ArrayList[N];
        for (int i = 0; i < N; i++)
            primsGraph[i] = new ArrayList<Edge>();

        // PriorityQueue<pair_> pq = new PriorityQueue<pair_>(); // using with
        // implements comparable
        PriorityQueue<pair_> pq = new PriorityQueue<pair_>((pair_ a, pair_ b) -> { // this pq is with inside comparator
            return a.w - b.w; // default behaviour min pq;
            // return b.w - a.w; // max pq;
        });

        boolean[] vis = new boolean[N];
        pq.add(new pair_(src, -1, 0, 0));

        while (pq.size() != 0) {
            int size = pq.size();
            while (size-- > 0) {
                pair_ rvtx = pq.remove();

                if (vis[rvtx.src]) // for cycle
                    continue;

                if (rvtx.par != -1) // for creating dijkstras graph
                    addEdge(primsGraph, rvtx.par, rvtx.src, rvtx.wsf);

                vis[rvtx.src] = true;
                for (Edge e : graph[rvtx.src])
                    if (!vis[e.v])
                        pq.add(new pair_(e.v, rvtx.src, e.w, rvtx.wsf + e.w));
            }
        }

        display(primsGraph);
    }

    public static void solve() {
        constructGraph();

        // boolean[] vis = new boolean[N];
        // BFS(0, vis);
        // BFS_02(0, vis);
        // bipartitieGraph();
        DijkstraAlgo(0);
    }

}