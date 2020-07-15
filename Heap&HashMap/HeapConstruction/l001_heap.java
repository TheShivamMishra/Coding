import java.util.ArrayList;

public class l001_heap {

    public static int height(int[] arr, int idx) {
        if (idx >= arr.length)
            return -1;

        int lh = height(arr, 2 * idx + 1);
        int rh = height(arr, 2 * idx + 2);

        return Math.max(lh, rh) + 1;
    }

    public static int size(int[] arr, int idx) {
        if (idx >= arr.length)
            return 0;

        int ls = size(arr, 2 * idx + 1);
        int rs = size(arr, 2 * idx + 2);

        return ls + rs + 1;
    }

    // Heap ============================================
    public static class Heap {
        ArrayList<Integer> arr = new ArrayList<>();
        boolean isMaxHeap = false;

        public Heap(int[] list, boolena isMaxHeap) {
            this.isMaxHeap = isMaxHeap;
            int n = list.length;
            for (int ele : list)
                this.arr.add(ele);

            for (int i = n - 1; i >= 0; i--)
                downHeapify(i, n);

        }

        public Heap(int[] list) {
            for (int ele : list)
                this.arr.add(ele);

            int n = arr.size();
            for (int i = n - 1; i >= 0; i--) {// (nlogn -> o(n)) , i = (n/2) + 1
                downHeapify(i, n);
            }
        }

        public Heap() {
            arr.clear();
        }

        // Basic Util ===========================================================

        public void swap(int x, int y) {
            int ele1 = this.arr.get(x);
            int ele2 = this.arr.get(y);

            this.arr.set(x, ele2);
            this.arr.set(y, ele1);
        }

        public int compareTo(int x, int y) {
            if (isMaxHeap) {
                return this.arr.get(x) - this.arr.get(y); // this-other , default behaviour, in CPP '-' replace wit '<'
            } else {
                return this.arr.get(y) - this.arr.get(x); // other - this
            }

            // for CPP
            // if (isMaxHeap) {
            // return this.arr.get(x) > this.arr.get(y);
            // } else {
            // return this.arr.get(y) > this.arr.get(x);
            // }
        }

        public void downHeapify(int pi, int n) {

            int lci = 2 * pi + 1;
            int rci = 2 * pi + 2;
            int maxIdx = pi;

            if (lci < n && compareTo(lci, maxIdx) > 0)
                maxIdx = lci;

            if (rci < n && compareTo(rci, maxIdx) > 0)
                maxIdx = rci;

            if (maxIdx != pi) {
                swap(maxIdx, pi);
                downHeapify(maxIdx, n);
            }
        }

        public void upHeapify(int ci) {
            int pi = (ci - 1) / 2;
            int minIdx = ci;

            if (ci >= 0 && compareTo(minIdx, pi) > 0)
                minIdx = pi;

            if (minIdx != ci) {
                swap(minIdx, ci);
                upHeapify(minIdx);
            }
        }

        // User Functions =======================================================

        public boolean isEmpty() {
            return this.arr.size() == 0;
        }

        public int size() {
            return this.arr.size();
        }

        public int top() {
            if (this.arr.size() == 0)
                return -1;
            return arr.get(0);
        }

        public void add(int val) {
            this.arr.add(val);
            upHeapify(ar.size() - 1);
        }

        public void pop() {
            if (this.arr.size() == 0)
                return;
            swap(0, this.arr.size() - 1);
            downHeapify(0, this.arr.size());
        }
    }

    public static void main(String[] args) {

        int[] arr2 = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
        // System.out.println(height(arr2, 0));
        // System.out.println(size(arr2, 0));

        Heap pq = new Heap();
        for (int ele : arr2)
            pq.add(ele);

        // Heap pq = new Heap(arr2, true);
        pq.add(100);
        pq.add(25);
        while (pq.size() != 0) { // nlog(n)
            System.out.print(pq.top() + " ");
            pq.pop();
        }
    }

}