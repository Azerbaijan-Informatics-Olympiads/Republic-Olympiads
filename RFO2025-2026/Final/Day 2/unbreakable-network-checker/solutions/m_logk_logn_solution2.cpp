#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MAXK = 250005;

vector<pair<int, int>> seg_tree[4 * MAXK];

struct DSU {
    vector<int> parent;
    vector<int> sz;
    int components;
    vector<int> history;

    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1);
    }

    void init(int n) {
        components = n;
        history.clear();
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int find(int i) {
        while (i != parent[i]) {
            i = parent[i];
        }
        return i;
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
            components--;
            
            history.push_back(root_j);
            return true;
        }
        return false;
    }

    void rollback() {
        int child = history.back();
        history.pop_back();
        
        int root = parent[child];
        parent[child] = child;
        sz[root] -= sz[child]; 
        components++;
    }
} dsu(1);

void add_to_tree(int node, int l, int r, int ql, int qr, int u, int v) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        seg_tree[node].push_back({u, v});
        return;
    }
    int mid = (l + r) / 2;
    add_to_tree(2 * node, l, mid, ql, qr, u, v);
    add_to_tree(2 * node + 1, mid + 1, r, ql, qr, u, v);
}

void solve_seg_tree(int node, int l, int r) {
    int unions_made = 0;
    
    for (auto& edge : seg_tree[node]) {
        if (dsu.unite(edge.first, edge.second)) {
            unions_made++;
        }
    }

    if (l == r) {
        if (dsu.components == 1) {
            cout << "1";
        } else {
            cout << "0";
        }
    } else {
        int mid = (l + r) / 2;
        solve_seg_tree(2 * node, l, mid);
        solve_seg_tree(2 * node + 1, mid + 1, r);
    }

    for (int i = 0; i < unions_made; ++i) {
        dsu.rollback();
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    if (dsu.parent.size() <= n) {
        dsu.parent.resize(n + 1);
        dsu.sz.resize(n + 1);
    }
    dsu.init(n);

    for (int i = 1; i <= 4 * k; ++i) {
        seg_tree[i].clear();
    }

    for (int i = 0; i < m; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        
        if (l > 1) {
            add_to_tree(1, 1, k, 1, l - 1, u, v);
        }
        if (l < k) {
            add_to_tree(1, 1, k, l + 1, k, u, v);
        }
    }
    solve_seg_tree(1, 1, k);
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}