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

void solve() {
  int n, m, x;
  cin >> n >> m;
  priority_queue<int>q;
  for (int i = 0; i < n; ++i) {
    cin >> x;
    q.push(x);
  }
  for (int i = 0; i < m; ++i) {
    int largest = q.top();
    q.pop();
    largest /= 2;
    q.push(largest);
  }
  ll res = 0;
  for (int i = 0; i < n; ++i) {
    res += q.top();
    q.pop();
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
