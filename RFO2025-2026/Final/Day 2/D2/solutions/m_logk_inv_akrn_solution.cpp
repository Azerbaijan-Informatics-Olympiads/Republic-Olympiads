#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <numeric>

using namespace std;

struct Edge {
  int u, v, c;
};

const int MAXN = 250005;
const int MAX_DEPTH = 30;

// Global flat arrays to completely eliminate allocator overhead
int parent_dsu[MAXN];
int sz[MAXN];
int active[MAXN];
int new_id[MAXN];

// Memory pool for edges at each depth of the recursion tree
Edge edge_pool[MAX_DEPTH][MAXN];
Edge initial_edges[MAXN];
char ans[MAXN];

// Highly optimized DSU with Path Compression
inline int find_dsu(int i) {
  int root = i;
  while (root != parent_dsu[root]) root = parent_dsu[root];
  int curr = i;
  while (curr != root) {
    int nxt = parent_dsu[curr];
    parent_dsu[curr] = root;
    curr = nxt;
  }
  return root;
}

void solve_dc(int L, int R, int V_count, Edge* E, int E_size, int depth) {
  // Base Case 1: Entirely connected
  if (V_count == 1) {
    for (int i = L; i <= R; ++i) ans[i] = '1';
    return;
  }
  // Base Case 2: Disconnected and no edges left to fix it
  if (E_size == 0) {
    for (int i = L; i <= R; ++i) ans[i] = '0';
    return;
  }

  // Pruning: Check if any vertices are dead/isolated
  for (int i = 0; i < V_count; ++i) active[i] = 0;
  for (int i = 0; i < E_size; ++i) {
    active[E[i].u] = 1;
    active[E[i].v] = 1;
  }
  
  int U = 0;
  for (int i = 0; i < V_count; ++i) U += active[i];
  if (U < V_count) {
    for (int i = L; i <= R; ++i) ans[i] = '0';
    return;
  }

  // Leaf reached, but graph still disconnected
  if (L == R) {
    ans[L] = '0';
    return;
  }

  int mid = L + (R - L) / 2;

  // ---------------------------------------------------------
  // Process Left Child (We need edges > mid to connect things)
  // ---------------------------------------------------------
  for (int i = 0; i < V_count; ++i) {
    parent_dsu[i] = i;
    sz[i] = 1;
    new_id[i] = -1;
  }
  
  for (int i = 0; i < E_size; ++i) {
    if (E[i].c > mid) {
      int u = find_dsu(E[i].u);
      int v = find_dsu(E[i].v);
      if (u != v) {
        if (sz[u] < sz[v]) swap(u, v);
        parent_dsu[v] = u;
        sz[u] += sz[v];
      }
    }
  }
  
  int V_left = 0;
  for (int i = 0; i < V_count; ++i) {
    int root = find_dsu(i);
    if (new_id[root] == -1) new_id[root] = V_left++;
    new_id[i] = new_id[root];
  }
  
  int E_left_size = 0;
  for (int i = 0; i < E_size; ++i) {
    if (E[i].c <= mid) {
      int nu = new_id[E[i].u];
      int nv = new_id[E[i].v];
      if (nu != nv) {
        edge_pool[depth][E_left_size++] = {nu, nv, E[i].c};
      }
    }
  }
  solve_dc(L, mid, V_left, edge_pool[depth], E_left_size, depth + 1);


  // ---------------------------------------------------------
  // Process Right Child (We need edges <= mid to connect things)
  // ---------------------------------------------------------
  for (int i = 0; i < V_count; ++i) {
    parent_dsu[i] = i;
    sz[i] = 1;
    new_id[i] = -1;
  }
  
  for (int i = 0; i < E_size; ++i) {
    if (E[i].c <= mid) {
      int u = find_dsu(E[i].u);
      int v = find_dsu(E[i].v);
      if (u != v) {
        if (sz[u] < sz[v]) swap(u, v);
        parent_dsu[v] = u;
        sz[u] += sz[v];
      }
    }
  }
  
  int V_right = 0;
  for (int i = 0; i < V_count; ++i) {
    int root = find_dsu(i);
    if (new_id[root] == -1) new_id[root] = V_right++;
    new_id[i] = new_id[root];
  }
  
  int E_right_size = 0;
  for (int i = 0; i < E_size; ++i) {
    if (E[i].c > mid) {
      int nu = new_id[E[i].u];
      int nv = new_id[E[i].v];
      if (nu != nv) {
        edge_pool[depth][E_right_size++] = {nu, nv, E[i].c};
      }
    }
  }
  solve_dc(mid + 1, R, V_right, edge_pool[depth], E_right_size, depth + 1);
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  for (int i = 0; i < m; ++i) {
    cin >> initial_edges[i].u >> initial_edges[i].v >> initial_edges[i].c;
    // Map to 0-indexed for the array logic
    initial_edges[i].u--;
    initial_edges[i].v--;
  }

  solve_dc(1, k, n, initial_edges, m, 0);

  // Print results
  ans[k + 1] = '\0';
  cout << (ans + 1) << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  if (cin >> t) {
    while (t--) {
      solve();
    }
  }
  return 0;
}