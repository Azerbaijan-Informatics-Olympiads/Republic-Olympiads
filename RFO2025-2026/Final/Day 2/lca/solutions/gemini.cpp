#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;
const int MAXN = 300005;

vector<int> adj[MAXN];
int sz[MAXN];
long long p2[MAXN];
long long ans = 0;

void dfs(int u, int p) {
  sz[u] = 1;
  long long child_subsets_sum = 0;

  for (int v : adj[u]) {
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      
      // Calculate non-empty subsets strictly within this child's subtree
      long long subsets = (p2[sz[v]] - 1 + MOD) % MOD;
      child_subsets_sum = (child_subsets_sum + subsets) % MOD;
    }
  }

  // Calculate non-empty subsets strictly within u's subtree
  long long total_subsets = (p2[sz[u]] - 1 + MOD) % MOD;
  
  // Subtract the subsets that are entirely contained within any single child's subtree
  long long lca_count = (total_subsets - child_subsets_sum + MOD) % MOD;
  
  // Add u's contribution to the answer
  long long contribution = (lca_count * u) % MOD;
  ans = (ans + contribution) % MOD;
}

int main() {
  // Optimize standard I/O operations for speed
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n)) return 0;

  // Precompute powers of 2 modulo 998244353
  p2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    p2[i] = (p2[i - 1] * 2) % MOD;
  }

  // Read the n-1 edges of the tree
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Start DFS from root vertex 1, parent is 0
  dfs(1, 0);

  // Print the final modulo sum
  cout << ans << "\n";

  return 0;
}