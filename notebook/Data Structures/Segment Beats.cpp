struct JiDriverSegmentTree {
    static const int T = (1 << 20);
    static const int INF = 1e9 + 7;
    struct Node {
        int max;
        long long sum;
    } tree[T];
    int n;
    void updateFromChildren(int v) {
        tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
        tree[v].max = max(tree[2 * v].max, tree[2 * v + 1].max);
    }
    void build(int v, int l, int r, const vector<int>& inputArray) {
        if (l + 1 == r) {
            tree[v].max = tree[v].sum = inputArray[l];
        } else {
            int mid = (r + l) / 2;
            build(2 * v, l, mid, inputArray);
            build(2 * v + 1, mid, r, inputArray);
            updateFromChildren(v);
        }
    }
    void build(const vector<int>& inputArray) {
        n = inputArray.size();
        build(1, 0, n, inputArray);
    }
    void updateModEq(int v, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql || tree[v].max < val) return;
        if (l + 1 == r) {
            tree[v].max %= val;
            tree[v].sum = tree[v].max;
            return;
        }
        int mid = (r + l) / 2;
        updateModEq(2 * v, l, mid, ql, qr, val);
        updateModEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }
    void updateModEq(int ql, int qr, int val) {
        updateModEq(1, 0, n, ql, qr, val);
    }
    void updateEq(int v, int l, int r, int qi, int val) {
        if (l + 1 == r) {
            tree[v].max = tree[v].sum = val;
            return;
        }
        int mid = (l + r) / 2;
        if (qi < mid) {
            updateEq(2 * v, l, mid, qi, val);
        } else {
            updateEq(2 * v + 1, mid, r, qi, val);
        }
        updateFromChildren(v);
    }
    void updateEq(int qi, int val) {
        updateEq(1, 0, n, qi, val);
    }
    long long findSum(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[v].sum;
        }
        int mid = (r + l) / 2;
        return findSum(2 * v, l, mid, ql, qr) + findSum(2 * v + 1, mid, r, ql, qr);
    }
    long long findSum(int ql, int qr) {
        return findSum(1, 0, n, ql, qr);
    }
} segTree;
