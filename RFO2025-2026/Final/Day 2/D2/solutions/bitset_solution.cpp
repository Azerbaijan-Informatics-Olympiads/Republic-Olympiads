#include <iostream>
#include <vector>
#include <numeric>
#include <cstdint>

using namespace std;

struct Edge {
  int u, v, label;
};

const int MAXN = 250005;
vector<pair<int, int>> adj[MAXN]; 
vector<int> label_edges[MAXN];    
vector<vector<uint64_t>> val;

struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n + 1);
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
      parent[root_j] = root_i;
      return true;
    }
    return false;
  }
};

// DFS to compute XOR sums of bitsets for tree edges
vector<uint64_t> dfs(int u, int p, vector<vector<uint64_t>>& edge_weight) {
  vector<uint64_t> current_xor = val[u];
  
  for (auto& edge : adj[u]) {
    int v = edge.first;
    int id = edge.second;
    if (v != p) {
      vector<uint64_t> subtree_xor = dfs(v, u, edge_weight);
      edge_weight[id] = subtree_xor; // Assign computed bitset to tree edge
      
      // XOR the subtree's bitset into the current node's bitset
      for (size_t i = 0; i < current_xor.size(); ++i) {
        current_xor[i] ^= subtree_xor[i];
      }
    }
  }
  return current_xor;
}

// Attempts to insert a bitset into the Gaussian Basis
bool insert_into_basis(vector<uint64_t>& cur, vector<vector<uint64_t>>& basis, int num_non_tree) {
  for (int b = num_non_tree - 1; b >= 0; --b) {
    if ((cur[b / 64] >> (b % 64)) & 1) {
      // If the basis slot is empty, we found a linearly independent vector
      if (basis[b].empty()) {
        basis[b] = cur;
        return true; 
      }
      // Otherwise, XOR and continue down to lower bits
      for (size_t i = 0; i < cur.size(); ++i) {
        cur[i] ^= basis[b][i];
      }
    }
  }
  // If it reduced to all 0s, it is linearly dependent (forms a cut)
  return false; 
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  for (int i = 1; i <= n; ++i) adj[i].clear();
  for (int i = 1; i <= k; ++i) label_edges[i].clear();

  DSU dsu(n);
  int num_non_tree = 0;
  
  // Calculate exactly how many 64-bit words we need for the bitset
  // This helps minimize the massive memory footprint.
  vector<Edge> edges(m + 1);
  for (int i = 1; i <= m; ++i) {
    cin >> edges[i].u >> edges[i].v >> edges[i].label;
    if (dsu.find(edges[i].u) == dsu.find(edges[i].v)) {
      num_non_tree++;
    } else {
      dsu.unite(edges[i].u, edges[i].v);
    }
  }

  int words = (num_non_tree + 63) / 64;
  
  vector<vector<uint64_t>> edge_weight(m + 1, vector<uint64_t>(words, 0));
  val.assign(n + 1, vector<uint64_t>(words, 0));

  dsu = DSU(n); // Reset DSU for second pass
  int non_tree_idx = 0;

  for (int i = 1; i <= m; ++i) {
    int u = edges[i].u;
    int v = edges[i].v;
    int l = edges[i].label;
    label_edges[l].push_back(i);

    if (dsu.unite(u, v)) {
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
    } else {
      // It's a non-tree edge. Give it a distinct basis vector (single bit set)
      edge_weight[i][non_tree_idx / 64] |= (1ULL << (non_tree_idx % 64));
      
      // Add it to the endpoints for the Difference Array
      val[u][non_tree_idx / 64] ^= (1ULL << (non_tree_idx % 64));
      val[v][non_tree_idx / 64] ^= (1ULL << (non_tree_idx % 64));
      
      non_tree_idx++;
    }
  }

  // If there are no non-tree edges, the graph is a tree. Any edge removal breaks it.
  if (num_non_tree > 0) {
    dfs(1, 0, edge_weight);
  }

  for (int i = 1; i <= k; ++i) {
    if (num_non_tree == 0) {
      // Tree edge-case handler
      if (label_edges[i].empty()) cout << "1";
      else cout << "0";
      continue;
    }

    // Initialize an empty basis for this label
    vector<vector<uint64_t>> basis(num_non_tree);
    bool connected = true;

    for (int id : label_edges[i]) {
      vector<uint64_t> cur = edge_weight[id];
      if (!insert_into_basis(cur, basis, num_non_tree)) {
        connected = false;
        break;
      }
    }

    if (connected) cout << "1";
    else cout << "0";
  }
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