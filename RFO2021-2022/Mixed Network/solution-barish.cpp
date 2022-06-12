#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

int n, m, x, y;
long long res = 0;

// g is directed version, g_uni is undirected version, and g_rev is reversed directed version of graph
vector<int> g[N], g_uni[N], g_rev[N];

bool vis[N];
vector<int> component; // a connected component
void get_component(int v) {
  component.push_back(v);
  vis[v] = true;
  for (int i : g_uni[v]) {
    if (!vis[i]) {
      get_component(i);
    }
  }
}

vector<int> order, scc; // order is topological order; current scc component
vector<int> g_scc[N]; // condensation graph
int color[N]; // coloring for cycle detection
bool cycle;
bool used[N]; // yet another array for checking visited
int sz = 0;

void dfs(int v) {
  /*
    This DFS checks if a cycle exists in the graph while finding the order for the topological sort
  */
  sz++;
  color[v] = 1;
  for (int i : g[v]) {
    if (!color[i]) {
      dfs(i);
    } else if (color[i] == 1) {
      cycle = 1;
    }
  }
  color[v] = 2;
  order.push_back(v);
}

void get_scc(int v) {
  used[v] = true;
  scc.push_back(v);
  for (int i : g_rev[v]) {
    if (!used[i]) {
      get_scc(i);
    }
  }
}

void solve(vector<int> &nodes) {
  cycle = sz = 0;
  for (int i : nodes) {
    if (!color[i]) {
        dfs(i);
    }
  }
  if (!cycle) {
    res += 1ll * (sz - 1) * x;
    order.clear();
    return;
  }
  reverse(order.begin(), order.end());
  long long all_ans = min(1ll * sz * x, 1ll * (sz - 1) * y);
  long long condensed_ans = 0;
  int scc_count = 0;
  for (int v : order) {
    if (used[v]) continue;
    get_scc(v);
    scc_count += 1;
    condensed_ans += min((long long)scc.size() * x, (long long)(scc.size() - 1) * y);
    scc.clear();
  }
  condensed_ans += 1ll * (scc_count - 1) * x;
  res += min(all_ans, condensed_ans);
  order.clear();
}

int main() {
  ios_base :: sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m >> x >> y;
  if (y < x) {
    x = y;
  } else if (2 * x < y) {
    y = 2 * x;
  }
  for (int a, b, i = 1; i <= m; i++) {
    cin >> a >> b;
    g_uni[a].push_back(b); g_uni[b].push_back(a);
    g[a].push_back(b);
    g_rev[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      get_component(i);
      solve(component);
      component.clear();
    }
  }
  cout << res << endl;
  return 0;
}
