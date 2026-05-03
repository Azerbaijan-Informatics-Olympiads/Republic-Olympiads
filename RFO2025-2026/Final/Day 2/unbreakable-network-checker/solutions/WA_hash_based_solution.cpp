#include <iostream>
#include <vector>
#include <numeric>
#include <random>

using namespace std;

const int MAXN = 250005;
const int LOGN = 20;

// Global arrays to prevent reallocation overhead in multiple test cases
vector<pair<int, int>> adj[MAXN];
int up[MAXN][LOGN];
int depth[MAXN];
int tin[MAXN], tout[MAXN], timer;

int diff_count[MAXN]; 
unsigned long long diff_hash[MAXN];

unsigned long long label_hash[MAXN];
bool bad_label[MAXN];

struct DSU {
  vector<int> parent;
  vector<int> sz;

  DSU(int n) {
    parent.resize(n + 1);
    sz.assign(n + 1, 1);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
  }

  bool unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
      parent[root_j] = root_i;
      sz[root_i] += sz[root_j];
      return true;
    }
    return false;
  }
};

struct Edge {
  int u, v, label;
};

void dfs_lca(int u, int p, int d) {
  depth[u] = d;
  tin[u] = ++timer;
  up[u][0] = p;
  
  for (int i = 1; i < LOGN; ++i) {
    up[u][i] = up[up[u][i-1]][i-1];
  }
  
  for (auto& edge : adj[u]) {
    int v = edge.first;
    if (v != p) dfs_lca(v, u, d + 1);
  }
  
  tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
  if (is_ancestor(u, v)) return u;
  if (is_ancestor(v, u)) return v;
  for (int i = LOGN - 1; i >= 0; --i) {
    if (!is_ancestor(up[u][i], v)) {
      u = up[u][i];
    }
  }
  return up[u][0];
}

pair<int, unsigned long long> dfs_solve(int u, int p, int edge_label) {
  int cur_count = diff_count[u];
  unsigned long long cur_hash = diff_hash[u];

  for (auto& edge : adj[u]) {
    int v = edge.first;
    int lbl = edge.second;
    if (v != p) {
      auto res = dfs_solve(v, u, lbl);
      cur_count += res.first;
      cur_hash += res.second;
    }
  }

  if (p != u) { 
    // Explicit cast of cur_count to unsigned long long before multiplication
    if (cur_hash == (unsigned long long)cur_count * label_hash[edge_label]) {
      bad_label[edge_label] = true;
    }
  }
  
  return {cur_count, cur_hash};
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  // 1. Clear structures up to the bounds of the current test case
  for (int i = 1; i <= n; ++i) {
    adj[i].clear();
    diff_count[i] = 0;
    diff_hash[i] = 0;
  }
  for (int i = 1; i <= k; ++i) {
    bad_label[i] = false;
  }
  timer = 0;

  // 2. Read Edges and Build Spanning Tree
  vector<Edge> non_tree_edges;
  DSU dsu(n);

  for (int i = 0; i < m; ++i) {
    int u, v, l;
    cin >> u >> v >> l;
    if (dsu.unite(u, v)) {
      adj[u].push_back({v, l});
      adj[v].push_back({u, l});
    } else {
      non_tree_edges.push_back({u, v, l});
    }
  }

  // 3. LCA Preprocessing
  dfs_lca(1, 1, 0);

  // 4. Path Updates via Difference Arrays
  for (auto& e : non_tree_edges) {
    int l = lca(e.u, e.v);
    unsigned long long h = label_hash[e.label];
    
    diff_count[e.u]++; 
    diff_count[e.v]++; 
    diff_count[l] -= 2;
    
    diff_hash[e.u] += h; 
    diff_hash[e.v] += h; 
    diff_hash[l] -= 2 * h;
  }

  // 5. Aggregate and Check Condition
  dfs_solve(1, 1, 0);

  // 6. Output string formatting
  for (int i = 1; i <= k; ++i) {
    if (bad_label[i]) {
      cout << "0";
    } else {
      cout << "1";
    }
  }
  cout << "\n";
}

int main() {
  // Fast I/O is mandatory for large constraints
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // Precompute random hashes globally so it is only done once
  mt19937_64 rng(1337);
  for (int i = 1; i < MAXN; i++) {
    label_hash[i] = rng();
  }

  int t;
  if (cin >> t) {
    while (t--) {
      solve();
    }
  }
  return 0;
}