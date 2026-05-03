#pragma GCC optimize ("O3")
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

const int MAX = 3e5 + 5;
const int mod = 998244353;
vi g[MAX];
int pow2[MAX], sub_size[MAX], cnt[MAX];

void dfs(int v, int pa) {
  sub_size[v] = 1;
  for (int to : g[v]) {
    if (to != pa) {
      dfs(to, v);
      sub_size[v] += sub_size[to];
      cnt[v] -= (pow2[sub_size[to]] - 1);
      if (cnt[v] < 0) cnt[v] += mod;
    }
  }
  cnt[v] += (pow2[sub_size[v]] - 1);
  if (cnt[v] < 0) cnt[v] += mod;
  if (cnt[v] >= mod) cnt[v] -= mod;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].eb(v);
    g[v].eb(u);
  }
  pow2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow2[i] = (pow2[i - 1] * 2) % mod;
  }
  dfs(1, 1);
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    res = (res + (1ll * cnt[i] * i) % mod);
    if (res >= mod) res -= mod;
  }
  cout << res << ln;
}
int main() {
  iospeed;
  solve();
  return 0;
}