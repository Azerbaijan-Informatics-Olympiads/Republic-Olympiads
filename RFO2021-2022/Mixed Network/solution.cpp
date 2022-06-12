#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define pii pair<int, int>
#define piii pair<pii, int>
#define vi vector<int>
#define vvi vector<vi>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define f first
#define s second
#define oo 1000000001
#define eb emplace_back
#define pb push_back
#define mpr make_pair
#define size(v) (int)v.size()
#define ln '\n'
#define ull unsigned long long
#define ll long long
#define all(v) v.begin(), v.end()

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void dfs(int v, vi &visited, vvi &g, vi &component) {
  visited[v] = 1;
  for (int to : g[v]) {
    if (!visited[to]) {
      dfs(to, visited, g, component);
    }
  }
  component.eb(v);
}

void findSCC(int v, vi &color, vvi &g_rev) {
  color[v] = 2;
  for (int to : g_rev[v]) {
    if (color[to] != 2) {
      findSCC(to, color, g_rev);
    }
  }
}

ll solve(vi &component, vvi &g, vvi &g_rev, vi &color, int x, int y) {
  vector<int>order;
  for (int node : component) {
    if (!color[node]) {
      dfs(node, color, g, order);
    }
  }
  reverse(all(order));
  int SCCs = 0;
  for (int node : order) {
    if (color[node] != 2) {
      findSCC(node, color, g_rev);
      ++SCCs;
    }
  }
  return min(1ll * x * size(component), 1ll * y * (size(component) - SCCs) + 1ll * x * (SCCs - 1));
}
void solve() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;
  if (x + x < y) {
    y = x + x;
  } else if (y < x) {
    x = y;
  }
  vvi g(n + 1), g_rev(n + 1), g_uni(n + 1);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    g[u].eb(v);
    g_rev[v].eb(u);
    g_uni[u].eb(v);
    g_uni[v].eb(u);
  }
  vector<int>visited(n + 1, 0);
  vector<int>color(n + 1, 0);
  vector<int>component;
  ll res = 0;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i, visited, g_uni, component); // finds connected component in undirected graph
      res += solve(component, g, g_rev, color, x, y);
      component.clear();
    }
  }
  cout << res << ln;
}
int main() {
  ios_base::sync_with_stdio(false);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
