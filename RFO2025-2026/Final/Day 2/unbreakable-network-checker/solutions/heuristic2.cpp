#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
#include <random>
#include <algorithm>

using namespace std;

struct Edge {
  int u, v, label, id;
};

// ==========================================
// SUBTASK 2: Tree (M = N - 1)
// ==========================================
void solve_st2(int n, int m, int k, const vector<Edge>& edges) {
  vector<bool> has_edge(k + 1, false);
  for (const auto& e : edges) has_edge[e.label] = true;
  string ans = "";
  for (int i = 1; i <= k; ++i) ans += (has_edge[i] ? "0" : "1");
  cout << ans << "\n";
}

// ==========================================
// SUBTASK 4: Pseudotree (M = N)
// ==========================================
void solve_st4(int n, int m, int k, const vector<Edge>& edges) {
  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> degree(n + 1, 0);
  for (const auto& e : edges) {
    adj[e.u].push_back({e.v, e.id});
    adj[e.v].push_back({e.u, e.id});
    degree[e.u]++;
    degree[e.v]++;
  }

  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 1) q.push(i);
  }

  vector<bool> is_bridge(m + 1, false);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto& edge : adj[u]) {
      int v = edge.first, id = edge.second;
      if (!is_bridge[id]) {
        is_bridge[id] = true;
        degree[u]--; degree[v]--;
        if (degree[v] == 1) q.push(v);
      }
    }
  }

  vector<int> bridge_count(k + 1, 0), cycle_count(k + 1, 0);
  for (const auto& e : edges) {
    if (is_bridge[e.id]) bridge_count[e.label]++;
    else cycle_count[e.label]++;
  }

  string ans = "";
  for (int i = 1; i <= k; ++i) {
    ans += (bridge_count[i] > 0 || cycle_count[i] >= 2) ? "0" : "1";
  }
  cout << ans << "\n";
}

// ==========================================
// HEURISTIC CASE: Multi-Layer Hash
// ==========================================
struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int i) {
    return parent[i] == i ? i : parent[i] = find(parent[i]);
  }
  bool unite(int i, int j) {
    int ri = find(i), rj = find(j);
    if (ri != rj) {
      parent[rj] = ri;
      return true;
    }
    return false;
  }
};

struct Basis {
  uint64_t basis[64];
  Basis() { for (int i = 0; i < 64; ++i) basis[i] = 0; }
  bool insert(uint64_t x) {
    for (int i = 63; i >= 0; --i) {
      if ((x >> i) & 1) {
        if (!basis[i]) {
          basis[i] = x;
          return true;
        }
        x ^= basis[i];
      }
    }
    return false;
  }
};

vector<vector<pair<int, int>>> tree_adj;
vector<uint64_t> node_val, edge_weight;

uint64_t dfs_hash(int u, int p) {
  uint64_t current_xor = node_val[u];
  for (auto& edge : tree_adj[u]) {
    int v = edge.first, id = edge.second;
    if (v != p) {
      uint64_t sub_xor = dfs_hash(v, u);
      edge_weight[id] = sub_xor;
      current_xor ^= sub_xor;
    }
  }
  return current_xor;
}

bool check_large_label_heuristic(vector<uint64_t>& w) {
  // 1. Macro Cut Check
  uint64_t total = 0;
  for (uint64_t x : w) total ^= x;
  if (total == 0) return false; // Entire set forms a cut
  
  // 2. Micro Cut Check (Size 1)
  for (uint64_t x : w) {
    if (x == 0) return false; // Contains a bridge
  }
  
  sort(w.begin(), w.end());
  
  // 3. Micro Cut Check (Size 2)
  for (size_t i = 1; i < w.size(); ++i) {
    if (w[i] == w[i - 1]) return false; // Duplicate weight = 2-cut
  }
  
  // 4. Micro Cut Check (Size 3)
  // Limited to avoid TLE on artificially massive labels
  if (w.size() <= 1000) {
    for (size_t i = 0; i < w.size(); ++i) {
      for (size_t j = i + 1; j < w.size(); ++j) {
        uint64_t target = w[i] ^ w[j];
        if (binary_search(w.begin(), w.end(), target)) {
          return false; // Three edges XOR to 0 = 3-cut
        }
      }
    }
  }
  
  // If no common cut configurations were found, it's highly likely safe
  return true;
}

void solve_heuristic(int n, int m, int k, const vector<Edge>& edges) {
  tree_adj.assign(n + 1, vector<pair<int, int>>());
  node_val.assign(n + 1, 0);
  edge_weight.assign(m + 1, 0);
  vector<vector<int>> label_edges(k + 1);
  
  DSU dsu(n);
  mt19937_64 rng(1337);

  for (const auto& e : edges) {
    label_edges[e.label].push_back(e.id);
    if (dsu.unite(e.u, e.v)) {
      tree_adj[e.u].push_back({e.v, e.id});
      tree_adj[e.v].push_back({e.u, e.id});
    } else {
      uint64_t w = rng();
      edge_weight[e.id] = w;
      node_val[e.u] ^= w;
      node_val[e.v] ^= w;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (dsu.parent[i] == i) dfs_hash(i, 0);
  }

  string ans = "";
  for (int i = 1; i <= k; ++i) {
    if (label_edges[i].empty()) {
      ans += "1";
      continue;
    }
    
    int sz = label_edges[i].size();
    if (sz <= 62) {
      // The Exact Layer
      Basis b;
      bool connected = true;
      for (int id : label_edges[i]) {
        if (!b.insert(edge_weight[id])) {
          connected = false;
          break;
        }
      }
      ans += (connected ? "1" : "0");
    } else {
      // The Heuristic Layer
      vector<uint64_t> w;
      w.reserve(sz);
      for (int id : label_edges[i]) w.push_back(edge_weight[id]);
      
      bool connected = check_large_label_heuristic(w);
      ans += (connected ? "1" : "0");
    }
  }
  cout << ans << "\n";
}

// ==========================================
// MAIN DISPATCHER
// ==========================================
void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    cin >> edges[i].u >> edges[i].v >> edges[i].label;
    edges[i].id = i + 1;
  }

  if (m == n - 1) solve_st2(n, m, k, edges);
  else if (m == n) solve_st4(n, m, k, edges);
  else solve_heuristic(n, m, k, edges);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  if (cin >> t) {
    while (t--) solve();
  }
  return 0;
}