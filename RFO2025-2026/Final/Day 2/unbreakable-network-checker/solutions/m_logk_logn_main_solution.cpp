//#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define oo 1000000001
#define eb emplace_back
#define pb push_back
#define mpr make_pair
#define ln '\n'
#define ull unsigned long long
#define ll long long
#define all(v) v.begin(), v.end()
#define iospeed ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T> void show(vector<T> &v) {
  for (T i : v) {
    cout << i << ' ';
  }
  cout << ln;
}

struct RollbackDSU {
  vector<int> parent, sz;
  vector<pair<int, int>> history;
  int comps;

  RollbackDSU(int n) {
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
    sz.assign(n + 1, 1);
    comps = n;
  }

  int find(int u) {
    while (u != parent[u]) u = parent[u];
    return u;
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    
    if (sz[u] < sz[v]) swap(u, v);
    
    history.push_back({v, u});
    parent[v] = u;
    sz[u] += sz[v];
    --comps;
  }

  int get_state() { return history.size(); }

  void rollback(int state) {
    while (history.size() > state) {
      int child = history.back().first;
      int prnt = history.back().second;
      history.pop_back();
      
      sz[prnt] -= sz[child];
      parent[child] = child;
      ++comps;
    }
  }
};

const int MAX = 2.5e5 + 5;

vector<pair<int, int>> edges_by_label[MAX];
bool bad_label[MAX];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= k; ++i) {
    edges_by_label[i].clear();
    bad_label[i] = false;
  }
  for (int i = 0; i < m; ++i) {
    int u, v, l;
    cin >> u >> v >> l;
    edges_by_label[l].push_back({u, v});
  }
  RollbackDSU dsu(n);
  auto check_connectivity = [&](auto& self, int L, int R) -> void {
    if (L == R) bad_label[L] = (dsu.comps > 1);
    else {
      int mid = L + (R - L) / 2;
      
      int state_before_left = dsu.get_state();
      for (int i = mid + 1; i <= R; ++i) {
        for (auto e : edges_by_label[i]) dsu.unite(e.first, e.second);
      }
      self(self, L, mid);
      dsu.rollback(state_before_left);

      int state_before_right = dsu.get_state();
      for (int i = L; i <= mid; ++i) {
        for (auto e : edges_by_label[i]) dsu.unite(e.first, e.second);
      }
      self(self, mid + 1, R);
      dsu.rollback(state_before_right);
    }
  };

  check_connectivity(check_connectivity, 1, k);

  for (int i = 1; i <= k; ++i) {
    if (bad_label[i]) {
      cout << "0";
    } else {
      cout << "1";
    }
  }
  cout << "\n";
}
int main() {
  iospeed;
  int t;
  cin >> t;
  for (int cs = 1; cs <= t; ++cs) {
    solve();
  }
  return 0;
}