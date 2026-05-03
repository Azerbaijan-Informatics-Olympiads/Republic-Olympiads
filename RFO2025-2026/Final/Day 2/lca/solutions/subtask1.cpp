#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

vector<vector<int>> adj;
vector<int> depth;
vector<int> parent_node;

// Precompute depths and parents using a simple DFS
void dfs(int u, int p, int d) {
  parent_node[u] = p;
  depth[u] = d;
  for (int v : adj[u]) {
    if (v != p) {
      dfs(v, u, d + 1);
    }
  }
}

// Simple LCA algorithm (fast enough since max depth <= 18)
int get_lca(int u, int v) {
  // Make u the deeper node
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  
  // Bring u up to the same depth as v
  while (depth[u] > depth[v]) {
    u = parent_node[u];
  }
  
  // Move both up until they meet
  while (u != v) {
    u = parent_node[u];
    v = parent_node[v];
  }
  
  return u;
}

int main() {
  // Optimize standard I/O operations for speed
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n)) return 0;

  adj.resize(n + 1);
  depth.resize(n + 1);
  parent_node.resize(n + 1);

  // Read the n-1 edges of the tree
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Root the tree at vertex 1
  dfs(1, 0, 0);

  long long ans = 0;
  int max_mask = (1 << n);

  // Iterate over all possible subsets using bitmasks
  for (int mask = 1; mask < max_mask; ++mask) {
    int current_lca = -1;
    
    // Find the LCA of all nodes present in the current subset
    for (int i = 0; i < n; ++i) {
      if ((mask >> i) & 1) {
        int node = i + 1; // 1-based indexing for vertices
        
        if (current_lca == -1) {
          current_lca = node; // First node in the subset
        } else {
          current_lca = get_lca(current_lca, node);
        }
      }
    }
    
    // Add the resulting LCA index to the total sum
    ans = (ans + current_lca) % MOD;
  }

  // Print the final modulo sum
  cout << ans << "\n";

  return 0;
}