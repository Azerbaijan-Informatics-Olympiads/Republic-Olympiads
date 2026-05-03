#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {
  int to;
  int id;
};

int timer;
vector<int> tin, low;
vector<bool> is_bridge;
vector<vector<Edge>> adj;

// Tarjan's Bridge-Finding DFS
void dfs(int u, int p_edge_id = -1) {
  tin[u] = low[u] = ++timer;
  
  for (auto& edge : adj[u]) {
    int v = edge.to;
    int id = edge.id;

    // Do not walk back across the exact same edge we just came from
    if (id == p_edge_id) continue;

    if (tin[v]) {
      // Back-edge found: update the lowest reachable time
      low[u] = min(low[u], tin[v]);
    } else {
      // Tree-edge: continue DFS
      dfs(v, id);
      low[u] = min(low[u], low[v]);
      
      // If the lowest reachable node from v is strictly below u, 
      // there is no back-edge wrapping around this edge. It's a bridge!
      if (low[v] > tin[u]) {
        is_bridge[id] = true;
      }
    }
  }
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  // Reset states for the current testcase
  timer = 0;
  tin.assign(n + 1, 0);
  low.assign(n + 1, 0);
  is_bridge.assign(m + 1, false);
  adj.assign(n + 1, vector<Edge>());

  for (int i = 1; i <= m; ++i) {
    int u, v, l;
    cin >> u >> v >> l;
    
    // In Subtask 3, l is exactly i. We use i as the universal edge ID.
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }

  // Find all bridges
  for (int i = 1; i <= n; ++i) {
    if (!tin[i]) {
      dfs(i);
    }
  }

  // Build the answer string
  string ans = "";
  for (int i = 1; i <= k; ++i) {
    if (is_bridge[i]) {
      // It is a bridge. Removing it breaks the graph.
      ans += "0";
    } else {
      // It is part of a cycle. Removing it leaves the graph connected.
      ans += "1";
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