
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
}