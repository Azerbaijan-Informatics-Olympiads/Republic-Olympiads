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

ll rangeSqSum(ll x, ll y) {
    return (y - x + 1) * ((x * x + y * y + x * y) * 2 + y - x) / 6;
}

ll rangeSum(ll x, ll y) {
  return (y * (y + 1) - x * (x - 1)) / 2;
}

ll findK(ll N, ll L) {
  ll l = 1, r = 1e5;
  ll K, m;
  while (l <= r) {
    m = (l + r) / 2;
    if (rangeSum(L, L + m - 1) <= N) {
      K = m;
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return K;
}
void solve() {
  ll N, L;
  cin >> N >> L;
  ll K = findK(N, L);
  ll R = N - rangeSum(L, L + K - 1);
  ll I = R / K;
  ll J = R % K;
  ll res = rangeSqSum(L + I, L + I + K - 1 - J) + rangeSqSum(L + I + K - J + 1, L + I + K);
  cout << res << ln;
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
