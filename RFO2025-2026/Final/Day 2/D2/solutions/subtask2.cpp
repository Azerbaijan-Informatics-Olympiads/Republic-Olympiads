#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  // Track if a manufacturer owns at least one edge
  vector<bool> has_edge(k + 1, false);

  for (int i = 0; i < m; ++i) {
    int u, v, label;
    cin >> u >> v >> label;
    
    // We only care that this label exists in the tree
    has_edge[label] = true;
  }

  string ans = "";
  for (int i = 1; i <= k; ++i) {
    if (has_edge[i]) {
      // They own a bridge, removing it breaks the graph
      ans += "0";
    } else {
      // They own nothing, the graph is safe
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