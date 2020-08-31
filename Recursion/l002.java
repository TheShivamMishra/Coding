
public class l002 {

    public static void main(String[] args) {

        int[][] board = new int[4][4];
        // System.out.println(floodFill_Heigth(0, 0, board.length - 1, board[0].length -
        // 1, board));
        // pair ans = floodFill_LongestPath(0, 0, board.length - 1, board[0].length - 1,
        // board);
        pair ans = floodFill_SortestPath(0, 0, board.length - 1, board[0].length - 1, board);
        System.out.println(ans.len + " -> " + ans.str);
    }

    static int[][] dir = { { 0, 1 }, { -1, 1 }, { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };
    static String[] dirN = { "R", "E", "U", "N", "L", "W", "D", "S" };

    public static int floodFill_Heigth(int sr, int sc, int er, int ec, int[][] board) {
        if (sr == er && sc == ec) {
            return 0;
        }
        board[sr][sc] = 2;
        int minAns = 0;
        for (int d = 0; d < dir.length; d++) {
            int nr = sr + dir[d][0];
            int nc = sc + dir[d][1];
            if (nr >= 0 && nc >= 0 && nr < board.length && nc < board[0].length && board[nr][nc] == 0) {
                int recAns = floodFill_Heigth(nr, nc, er, ec, board);
                minAns = Math.max(minAns, recAns + 1);
            }
        }
        board[sr][sc] = 0;
        return minAns;
    }

    static class pair {
        int len = 0;
        String str = "";

        pair(int len, String str) {
            this.len = len;
            this.str = str;
        }
    }

    public static pair floodFill_LongestPath(int sr, int sc, int er, int ec, int[][] board) {
        if (sr == er && sc == ec) {
            return new pair(0, "");
        }
        board[sr][sc] = 2;
        pair myAns = new pair(0, "");
        for (int d = 0; d < dir.length; d++) {
            int nr = sr + dir[d][0];
            int nc = sc + dir[d][1];
            if (nr >= 0 && nc >= 0 && nr < board.length && nc < board[0].length && board[nr][nc] == 0) {
                pair recAns = floodFill_LongestPath(nr, nc, er, ec, board);
                if (recAns.len + 1 > myAns.len) {
                    myAns.len = recAns.len + 1;
                    myAns.str = recAns.str + dirN[d] + " ";
                }
            }
        }
        board[sr][sc] = 0;
        return myAns;
    }

    public static pair floodFill_SortestPath(int sr, int sc, int er, int ec, int[][] board) {
        if (sr == er && sc == ec) {
            return new pair(0, "");
        }
        board[sr][sc] = 2;
        pair myAns = new pair((int) 1e7, "");
        for (int d = 0; d < dir.length; d++) {
            int nr = sr + dir[d][0];
            int nc = sc + dir[d][1];
            if (nr >= 0 && nc >= 0 && nr < board.length && nc < board[0].length && board[nr][nc] == 0) {
                pair recAns = floodFill_SortestPath(nr, nc, er, ec, board);
                if (recAns.len + 1 < myAns.len) {
                    myAns.len = recAns.len + 1;
                    myAns.str = recAns.str + dirN[d] + " ";
                }
            }
        }
        board[sr][sc] = 0;
        return myAns;
    }

    // CoinTrees.====================================================

    public static int coinChangePermuINFI_01(int[] arr, int tar, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < arr.length; i++) {
            if (tar - arr[i] >= 0)
                count += coinChangePermuINFI_01(arr, tar - arr[i], ans + arr[i] + " ");
        }

        return count;
    }

    public static int coinChangePermu_01(int[] arr, int tar, boolean[] vis, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < arr.length; i++) {
            if (!vis[i] && tar - arr[i] >= 0) {
                vis[i] = true;
                count += coinChangePermu_01(arr, tar - arr[i], vis, ans + i + " ");
                vis[i] = false;
            }
        }
        return count;
    }

    public static int coinChangeCombinationINFI_01(int[] arr, int idx, int tar, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        for (int i = idx; i < arr.length; i++) {
            if (tar - arr[i] >= 0)
                count += coinChangeCombinationINFI_01(arr, i, tar - arr[i], ans + arr[i] + " ");
        }

        return count;
    }

    public static int coinChangeCombination_01(int[] arr, int idx, int tar, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        for (int i = idx; i < arr.length; i++) {
            if (tar - arr[i] >= 0)
                count += coinChangeCombination_01(arr, i + 1, tar - arr[i], ans + arr[i] + " ");
        }

        return count;
    }

    //using a subequence type calls structure for combination because a combination can be reduce in a subsequence tree;
    public static int coinChangeCombination_02(int[] arr, int idx, int tar, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }

            return 0;
        }

        int count = 0;
        if (tar - arr[idx] >= 0)
            count += coinChangeCombination_02(arr, idx + 1, tar - arr[idx], ans + arr[idx] + " ");
        count += coinChangeCombination_02(arr, idx + 1, tar, ans);

        return count;
    }

    public static int coinChangeCombinationINFI_02(int[] arr, int idx, int tar, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }

            return 0;
        }

        int count = 0;
        if (tar - arr[idx] >= 0)
            count += coinChangeCombinationINFI_02(arr, idx, tar - arr[idx], ans + arr[idx] + " ");
        count += coinChangeCombinationINFI_02(arr, idx + 1, tar, ans);

        return count;
    }

    public static int coinChangePermuINFI_02(int[] arr, int idx, int tar, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }

            return 0;
        }

        int count = 0;
        if (tar - arr[idx] >= 0)
            count += coinChangePermuINFI_02(arr, 0, tar - arr[idx], ans + arr[idx] + " ");
        count += coinChangePermuINFI_02(arr, idx + 1, tar, ans);

        return count;
    }

    public static int coinChangePermu_02(int[] arr, boolean[] vis, int idx, int tar, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }

            return 0;
        }

        int count = 0;
        if (tar - arr[idx] >= 0 && !vis[idx]) {
            vis[idx] = true;
            count += coinChangePermu_02(arr, vis, 0, tar - arr[idx], ans + arr[idx] + " ");
            vis[idx] = false;
        }

        count += coinChangePermu_02(arr, vis, idx + 1, tar, ans);

        return count;
    }

}