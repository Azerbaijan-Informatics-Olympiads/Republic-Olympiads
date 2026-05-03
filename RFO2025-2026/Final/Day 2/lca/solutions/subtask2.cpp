#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

vector<vector<int>> adj;
vector<vector<int>> children;
vector<long long> p2;

// Build a directed tree structure (parent to children)
void build_tree(int u, int p) {
  for (int v : adj[u]) {
    if (v != p) {
      children[u].push_back(v);
      build_tree(v, u);
    }
  }
}

// Unoptimized DFS to count nodes in a subtree
// Calling this repeatedly makes the algorithm O(N^2)
int count_nodes_in_subtree(int u) {
  int count = 1; // Count itself
  for (int v : children[u]) {
    count += count_nodes_in_subtree(v);
  }
  return count;
}

int main() {
  // Optimize standard I/O operations for speed
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n)) return 0;

  adj.resize(n + 1);
  children.resize(n + 1);
  p2.resize(n + 1);

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

  // Root the tree at vertex 1
  build_tree(1, 0);

  long long ans = 0;

  // Iterate over every node to calculate its contribution as the exact LCA
  for (int u = 1; u <= n; ++u) {
    // 1. Total nodes in u's subtree
    int total_sz = count_nodes_in_subtree(u);
    long long lca_subsets = (p2[total_sz] - 1 + MOD) % MOD;

    // 2. Subtract subsets that are entirely inside any single child's subtree
    for (int v : children[u]) {
      int child_sz = count_nodes_in_subtree(v);
      long long child_subsets = (p2[child_sz] - 1 + MOD) % MOD;
      lca_subsets = (lca_subsets - child_subsets + MOD) % MOD;
    }

    // 3. Multiply the valid subsets by the node's index and add to total answer
    long long contribution = (lca_subsets * u) % MOD;
    ans = (ans + contribution) % MOD;
  }

  // Print the final modulo sum
  cout << ans << "\n";

  return 0;
}