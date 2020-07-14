import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

import org.graalvm.compiler.phases.common.RemoveValueProxyPhase;

public class l001 {

    public static void main(String[] args) {
        solve();
    }

    public static class Node {
        int data;
        Node left = null; // Node* left=nullptr;
        Node right = null; // Node* right=nullptr;

        Node(int data) {
            this.data = data;
        }

        Node() {
        }
    }

    static int idx = 0;

    public static Node constructTree(int[] arr) {
        if (idx >= arr.length || arr[idx] == -1) {
            idx++;
            return null;
        }

        Node node = new Node(arr[idx++]); // Node* node=new Node(arr[idx++]);
        node.left = constructTree(arr);
        node.right = constructTree(arr);

        return node;
    }

    public static void display(Node node) {
        if (node == null)
            return;

        String str = "";
        str += ((node.left != null) ? node.left.data : ".");
        str += " <- " + node.data + " -> ";
        str += ((node.right != null) ? node.right.data : ".");
        System.out.println(str);

        display(node.left);
        display(node.right);

    }

    // Basic.================================================================

    public static int size(Node node) {
        if (node == null)
            return 0;
        return (size(node.left) + size(node.right) + 1);
    }

    public static int height(Node node) {
        if (node == null)
            return -1; // return -1, height w.r.t edge, return 0, height w.r.t node.
        return Math.max(height(node.left), height(node.right)) + 1;
    }

    public static int Maximum(Node node) {
        if (node == null)
            return (int) -1e8; // java: Integer.MIN_VALUE, c++: INT_MIN;
        return Math.max(Math.max(Maximum(node.left), Maximum(node.right)), node.data); // max(leftSubtree,rightSubtree,myself);
    }

    public static int Minimum(Node node) {
        if (node == null)
            return (int) 1e8; // java: Integer.MAX_VALUE, c++: INT_MAX;
        return Math.min(Math.min(Minimum(node.left), Minimum(node.right)), node.data);
    }

    public static int Minimum_02(Node node) {
        int min_ = node.data;

        if (node.left != null)
            min_ = Math.min(min_, Minimum_02(node.left));
        if (node.right != null)
            min_ = Math.min(min_, Minimum_02(node.right));

        return min_;
    }

    public static boolean find(Node node, int data) {
        if (node == null)
            return false;

        if (node.data == data)
            return true;
        return find(node.left, data) || find(node.right, data);
    }

    // Traversal.============================================================

    public static void preOrder(Node node) {
        if (node == null)
            return;

        System.out.print(node.data + " ");
        preOrder(node.left);
        preOrder(node.right);
    }

    public static void inOrder(Node node) {
        if (node == null)
            return;

        inOrder(node.left);
        System.out.print(node.data + " ");
        inOrder(node.right);
    }

    public static void postOrder(Node node) {
        if (node == null)
            return;

        postOrder(node.left);
        postOrder(node.right);
        System.out.print(node.data + " ");
    }

    // node to root path ==========================================================

    public static boolean rootToNodePath_(Node root, int data, ArrayList<Node> path) {
        if (root == null)
            return false;
        if (root.data == data) {
            path.add(root);
            return true;
        }

        boolean res = rootToNodePath_(root.left, data, path) || rootToNodePath_(root.right, data, path);
        if (res)
            path.add(root);
        return res;
    }

    public static ArrayList<Node> nodeToRoot_path_02(Node node, int val) {
        if (node == null)
            return null;

        if (node.data == val) {
            ArrayList<Node> base = new ArrayList<>();
            base.add(node);
            return base;
        }

        ArrayList<Node> left = nodeToRoot_path_02(node.left, val);

        if (left != null) {
            left.add(node);
            return left;
        }
        ArrayList<Node> right = nodeToRoot_path_02(node.right, val);

        if (right != null) {
            right.add(node);
            return right;
        }

        return null;
    }

    // LCA ========================================================
    public Node lowestCommonAncestor(Node root, int p, int q) {
        ArrayList<Node> path1 = new ArrayList<>();
        ArrayList<Node> path2 = new ArrayList<>();

        rootToNodePath_(root, p, path1);
        rootToNodePath_(root, q, path2);

        Node prev = null;
        int i = path1.size() - 1;
        int j = path2.size() - 1;

        while (i >= 0 && j >= 0) {
            if (path1.get(i).data != path2.get(j).data)
                break;

            prev = path1.get(i);
            i--;
            j--;
        }

        return prev;
    }

    static Node LCANode = null;

