import java.util.ArrayList;
import java.util.LinkedList;

public class l002_directedGraph {

    public static void main(String[] args) {
        solve();
    }

    static int N = 8;
    static ArrayList<Integer> graph[];

    public static void display() {
        for (int i = 0; i < graph.length; i++) {
            System.out.print(i + "->");
            for (Integer e : graph[i]) {
                System.out.print("(" + e + ") ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void constructGraph() {
        graph = new ArrayList[N];
        for (int i = 0; i < graph.length; i++)
            graph[i] = new ArrayList<Integer>();

        graph[7].add(5);
        graph[7].add(6);
        graph[5].add(4);
        graph[5].add(2);
        graph[6].add(4);
        graph[6].add(3);
        graph[2].add(1);
        graph[3].add(1);
        graph[1].add(0);

        display();

    }

    // Topological sort for directed
    // Graph===================================================
    public static void topologicalSort_(int src, boolean[] vis, ArrayList<Integer> ans) { // dfs
        vis[src] = true;

        for (Integer e : graph[src])
            if (!vis[e])
                topologicalSort_(e, vis, ans);

        ans.add(src);
    }

    public static void topologicalSort() {
        ArrayList<Integer> ans = new ArrayList<>();
        boolean vis[] = new boolean[N];

        for (int i = 0; i < N; i++) // calling the topologicalsort_ for all the gcc of graph.
            if (!vis[i])
                topologicalSort_(i, vis, ans);

        for (int i = ans.size() - 1; i >= 0; i--) // printing the stack in revrse order.
            System.out.print(i + " ");
    }

    // Kahns Algo For used for topological sort and cycle founding in
    // graph=====================
    public static void KahnsAlgo() {

        int[] indegree = new int[N];

        for (int i = 0; i < N; i++) { // creating indegree array.
            for (Integer e : graph[i])
                indegree[e]++;
        }

        LinkedList<Integer> que = new LinkedList<>();
        for (int i = 0; i < N; i++) // adding all the 0 indgree in queue.
            if (indegree[i] == 0)
                que.addLast(i);

        ArrayList<Integer> ans = new ArrayList<>();
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int rvtx = que.removeFirst();
                ans.add(rvtx);

                for (int e : graph[rvtx]) {
                    if (--indegree[e] == 0)
                        que.addLast(e);
                }

            }

        }

        if (ans.size() != N)
            System.out.println("Cycle");
        else
            System.out.println(ans);

    }

    // topological sort using dfs marking the array 1 for current path as visiting
    // to find cycle.
    public static boolean topologicalSort_(int src, int[] vis, ArrayList<Integer> ans) {
        if (vis[src] == 1)// visited vertex in my path.
            return true;
        if (vis[src] == 2) // already viseited vertex but not by my path.
            return false;

        vis[src] = 1;
        boolean res = false;
        for (int e : graph[src]) {
            res = res || topologicalSort_(e, vis, ans);
        }

        vis[src] = 2;
        ans.add(src);
        return res;
    }

    public static void topologicalSortCycle() {
        int[] vis = new int[N];
        ArrayList<Integer> ans = new ArrayList<>();

        boolean res = false;
        for (int i = 0; i < N && !res; i++)
            if (vis[i] == 0)
                res = res || topologicalSort_(i, vis, ans);

        if (!res) {
            System.out.println(ans);
        } else
            System.out.println("Cycle :" + ans);
    }

    // Scc of a graph using kosa raju algo.======================
    public static void dfs_scc(int src, ArrayList<Integer>[] ngraph, boolena[] vis, ArrayList<Integer> ans) {
        vis[src] = true;
        for (int ele : ngraph[src]) {
            if (!vis[ele])
                dfs_scc(e, ngraph, vis, ans);
        }
    }

    public static void KosaRajuAlgo() {
        boolean vis[] = new boolean[N];
        ArrayList<Integer> ans = new ArrayList<>(); // getting topo Order in which we have to travel;
        for (int i = 0; i < N; i++)
            if (!vis[i])
                topologicalSort_(i, vis, ans);

        ArrayList<Integer>[] ngraph = new ArrayList[N]; // creation of a new graph;
        for (int i = 0; i < N; i++)
            ngraph[i] = new ArrayList<>();

        for (int i = 0; i < N; i++) { // inversion of old graph and storing it into ngraph;
            for (int ele : graph[i]) {
                ngraph[ele].add(i);
            }
        }

        vis = new boolean[N];
        count = 0;
        for (int i = ans.size() - 1; i >= 0; i--) // running again dfs but now on topo Order obtianed;
        {
            if (!vis[ans.get(i)]) {
                ArrayList<Integer> ans_ = new ArrayList<>();
                dfs_scc(ans.get(i), ngraph, vis, ans_);
                System.out.println(ans_);
                count++;
            }
        }

        System.out.println(count);

    }

    public static void solve() {
        constructGraph();
        // topologicalSort();
        // KahnsAlgo();
        topologicalSortCycle();
    }
}