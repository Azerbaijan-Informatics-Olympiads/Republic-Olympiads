#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Fast Disjoint Set Union to check connectivity
struct DSU {
  vector<int> parent;
  int comps;
  
  DSU(int n) {
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
    comps = n; // Start with N isolated components
  }
  
  int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
  }
  
  bool unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      parent[root_i] = root_j;
      comps--; // Successfully merged two components
      return true;
    }
    return false;
  }
};

struct Edge {
  int u, v, label;
};

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  
  vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    cin >> edges[i].u >> edges[i].v >> edges[i].label;
  }
  
  string ans = "";
  
  // Test removing each manufacturer's edges one by one
  for (int i = 1; i <= k; ++i) {
    DSU dsu(n);
    
    for (const auto& e : edges) {
      // Add all edges EXCEPT the ones belonging to manufacturer 'i'
      if (e.label != i) {
        dsu.unite(e.u, e.v);
      }
    }
    
    // If we only have 1 component left, the graph is fully connected
    if (dsu.comps == 1) {
      ans += "1";
    } else {
      ans += "0";
    }
  }
  
  cout << ans << "\n";
}

int main() {
  // Fast I/O
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