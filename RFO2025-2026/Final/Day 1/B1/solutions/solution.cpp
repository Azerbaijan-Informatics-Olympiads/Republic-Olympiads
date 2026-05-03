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

bool ok(vector<array<int, 2>> &s) {
  set<int>diff;
  for (auto[x, y] : s) {
    for (auto [i, j] : s) {
      diff.insert(abs(i - x) + abs(j - y));
    }
  }
  int n = s.size();
  return (diff.size() == n * (n - 1) / 2 + 1);
}
void solve() {
  vector<array<int, 2>>s;
  vi has(4100, 0);
  for (int x = 2026; x >= 1; --x) {
    for (int y = 2026; y >= 1; --y) {
      bool done = true;
      vi newD;
      for (auto [i, j] : s) {
        int d = abs(x - i) + abs(y - j);
        if (has[d]) {
          done = false;
          break;
        }
        newD.eb(d);
        has[d]++;
      }
      if (done) {
        //cerr << x << ' ' << y << ln;
        s.pb({x, y});
        //assert(ok(s));
      } else {
        for (int d : newD) has[d]--;
      }
    }
  }
  cout << s.size() << ln;
  for (auto [i, j] : s) cout << i << ' ' << j << ln;
}
int main() {
  iospeed;
  solve();
  return 0;
}