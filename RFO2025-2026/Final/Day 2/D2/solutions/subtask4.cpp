#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Edge {
  int to;
  int id;
  int label;
};

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<Edge>> adj(n + 1);
  vector<int> degree(n + 1, 0);
  
  for (int i = 1; i <= m; ++i) {
    int u, v, l;
    cin >> u >> v >> l;
    adj[u].push_back({v, i, l});
    adj[v].push_back({u, i, l});
    degree[u]++;
    degree[v]++;
  }

  // Find all bridges by iteratively removing leaves (degree == 1)
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 1) {
      q.push(i);
    }
  }

  vector<bool> is_bridge(m + 1, false);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& edge : adj[u]) {
      int v = edge.to;
      int id = edge.id;

      // If the edge hasn't been removed yet
      if (!is_bridge[id]) {
        is_bridge[id] = true; // Mark as a bridge (tree edge)
        degree[u]--;
        degree[v]--;

        // If the neighbor becomes a leaf, add it to the queue
        if (degree[v] == 1) {
          q.push(v);
        }
      }
    }
  }

  // Count bridges and cycle edges for each manufacturer
  vector<int> bridge_count(k + 1, 0);
  vector<int> cycle_count(k + 1, 0);

  // To avoid iterating through adjacency list again, we can iterate 
  // through nodes and their edges, being careful not to double-count.
  // A simpler way is to just recount from the adjacency list:
  vector<bool> edge_processed(m + 1, false);
  for (int u = 1; u <= n; ++u) {
    for (auto& edge : adj[u]) {
      if (!edge_processed[edge.id]) {
        edge_processed[edge.id] = true;
        
        if (is_bridge[edge.id]) {
          bridge_count[edge.label]++;
        } else {
          cycle_count[edge.label]++;
        }
      }
    }
  }

  // Build the answer
  string ans = "";
  for (int i = 1; i <= k; ++i) {
    if (bridge_count[i] > 0 || cycle_count[i] >= 2) {
      // The graph is broken
      ans += "0";
    } else {
      // The graph remains connected
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