    public static boolean lowestCommonAncestor_02(Node root, int p, int q) {
        if (root == null)
            return false;

        boolean selfDone = false;
        if (root.data == p || root.data == q) {
            selfDone = true;
        }

        boolean leftDone = lowestCommonAncestor_02(root.left, p, q);
        if (LCANode != null)
            return true;

        boolean rightDone = lowestCommonAncestor_02(root.right, p, q);
        if (LCANode != null)
            return true;

        if ((selfDone && leftDone) || (selfDone && rightDone) || (leftDone && rightDone))
            LCANode = root;

        return selfDone || leftDone || rightDone;
    }

    // all Nodes k down form a given Node in a BT
    // =========================================
    public static void kDown(Node root, int level, Node blockNode) {
        if (root == null || root == blockNode)
            return;

        if (level == 0) {
            System.out.print(root.data + " ");
            return;
        }

        kDown(root.left, level - 1, blockNode);
        kDown(root.right, level - 1, blockNode);

    }

    public static void allNodeKAway(Node root, int target, int K) {
        ArrayList<Node> path = new ArrayList<>();
        rootToNodePath_(root, target, path);

        Node blockNode = null;
        for (int i = 0; i < path.size(); i++) {
            if (K - i < 0)
                break;
            kDown(path.get(i), K - i, blockNode);
            blockNode = path.get(i);
        }
    }

    public static int allNodeKAway_02_(Node root, int target, int K) {
        if (root == null)
            return -1;

        if (root.data == target) {
            kDown(root, K, null);
            return 1;
        }

        int leftdistance = allNodeKAway_02_(root.left, target, K);
        if (leftdistance != -1) {
            if (K - leftdistance >= 0)
                kDown(root, K - leftdistance, root.left);
            return leftdistance + 1;
        }

        int rightdistance = allNodeKAway_02_(root.right, target, K);
        if (rightdistance != -1) {
            if (K - rightdistance >= 0)
                kDown(root, K - rightdistance, root.right);
            return rightdistance + 1;
        }

        return -1;

    }

    public static void kDown(Node root, int level) {
        if (root == null)
            return;

        if (level == 0) {
            System.out.print(root.data + " ");
            return;
        }

        kDown(root.left, level - 1);
        kDown(root.right, level - 1);

    }

    // Diameter of a Tree : total no of nodes b/w the two end nodes of the longest
    // path in the tree.
    public static int diameter_01(Node root) {
        if (root == null) // O(n2) soltuion becuase needed lh,rh for every root;
            return 0;
        int lh = height(root.left);
        int rh = height(root.right);
        int ld = diameter_01(root.left);
        int rd = diameter_01(root.right);
        int myDia = lh + rh + 2;
        return Math.max(Math.max(ld, rd), myDia);
    }

    public static class diaPair {

        int dia = 0;
        int hei = 0;

        diaPair(int dia, int hei) {
            this.dia = dia;
            this.hei = hei;
        }
    }

    public static diaPair diameter_02(Node node) {
        if (node == null)
            return new diaPair(0, -1);

        diaPair lr = diameter_02(node.left);
        diaPair rr = diameter_02(node.right);

        diaPair myRes = new diaPair(0, -1);
        myRes.dia = Math.max(Math.max(lr.dia, rr.dia), lr.hei + rr.hei + 2);
        myRes.hei = Math.max(lr.hei, rr.hei) + 1;
        return myRes;
    }

    public static int diameter = 0;

    public static int diameter_03(Node node) {
        if (node == null)
            return -1;

        int lh = diameter_03(node.left);
        int rh = diameter_03(node.right);

        diameter = Math.max(diameter, lh + rh + 2);
        return Math.max(lh, rh) + 1;
    }

    public static class pairVO {
        Node node;
        int vl;

        pairVO(Node node, int vl) {
            this.node = node;
            this.vl = vl;
        }
    }

    // View=====================================================================

    public static void leftView(Node node) {
        LinkedList<Node> que = new LinkedList<>(); // addLast and removeFirst.
        que.addLast(node);
        while (que.size() != 0) {
            int size = que.size();
            System.out.print(que.getFirst().data + " ");
            while (size-- > 0) {
                Node rnode = que.removeFirst();
                if (rnode.left != null)
                    que.addLast(rnode.left);
                if (rnode.right != null)
                    que.addLast(rnode.right);
            }
        }
        System.out.println();
    }

