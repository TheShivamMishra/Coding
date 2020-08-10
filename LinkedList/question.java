public class ListNode {

    public class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }

    }

    // Leetcode 876: getMid
    public ListNode getMidNode(ListNode node) {
        if (node == null || node.next == null)
            return node;
        ListNode slow = node;
        ListNode fast = node;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Leetcode 206 : reverseOfLL
    public ListNode reverseList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode forw = curr.next;

            curr.next = prev;
            prev = curr;
            curr = forw;
        }

        return prev;
    }

    // Class Question: reverse Data.
    public void reverseListData(ListNode head) {
        if (head == null || head.next == null)
            return;

        ListNode curr = head;
        ListNode midNode = getMidNode(curr);

        ListNode nhead = midNode.next;
        midNode.next = null;

        nhead = reverseList(nhead);
        ListNode curr1 = nhead;
        while (curr != null && curr1 != null) {

            int temp = curr.val;
            curr.val = curr1.val;
            curr1.val = temp;

            curr = curr.next;
            curr1 = curr1.next;
        }

        nhead = reverseList(nhead);
        midNode.next = nhead;
    }

    // IN this the middel node is by index wise;
    public ListNode getMidNode2(ListNode node) {
        if (node == null || node.next == null)
            return node;
        ListNode slow = node;
        ListNode fast = node;

        while (fast != null && fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Leetcode 234: palindrome

    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null)
            return true;

        ListNode curr = head;
        ListNode midNode = getMidNode2(curr);

        ListNode nhead = midNode.next;
        midNode.next = null;

        nhead = reverseList(nhead);
        ListNode curr1 = nhead;
        while (curr != null && curr1 != null) {
            if (curr.val != curr1.val)
                return false;

            curr = curr.next;
            curr1 = curr1.next;
        }

        nhead = reverseList(nhead);
        midNode.next = nhead;

        return true;
    }

    public ListNode removeNthFromEnd(ListNode head, int n) {
        if (n == 0 || head == null)
            return head;
        if (n == 1 && head.next == null)
            return null;

        ListNode slow = head, fast = head;
        while (n-- > 0) {
            fast = fast.next;
            // if(fast==null && n > 0) return null; // if n is greater than one;
        }

        if (fast == null)
            return slow.next;

        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }

        ListNode forw = slow.next;
        slow.next = slow.next.next;
        forw.next = null;
        return head;
    }

    public void reorderList(ListNode head) {
        if (head == null || head.next == null)
            return;

        ListNode curr1 = head;
        ListNode midNode = getMidNode2(curr1);

        ListNode nhead = midNode.next;
        midNode.next = null;

        nhead = reverseList(nhead);
        ListNode curr2 = nhead;
        while (curr1 != null && curr2 != null) {
            ListNode forw1 = curr1.next;
            ListNode forw2 = curr2.next;

            curr1.next = curr2;
            curr2.next = forw1;

            curr1 = forw1;
            curr2 = forw2;
        }
    }

    // Leetcode 21: merge Two LL.

    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null)
            return l1 == null ? l2 : l1;

        ListNode head = new ListNode(-1);
        ListNode prev = head;

        ListNode curr1 = l1;
        ListNode curr2 = l2;

        while (curr1 != null && curr2 != null) {
            if (curr1.val <= curr2.val) {
                prev.next = curr1;
                prev = curr1;
                curr1 = curr1.next;
            } else {
                prev.next = curr2;
                prev = curr2;
                curr2 = curr2.next;
            }
        }

        if (curr1 != null) {
            prev.next = curr1;
        }

        if (curr2 != null) {
            prev.next = curr2;
        }

        return head.next;
    }
     
    ListNode mergeTwoLists(Node* l1, Node* l2) {
        if (l1 == null) {
            return l2;
        } else if (l2 == null) {
            return l1;
        }

        if (l1->val <= l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }

    }

    // Leetcode 328:
    public ListNode oddEvenList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode curr1 = head;
        ListNode nhead = head.next;
        ListNode curr2 = head.next;

        while (curr1.next != null && curr2.next != null) {
            curr1.next = curr2.next;
            curr1 = curr2.next;

            curr2.next = curr1.next;
            curr2 = curr1.next;
        }

        curr1.next = nhead;
        return head;
    }

    // leetcode 41:

    public boolean hasCycle(ListNode head) {
        if (head == null || head.next == null)
            return false;

        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast)
                return true;
        }

        return false;
    }

    // Leetcode 142: detectCyclePoint
    public ListNode detectCycle(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast)
                break;
        }

        if (slow != fast)
            return head;

        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }

        return slow;
    }

    // LeetCode 25: reverse K nodes in group=====================
    ListNode oh = null;
    ListNode ot = null;

    ListNode th = null;
    ListNode tt = null;

    public void addFirstNode(ListNode node) {
        if (th == null) {
            th = node;
            tt = node;
        } else {
            node.next = th;
            th = node;
        }
    }

    public int len(ListNode node) {
        int l = 0;
        while (node != null) {
            l++;
            node = node.next;
        }
        return l;
    }

    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || head.next == null || k == 0 || k == 1)
            return head;

        int len = len(head);
        if (len < k)
            return head;

        ListNode curr = head;
        while (curr != null) {
            int tk = k;

            while (tk-- > 0) {
                ListNode forw = curr.next;

                curr.next = null;
                addFirstNode(curr);

                curr = forw;
            }

            len -= k;

            if (ot == null) {
                oh = th;
                ot = tt;
            } else {
                ot.next = th;
                ot = tt;
            }

            th = null;
            tt = null;

            if (len < k) {
                ot.next = curr;
                curr = null;
            }
        }

        return oh;
    }

    public ListNode reverseKGroup_02(ListNode head, int k) {
        if (head == null || head.next == null)
            return head;

        int len = len(head);

        if (len < k)
            return head;

        ListNode nhead = null;
        ListNode ntail = head;

        while (head != null) {
            int temp = k;
            ListNode ttail = null;
            ListNode rev = null;

            if (len >= k) {
                while (head != null && temp != 0) {
                    if (ttail == null) {
                        ttail = head;
                    }

                    ListNode forw = head.next;

                    head.next = rev;

                    rev = head;
                    head = forw;

                    temp--;
                }
                len -= k;

                if (nhead == null) {
                    nhead = rev;
                } else {
                    ntail.next = rev;
                    ntail = ttail;
                }
            } else {
                ntail.next = head;
                break;
            }

        }

        return nhead;

    }

    // Leetcode 92==============================================
    // ListNode th = null;
    // ListNode tt = null;

    // public void addFirstNode(ListNode node) {
    // if (th == null) {
    // th = node;
    // tt = node;
    // } else {
    // node.next = th;
    // th = node;
    // }
    // }

    public ListNode reverseBetween(ListNode node, int m, int n) {
        if (node.next == null || m == n)
            return node;

        int idx = 1;

        ListNode curr = node;
        ListNode prev = null;
        ListNode nhead = node;

        while (curr != null) {
            while (idx >= m && idx <= n) {
                ListNode forw = curr.next;
                curr.next = null;
                addFirstNode(curr);

                curr = forw;
                idx++;
            }

            if (tt != null) {
                tt.next = curr;
                if (prev != null)
                    prev.next = th;
                else
                    nhead = th;
                break;
            }

            prev = curr;
            curr = curr.next;
            idx++;
        }

        return nhead;
    }
}