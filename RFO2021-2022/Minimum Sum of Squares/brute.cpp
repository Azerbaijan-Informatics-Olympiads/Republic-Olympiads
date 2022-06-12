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

ll brute(ll n, ll l) {
  if (n == 0) return 0;
  else if (n < l) return 1e18;
  else {
    ll res = 1e18;
    for (ll i = l; i <= n; ++i) {
      res = min(res, i * i + brute(n - i, i + 1));
    }
    return res;
  }
}
void solve() {
  ll n, l;
  cin >> n >> l;
  cout << brute(n, l) << ln;
}
int main() {
  ios_base::sync_with_stdio(false);

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
