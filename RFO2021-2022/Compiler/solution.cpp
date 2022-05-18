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
  string s;
  cin >> s;
  string res = "";
  string brackets = "()[]{}";
  for (char c : s) {
    if (brackets.find(c) != -1) {
      res += c;
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
