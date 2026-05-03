#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Edge {
  int u, v, label;
};

// Standard DFS to count reachable nodes
void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited, int& visited_count) {
  visited[u] = true;
  visited_count++;
  
  for (int v : adj[u]) {
    if (!visited[v]) {
      dfs(v, adj, visited, visited_count);
    }
  }
}

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
    vector<vector<int>> adj(n + 1);
    
    // Build the graph ignoring edges with label 'i'
    for (const auto& e : edges) {
      if (e.label != i) {
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
      }
    }
    
    vector<bool> visited(n + 1, false);
    int visited_count = 0;
    
    // Start DFS from node 1. If the graph is connected, 
    // we should be able to reach all N nodes.
    dfs(1, adj, visited, visited_count);
    
    if (visited_count == n) {
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