    public static void rightView(Node node) {
        LinkedList<Node> que = new LinkedList<>(); // addLast and removeFirst.
        que.addLast(node);
        while (que.size() != 0) {
            int size = que.size();
            Node prev = null;
            while (size-- > 0) {
                Node rnode = que.removeFirst();
                if (rnode.left != null)
                    que.addLast(rnode.left);
                if (rnode.right != null)
                    que.addLast(rnode.right);
                prev = rnode;
            }
            System.out.print(prev.data + " ");
        }
        System.out.println();
    }

    static int leftMinValue = 0;
    static int rightMaxValue = 0;

    public static void width(Node node, int lev) {
        if (node == null)
            return;

        leftMinValue = Math.min(leftMinValue, lev);
        rightMaxValue = Math.max(rightMaxValue, lev);

        width(node.left, lev - 1);
        width(node.right, lev + 1);
    }

    public static class pairVO {
        Node node; // actual Node
        int vl = 0; // vertical Level

        public pairVO(Node node, int vl) {
            this.node = node;
            this.vl = vl;
        }
    }

    public static void verticalOrder(Node node) {
        width(node, 0);
        int n = rightMaxValue - leftMinValue + 1;
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>(); // vector<vector<int>> (n,vector<int>());
        for (int i = 0; i < n; i++)
            ans.add(new ArrayList<>());

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node, -leftMinValue));

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rpair = que.removeFirst();
                ans.get(rpair.vl).add(rpair.node.data);
                if (rpair.node.left != null)
                    que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pairVO(rpair.node.right, rpair.vl + 1));
            }
        }

        for (ArrayList<Integer> ar : ans)
            System.out.println(ar);
        System.out.println();
    }

    public static void verticalOrderSum(Node node) {
        width(node, 0);
        int[] ans = new int[rightMaxValue - leftMinValue + 1];

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node, -leftMinValue));

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rpair = que.removeFirst();
                ans[rpair.vl] += rpair.node.data;
                if (rpair.node.left != null)
                    que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pairVO(rpair.node.right, rpair.vl + 1));
            }
        }

        for (int ele : ans)
            System.out.println(ele);
        System.out.println();
    }

    public static void bottomView(Node node) {
        width(node, 0);
        int[] ans = new int[rightMaxValue - leftMinValue + 1];

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node, -leftMinValue));

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rpair = que.removeFirst();
                ans[rpair.vl] = rpair.node.data;
                if (rpair.node.left != null)
                    que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pairVO(rpair.node.right, rpair.vl + 1));
            }
        }

        for (int ele : ans)
            System.out.println(ele);
        System.out.println();
    }

    public static void topView(Node node) {
        width(node, 0);
        int[] ans = new int[rightMaxValue - leftMinValue + 1];
        Arrays.fill(ans, (int) -1e8);

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node, -leftMinValue));

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rpair = que.removeFirst();

                if (ans[rpair.vl] == (int) -1e8)
                    ans[rpair.vl] = rpair.node.data;

                if (rpair.node.left != null)
                    que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pairVO(rpair.node.right, rpair.vl + 1));
            }
        }

        for (int ele : ans)
            System.out.println(ele);
        System.out.println();
    }

    static int leftDMinValue = 0;

    public static void widthDiagonal(Node node, int lev) {
        if (node == null)
            return;

        leftMinValue = Math.min(leftMinValue, lev);

        width(node.left, lev - 1);
        width(node.right, lev + 0);
    }

    public static void diagonalOrder(Node node) {
        widthDiagonal(node, 0);
        int n = -leftDMinValue + 1;
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>(); // vector<vector<int>> (n,vector<int>());
        for (int i = 0; i < n; i++)
            ans.add(new ArrayList<>());

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node, -leftMinValue));

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rpair = que.removeFirst();
                ans.get(rpair.vl).add(rpair.node.data);
                if (rpair.node.left != null)
                    que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pairVO(rpair.node.right, rpair.vl + 0));
            }
        }

        for (ArrayList<Integer> ar : ans)
            System.out.println(ar);
        System.out.println();
    }

    public static void diagonalSum(Node node) {
        widthDiagonal(node, 0);
        int n = -leftDMinValue + 1;
        int[] ans = new int[n];

        LinkedList<pairVO> que = new LinkedList<>();
        que.addLast(new pairVO(node, -leftMinValue));

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                pairVO rpair = que.removeFirst();
                ans[rpair.vl] += rpair.node.data;
                if (rpair.node.left != null)
                    que.addLast(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pairVO(rpair.node.right, rpair.vl + 0));
            }
        }

        for (int ele : ans)
            System.out.println(ele);
        System.out.println();
    }

    static Node DLLhead = null;
    static Node DLLprev = null;

    public static void DLL(Node node) {
        if (node == null)
            return;

        DLL(node.left);

        if (DLLhead == null) {
            DLLhead = node;
        } else {
            DLLprev.right = node;
            node.left = DLLprev;
        }
        DLLprev = node;

        DLL(node.right);

    }

    public static class allSolution {
        int height = 0;
        int size = 0;
        boolean find = false;

        Node pred = null;
        Node succ = null;
        Node prev = null;
    }

    public static void allSol(Node node, int data, int level, allSolution pair) {
        if (node == null)
            return;
        pair.size++;
        pair.height = Math.max(pair.height, level);
        pair.find = pair.find || node.data == data;

        if (node.data == data && pair.pred == null)
            pair.pred = prev;
        if (pair.prev != null && pair.prev.data == data && pair.succ == null)
            pair.succ = node;
        pair.prev = node;

        allSol(node.left, data, level + 1, pair);
        allSol(node.right, data, level + 1, pair);
    }

    // Iterative travesal of the tree using a class
    // ==================================

    // =================================================================

    public static class tpair { // traversalPair
        Node node = null;
        boolean selfDone = false;
        boolean leftDone = false;
        boolean rightDone = false;

        tpair(Node node, boolean selfDone, boolean leftDone, boolean rightDone) {
            this.node = node;
            this.leftDone = leftDone;
            this.selfDone = selfDone;
            this.rightDone = rightDone;
        }
    }

    public static void ItrTraversalOfTree(Node node) {
        Stack<tpair> st = new Stack<>();
        st.push(new tpair(node, false, false, false));

        while (st.size() != 0) {
            if (st.peek().selfDone == false) {
                st.peek().selfDone = true;
                System.out.print(st.peek().node.data + " ");
            } else if (st.peek().leftDone == false) {
                st.peek().leftDone = true;
                if (st.peek().node.left != null) {
                    st.push(new tpair(st.peek().node.left, false, false, false));
                }
            } else if (st.peek().rightDone == false) {
                st.peek().rightDone = true;
                if (st.peek().node.right != null) {
                    st.push(new tpair(st.peek().node.right, false, false, false));
                }
            } else {
                st.pop();
            }
        }
    }

    public static class tpair_ { // traversalPair
        Node node = null;
        boolean selfDone = false;
        boolean leftDone = false;
        boolean rightDone = false;

        int ld = -1;
        int rd = -1;
        int sd = -1;
        boolean isleft = false;

        tpair_(Node node, boolean selfDone, boolean leftDone, boolean rightDone, boolean isleft) {
            this.node = node;
            this.leftDone = leftDone;
            this.selfDone = selfDone;
            this.rightDone = rightDone;
            this.isleft = isleft;
        }
    }

    public static void ItrHeightOfTree(Node node) {
        Stack<tpair_> st = new Stack<>();
        st.push(new tpair_(node, false, false, false, false));

        tpair_ rpair = null;
        while (st.size() != 0) {
            if (st.peek().leftDone == false) {
                st.peek().leftDone = true;
                if (st.peek().node.left != null) {
                    st.push(new tpair_(st.peek().node.left, false, false, false, true));
                }
            } else if (st.peek().rightDone == false) {
                st.peek().rightDone = true;
                if (st.peek().node.right != null) {
                    st.push(new tpair_(st.peek().node.right, false, false, false, false));
                }
            } else if (st.peek().selfDone == false) {
                st.peek().selfDone = true;
                st.peek().sd = Math.max(st.peek().ld, st.peek().rd) + 1;
            } else {
                rpair = st.pop();
                if (st.size() != 0) {
                    if (st.peek().isleft)
                        st.peek().ld = rpair.sd;
                    else
                        st.peek().rd = rpair.sd;
                }
            }
        }

        System.out.println(rpair.sd);
    }

    public static Node rightMost_of_LeftNode(Node lnode, Node curr) {
        while (lnode.right != null && lnode.right != curr) {
            lnode = lnode.right;
        }
        return lnode;
    }

    public static void morrisInOrder(Node node) {
        Node curr = node;
        while (curr != null) {
            if (curr.left == null) {
                System.out.print(curr.data + " ");
                curr = curr.right;
            } else {
                Node leftNode = curr.left;
                Node rightMost = rightMost_of_LeftNode(leftNode, curr);
                if (rightMost.right == null) { // thread create
                    rightMost.right = curr;
                    curr = curr.left;
                } else { // thread break
                    rightMost.right = null;
                    System.out.print(curr.data + " ");
                    curr = curr.right;
                }
            }
        }
        System.out.println();
    }

    public static void morrisPreOrder(Node node) {
        Node curr = node;
        while (curr != null) {
            if (curr.left == null) {
                System.out.print(curr.data + " ");
                curr = curr.right;
            } else {
                Node leftNode = curr.left;
                Node rightMost = rightMost_of_LeftNode(leftNode, curr);
                if (rightMost.right == null) { // thread create
                    rightMost.right = curr;
                    System.out.print(curr.data + " ");
                    curr = curr.left;
                } else { // thread break
                    rightMost.right = null;
                    curr = curr.right;
                }
            }
        }
        System.out.println();
    }

    // psi = preStartIndex, pei=preEndIndex, isi=inStartIndex, iei=inEndIndex
    public static Node ConstructFromPreAndIn(int[] pre, int psi, int pei, int[] in, int isi, int iei) {
        if (psi > pei || isi > iei)
            return null;

        Node node = new Node(pre[psi]);

        int idx = isi;
        while (in[idx] != pre[psi]) {
            idx++;
        }
        int tnel = idx - isi; // total no of elements between isi and idx

        node.left = ConstructFromPreAndIn(pre, psi + 1, psi + tnel, in, isi, idx - 1);
        node.right = ConstructFromPreAndIn(pre, psi + tnel + 1, pei, in, idx + 1, iei);

        return node;
    }

    public static Node ConstructFromPreAndIn(int[] pre, int[] in) {
        return ConstructFromPreAndIn(pre, 0, pre.length - 1, in, 0, in.length - 1);
    }

    // psi = postStartIndex, pei=postEndIndex, isi=inStartIndex, iei=inEndIndex
    public static Node ConstructFromPostAndIn(int[] post, int psi, int pei, int[] in, int isi, int iei) {
        if (psi > pei || isi > iei)
            return null;

        Node node = new Node(pre[pei]);

        int idx = isi;
        while (in[idx] != pre[psi]) {
            idx++;
        }
        int tnel = idx - isi; // total no of elements between isi and idx

        node.left = ConstructFromPostAndIn(post, psi, psi + tnel - 1, in, isi, idx - 1);
        node.right = ConstructFromPostAndIn(post, psi + tnel, pei - 1, in, idx + 1, iei);

        return node;
    }

    public static Node ConstructFromPostAndIn(int[] post, int[] in) {
        return ConstructFromPostAndIn(post, 0, post.length - 1, in, 0, in.length - 1);
    }

    // psi = preStartIndex, pei=preEndIndex, ppsi=postStartIndex, ppei=postEndIndex
    public static Node ConstructFromPreAndPost(int[] post, int psi, int pei, int[] in, int ppsi, int ppei) {
        if (psi > pei || ppsi > ppei)
            return null;

        Node node = new Node(pre[psi]);

        int idx = ppsi;
        while (post[idx] != pre[psi + 1]) {
            idx++;
        }

        int tnel = idx - isi + 1; // total no of elements between isi and idx

        node.left = ConstructFromPreAndPost(post, psi + 1, psi + tnel, in, ppsi, idx);
        node.right = ConstructFromPreAndPost(post, psi + tnel + 1, pei, in, idx + 1, iei - 1);

        return node;
    }

    public static Node ConstructFromPreAndPost(int[] pre, int[] post) {
        return ConstructFromPreAndPost(pre, 0, pre.length - 1, post, 0, post.length - 1);
    }

    public static void set2(Node node) {
        DLL(node);
        while (DLLhead != null) {
            System.out.print(DLLhead.data + " ");
            DLLhead = DLLhead.right;
        }
    }

    public static void view(Node node) {
        // leftView(node);
        // rightView(node);
        // verticalOrder(node);
        // bottomView(node);
        // topView(node);

    }

    public static void levelOrder(Node node) {
        // levelOrder_00(node);
        // levelOrder_01(node);
        // levelOrder_02(node);
        // levelOrder_03(node);
    }

    public static void solve() {
        // int[] arr = { 10, 20, 40, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1,
        // -1, 70, 110, -1, -1, 120, -1,
        // -1 };

        int[] arr = { 11, 6, 4, -1, 5, -1, -1, 8, -1, 10, -1, -1, 19, 17, -1, -1, 43, 31, -1, -1, 49, -1, -1 };
        // int[] arr = { 10, 20 };
        Node root = constructTree(arr);

        display(root);
        // ArrayList<Node> ans = nodeToRoot_path(root, 60);
        // System.out.println(ans);
        view(root);
    }

}