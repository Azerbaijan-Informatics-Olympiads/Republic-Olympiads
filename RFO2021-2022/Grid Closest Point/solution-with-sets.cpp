#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define pii pair<int, int>
#define piii pair<pii, int>
#define vi vector<int>
#define vvi vector<vi>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define x first
#define y second
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

void solve() {
  int n, m, q, type, x, y;
  cin >> n >> m >> q;
  bool swaped = false;
  if (n > m) {
    swaped = true;
    swap(n, m);
  }
  vector<set<int>>s(n);
  for (int i = 1; i <= q; ++i) {
    cin >> type >> x >> y;
    --x;
    --y;
    if (swaped) {
      swap(x, y);
    }
    if (type == 1) {
      s[x].insert(y);
    } else {
      int res = oo;
      for (int i = 0; i < n; ++i) {
        if (size(s[i])) {
          auto itr = s[i].upper_bound(y);
          if (itr != s[i].end()) {
            res = min(res, abs(i - x) + (*itr) - y);
          }
          if (itr != s[i].begin()) {
            --itr;
            res = min(res, abs(i - x) + y - (*itr));
          }
        }
      }
      cout << res << ln;
    }
  }
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
