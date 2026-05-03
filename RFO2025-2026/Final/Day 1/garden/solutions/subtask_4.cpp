#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
int n, q, k;
int a[MAXN];

struct Node {
    int ans01;       // Count of (0, 1) pairs
    int ans10;       // Count of (1, 0) pairs
    int first_val;   // Value of the first element in the range
    int last_val;    // Value of the last element in the range
    bool lazy;       // Pending flip
    bool is_null;

    Node() {
        ans01 = ans10 = 0;
        first_val = last_val = 0;
        lazy = false;
        is_null = false;
    }
};

Node tree[4 * MAXN];

Node merge_nodes(const Node& L, const Node& R) {
    if (L.is_null) return R;
    if (R.is_null) return L;

    Node res;
    // Base pairs from children
    res.ans01 = L.ans01 + R.ans01;
    res.ans10 = L.ans10 + R.ans10;
    
    // Add the boundary pair if it matches
    if (L.last_val == 0 && R.first_val == 1) res.ans01++;
    if (L.last_val == 1 && R.first_val == 0) res.ans10++;
    
    res.first_val = L.first_val;
    res.last_val = R.last_val;
    res.is_null = false;
    res.lazy = false;
    return res;
}

void apply(int node) {
    if (tree[node].is_null) return;
    // A flip swaps the counts of (0,1) and (1,0)
    swap(tree[node].ans01, tree[node].ans10);
    tree[node].first_val ^= 1;
    tree[node].last_val ^= 1;
    tree[node].lazy ^= 1;
}

void push_down(int node) {
    if (tree[node].lazy) {
        apply(2 * node);
        apply(2 * node + 1);
        tree[node].lazy = false;
    }
}

void build(int node, int l, int r) {
    tree[node].is_null = false;
    tree[node].lazy = false;
    if (l == r) {
        tree[node].ans01 = 0;
        tree[node].ans10 = 0;
        tree[node].first_val = a[l];
        tree[node].last_val = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        apply(node);
        return;
    }
    push_down(node);
    int mid = l + (r - l) / 2;
    update(2 * node, l, mid, ql, qr);
    update(2 * node + 1, mid + 1, r, ql, qr);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        Node null_node;
        null_node.is_null = true;
        return null_node;
    }
    if (ql <= l && r <= qr) {
        return tree[node];
    }
    push_down(node);
    int mid = l + (r - l) / 2;
    return merge_nodes(query(2 * node, l, mid, ql, qr), 
                       query(2 * node + 1, mid + 1, r, ql, qr));
}

int main() {
    if (!(cin >> n >> q >> k)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    build(1, 1, n);

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            update(1, 1, n, l, r);
        } else {
            if (l == r) {
                cout << 0 << "\n";
            } else {
                Node res = query(1, 1, n, l, r);
                cout << res.ans01 << "\n";
            }
        }
    }

    return 0;
}