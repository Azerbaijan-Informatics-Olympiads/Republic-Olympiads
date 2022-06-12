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

vector<string> GenerateLyndon(int n, int s) {
  vector<string>res;
  string L = "/"; // ascii 47
  while (L != "") {
    ++L.back();
    res.eb(L);
    int sz = size(L);
    while (size(L) < n) {
      L += L[size(L) - sz];
    }
    while (L != "" && L.back() == '/' + s) L.pop_back();
  }
  return res;
}
void solve() {
  int n;
  cin >> n;
  vector<string>Lyndon = GenerateLyndon(n, 2);
  string res = "";
  for (string L : Lyndon) {
    if (n % size(L) == 0) {
      res += L;
    }
  }
  res += string(n - 1, '0');
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
