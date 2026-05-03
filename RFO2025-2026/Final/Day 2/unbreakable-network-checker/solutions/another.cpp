#include <iostream>
#include <vector>

using namespace std;

// DSU with Rollbacks
struct DSU {
  vector<int> parent;
  vector<int> sz;
  int components;
  vector<int> history;

  void init(int n) {
    parent.resize(n + 1);
    sz.resize(n + 1);
    components = n;
    history.clear();
    for (int i = 1; i <= n; ++i) {
      parent[i] = i;
      sz[i] = 1;
    }
  }

  int find(int i) {
    // Note: Path compression is NOT allowed when using rollbacks.
    // We only use while-loops to find the root.
    while (i != parent[i]) {
      i = parent[i];
    }
    return i;
  }

  bool unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    
    if (root_i != root_j) {
      // Union by size to keep the tree shallow (O(log N) depth)
      if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
      
      parent[root_j] = root_i;
      sz[root_i] += sz[root_j];
      components--;
      
      history.push_back(root_j);
      return true;
    }
    return false;
  }

  void rollback() {
    int child = history.back();
    history.pop_back();
    
    int root = parent[child];
    parent[child] = child;
    sz[root] -= sz[child]; 
    components++;
  }
} dsu;

struct QueryEdge {
  int u, v, l, r;
};

// Top-Down Divide and Conquer (Replaces explicit Segment Tree)
void solve_dnc(int l, int r, const vector<QueryEdge>& edges) {
  int unions_made = 0;
  vector<QueryEdge> left_edges, right_edges;
  
  for (const auto& edge : edges) {
    // If the edge completely covers the current interval, apply it immediately
    if (edge.l <= l && r <= edge.r) {
      if (dsu.unite(edge.u, edge.v)) {
        unions_made++;
      }
    } else {
      // Otherwise, pass it down to the intersecting child intervals
      int mid = l + (r - l) / 2;
      if (edge.l <= mid) left_edges.push_back(edge);
      if (edge.r > mid) right_edges.push_back(edge);
    }
  }

  // If we reached a leaf node, we check the global connectivity
  if (l == r) {
    if (dsu.components == 1) cout << "1";
    else cout << "0";
  } else {
    // Continue dividing the problem
    int mid = l + (r - l) / 2;
    solve_dnc(l, mid, left_edges);
    solve_dnc(mid + 1, r, right_edges);
  }

  // Backtrack the DSU state before stepping back up the recursion tree
  for (int i = 0; i < unions_made; ++i) {
    dsu.rollback();
  }
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  dsu.init(n);

  vector<QueryEdge> initial_edges;
  // Reserve capacity to prevent vector reallocations during edge loading
  initial_edges.reserve(2 * m); 

  for (int i = 0; i < m; ++i) {
    int u, v, l;
    cin >> u >> v >> l;
    
    // Add the active ranges for this edge (when manufacturer 'l' is NOT removed)
    if (l > 1) {
      initial_edges.push_back({u, v, 1, l - 1});
    }
    if (l < k) {
      initial_edges.push_back({u, v, l + 1, k});
    }
  }
  
  // Start the DnC recursion
  if (k > 0) {
    solve_dnc(1, k, initial_edges);
  }
  cout << "\n";
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