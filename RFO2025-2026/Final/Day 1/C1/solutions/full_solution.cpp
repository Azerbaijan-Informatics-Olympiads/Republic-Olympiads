#pragma GCC optimize("O3,unroll-loops")
#include <iostream>

using namespace std;

const int MAXN = 200005;

// Flat, globally allocated arrays for the Segment Tree
int a[MAXN];
int ans[4 * MAXN][10];
int first_val[4 * MAXN];
int last_val[4 * MAXN];
int lz[4 * MAXN];
int n, q, k;

// Apply a lazy shift to a node
void apply(int node, int v) {
    if (v == 0) return;
    
    // Rotate the answers array correctly: new_ans[i] = old_ans[i + v]
    int temp[10];
    for (int i = 0; i < k; ++i) {
        int old_shift = i + v;
        if (old_shift >= k) old_shift -= k;
        temp[i] = ans[node][old_shift];
    }
    for (int i = 0; i < k; ++i) {
        ans[node][i] = temp[i];
    }
    
    // Update boundary values and lazy tag
    first_val[node] += v; if (first_val[node] >= k) first_val[node] -= k;
    last_val[node] += v;  if (last_val[node] >= k) last_val[node] -= k;
    lz[node] += v;        if (lz[node] >= k) lz[node] -= k;
}

// Push lazy tag down to children
void push(int node) {
    if (lz[node]) {
        apply(node << 1, lz[node]);
        apply(node << 1 | 1, lz[node]);
        lz[node] = 0;
    }
}

// Merge children into parent
void pull(int node) {
    int lc = node << 1;
    int rc = lc | 1;
    
    first_val[node] = first_val[lc];
    last_val[node] = last_val[rc];
    
    int l_last = last_val[lc];
    int r_first = first_val[rc];
    
    for (int s = 0; s < k; ++s) {
        ans[node][s] = ans[lc][s] + ans[rc][s];
        
        // Check boundary condition without % operator
        int v1 = l_last + s; if (v1 >= k) v1 -= k;
        int v2 = r_first + s; if (v2 >= k) v2 -= k;
        
        if (v1 < v2) {
            ans[node][s]++;
        }
    }
}

void build(int node, int l, int r) {
    lz[node] = 0;
    if (l == r) {
        first_val[node] = last_val[node] = a[l];
        for (int s = 0; s < k; ++s) ans[node][s] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    pull(node);
}

void update(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        apply(node, 1);
        return;
    }
    push(node);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(node << 1, l, mid, ql, qr);
    if (qr > mid)  update(node << 1 | 1, mid + 1, r, ql, qr);
    pull(node);
}

// Lightweight struct to return multiple values from the query
struct QRes {
    int res;
    int fv;
    int lv;
};

QRes query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return {ans[node][0], first_val[node], last_val[node]};
    }
    push(node);
    int mid = (l + r) >> 1;
    
    if (qr <= mid) return query(node << 1, l, mid, ql, qr);
    if (ql > mid)  return query(node << 1 | 1, mid + 1, r, ql, qr);
    
    QRes left_res = query(node << 1, l, mid, ql, qr);
    QRes right_res = query(node << 1 | 1, mid + 1, r, ql, qr);
    
    int total = left_res.res + right_res.res;
    if (left_res.lv < right_res.fv) {
        total++;
    }
    return {total, left_res.fv, right_res.lv};
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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
                cout << query(1, 1, n, l, r).res << "\n";
            }
        }
    }

    return 0;
}