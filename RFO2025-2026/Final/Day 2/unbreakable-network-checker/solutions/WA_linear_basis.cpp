/*
The algorithm maps the graph's cut-space into a 64-bit integer space (GF(2)64). 
It checks if a set of edges forms a cut by checking if their mapped 64-bit values 
are linearly dependent (i.e., if they XOR to 0 in the basis).

However, a 64-bit integer can only represent a vector space of at most 64 dimensions.

If a single label has 65 or more edges in the spanning tree, 
it is mathematically impossible for all 65 values to be linearly 
independent in a 64-bit space. By the Pigeonhole Principle (or basic linear algebra), 
inserting the 65th edge into the Basis struct will always fail, returning false.

Therefore, if a manufacturer has 100 cables that form a simple straight line 
(no cut at all), the algorithm will falsely flag them as linearly dependent and output 0. 
It assumes the graph broke, when in reality, the 64-bit capacity just overflowed.

*/

#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int MAXN = 250005;

struct Edge {
  int u, v, label;
};

vector<pair<int, int>> adj[MAXN]; // {target_node, edge_index}
vector<int> label_edges[MAXN];    // edge indices grouped by label

unsigned long long edge_weight[MAXN];
unsigned long long val[MAXN];

struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n + 1);
    for (int i = 1; i <= n; ++i) parent[i] = i;
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

// GF(2) Linear Basis for independence checking
struct Basis {
  unsigned long long basis[64];
  Basis() {
    for (int i = 0; i < 64; ++i) basis[i] = 0;
  }
  bool insert(unsigned long long x) {
    for (int i = 63; i >= 0; --i) {
      if ((x >> i) & 1) {
        if (!basis[i]) {
          basis[i] = x;
          return true; // Independent
        }
        x ^= basis[i];
      }
    }
    return false; // Linearly dependent (XORed to 0)
  }
};

// DFS to compute XOR sums for tree edges
unsigned long long dfs(int u, int p) {
  unsigned long long current_xor = val[u];
  for (auto& edge : adj[u]) {
    int v = edge.first;
    int id = edge.second;
    if (v != p) {
      unsigned long long subtree_xor = dfs(v, u);
      edge_weight[id] = subtree_xor;
      current_xor ^= subtree_xor;
    }
  }
  return current_xor;
}

void solve(mt19937_64& rng) {
  int n, m, k;
  cin >> n >> m >> k;

  // Clear structures for current test case
  for (int i = 1; i <= n; ++i) {
    adj[i].clear();
    val[i] = 0;
  }
  for (int i = 1; i <= k; ++i) {
    label_edges[i].clear();
  }

  DSU dsu(n);
  
  for (int i = 1; i <= m; ++i) {
    int u, v, l;
    cin >> u >> v >> l;
    label_edges[l].push_back(i);

    if (dsu.unite(u, v)) {
      // Tree edge: weight will be calculated in DFS
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
    } else {
      // Non-tree edge: assign random weight immediately
      unsigned long long w = rng();
      edge_weight[i] = w;
      val[u] ^= w;
      val[v] ^= w;
    }
  }

  // Compute tree edge weights
  dfs(1, 0);

  // Check each label
  for (int i = 1; i <= k; ++i) {
    Basis b;
    bool connected = true;
    
    for (int id : label_edges[i]) {
      // If we cannot insert the weight, it means this edge forms a cut
      // with the other edges of the same label.
      if (!b.insert(edge_weight[id])) {
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

  mt19937_64 rng(1337);

  int t;
  if (cin >> t) {
    while (t--) {
      solve(rng);
    }
  }
  return 0;
}