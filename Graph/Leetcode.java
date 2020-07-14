import java.util.LinkedList;
import java.util.ArrayList;
public class Leetcode {


    public static void main(String[] args) {
        //    int[][] matrix = { { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 1 } };
        //    int[][] ans = updateMatrix(matrix);

        //    for(int[] row : ans)
        //    {
        //        for(int el : row)
        //            System.out.print(el + " ");
        //        System.out.println();

        int[][] ar = { { 1, 0 } };
        for (int[] row : ar)
        System.out.println(row[0]+" "+row[1]);
        System.out.println(canFinish(2,ar));
    }
       


    public static void solve(char[][] board) {
        // surroundRegions(board);
       
    }

    // LeetCode 130 Surronding Regions==================
    void mark(char[][] board, int r, int c, int n, int m) {
        if (board[r][c] != 'O')
            return;

        board[r][c] = '#';
        if (r + 1 < n)
            mark(board, r + 1, c, n, m);
        if (c + 1 < m)
            mark(board, r, c + 1, n, m);
        if (r - 1 >= 0)
            mark(board, r - 1, c, n, m);
        if (c - 1 >= 0)
            mark(board, r, c - 1, n, m);
    }

    void surroundRegions(char[][] board) {
        if (board.length == 0)
            return;

        int n = board.length;
        int m = board[0].length;

        for (int i = 0; i < m; i++) {
            if (board[0][i] == 'O')
                mark(board, 0, i, n, m);
            if (board[n - 1][i] == 'O')
                mark(board, n - 1, i, n, m);
        }

        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O')
                mark(board, i, 0, n, m);
            if (board[i][m - 1] == 'O')
                mark(board, i, m - 1, n, m);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '#')
                    board[i][j] = 'O';
            }
        }
    }

    // qno 542
    public static int[][] updateMatrix(int[][] matrix) {

        int n = matrix.length;
        if (n == 0)
            return matrix;
        int m = matrix[0].length;
        if (m == 0)
            return matrix;

        LinkedList<int[]> que = new LinkedList<>();
        // que.addLast(new int[] { matrix[0][0] });

        int dir[][] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
        boolean[] vis = new boolean[n * m];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (matrix[i][j] == 0) {
                    que.addLast(new int[] { i * m + j, 0 });
                    break;
                }

        // int[] pair = que.getFirst();
        // System.out.println(pair[0]);
        // System.out.println(pair[1]);

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int[] rvtx = que.removeFirst();

                int r = rvtx[0] / m;
                int c = rvtx[0] % m;
                int level = rvtx[1];

                for (int d = 0; d < 4; d++) {
                    int x = r + dir[d][0];
                    int y = c + dir[d][1];
                    if (x >= 0 && y >= 0 && x < n && y < m && (vis[x * m + y]==false)) {
                        if (matrix[x][y] == 0) {
                            que.addLast(new int[] { x * m + y, 0 });
                        } else {
                            que.addLast(new int[] { x * m + y, level + 1 });
                            matrix[x][y] = level+1;
                        }
                        vis[x*m+y] = true; //needed to mark inside.
                    }
                }
            }
        }
        return matrix;
    }

    //207
    public static boolean canFinish(int numCourses, int[][] prerequisites) {

        int n = prerequisites.length;
        if (n == 0)
            return true;

        ArrayList<Integer> graph[] = new ArrayList[numCourses];
        for (int i = 0; i < numCourses; i++)
            graph[i] = new ArrayList<Integer>();

        for (int[] row : prerequisites)
            graph[row[0]].add(row[1]);

        int[] indegree = new int[numCourses];
        LinkedList<Integer> que = new LinkedList<>();
        ArrayList<Integer> ans = new ArrayList<>();

        for (int[] row : prerequisites)
            indegree[row[1]]++;

        for (int i = 0; i < numCourses; i++)
            if (indegree[i] == 0)
                que.addLast(i);

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int rvtx = que.removeFirst();
                ans.add(rvtx);

                for (int e : graph[rvtx])
                    if (--indegree[e] == 0)
                        que.addLast(e);
            }
        }

        return ans.size() == numCourses ? true : false;

    }

    //210
    public int[] findOrder(int numCourses, int[][] prerequisites) {

        int n = prerequisites.length;
        if (n == 0) {
            int[] ar = new int[numCourses];
            int idx = 0;
            for (int i = numCourses - 1; i >= 0; i--)
                ar[idx++] = i;
            return ar;
        }
        if (prerequisites[0].length == 0)
            return new int[] { 0 };
        ArrayList<Integer> graph[] = new ArrayList[numCourses];
        for (int i = 0; i < numCourses; i++)
            graph[i] = new ArrayList<>();

        for (int[] row : prerequisites)
            graph[row[0]].add(row[1]);

        int[] indegree = new int[numCourses];
        LinkedList<Integer> que = new LinkedList<>();
        ArrayList<Integer> ans = new ArrayList<>();

        for (int[] row : prerequisites)
            indegree[row[1]]++;

        for (int i = 0; i < numCourses; i++)
            if (indegree[i] == 0)
                que.addLast(i);

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int rvtx = que.removeFirst();
                ans.add(rvtx);

                for (int e : graph[rvtx])
                    if (--indegree[e] == 0)
                        que.addLast(e);
            }
        }

        if (ans.size() != numCourses)
            return new int[0];
        else {
            int[] arr = new int[ans.size()];
            int idx = 0;
            for (int i = ans.size() - 1; i >= 0; i--)
                arr[idx++] = ans.get(i);
            return arr;
        }

    }

    //329
    
    int[][] dir = { { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 0 } };

    public int longestIncreasingPath(int[][] matrix) {

        int n = matrix.length;
        if (n == 0)
            return 0;
        int m = matrix[0].length;
        if (m == 0)
            return 0;
        int[][] dp = new int[n][m];
        int[][] dp_ = new int[n][m];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                for (int d = 0; d < 4; d++) {
                    int x = i + dir[d][0];
                    int y = j + dir[d][1];
                    if (x < n && y < m && x >= 0 && y >= 0 && matrix[i][j] > matrix[x][y])
                        dp[i][j]++;
                }
            }

        int maxLen = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (dp[i][j] == 0)
                    maxLen = Math.max(dfs(i, j, n, m, matrix, dp_), maxLen);
            }

        return maxLen;

    }

    int dfs(int sr, int sc, int n, int m, int[][] matrix, int[][] dp) {
        if (dp[sr][sc] != 0)
            return dp[sr][sc];

        int count = 0;
        for (int d = 0; d < 4; d++) {
            int x = sr + dir[d][0];
            int y = sc + dir[d][1];
            if (x < n && y < m && x >= 0 && y >= 0 && matrix[sr][sc] < matrix[x][y])
                count = Math.max(dfs(x, y, n, m, matrix, dp), count);
        }
        dp[sr][sc] = count + 1;
        return count + 1;
    }

}