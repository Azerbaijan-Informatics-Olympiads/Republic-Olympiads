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

bool is_composite(string s) {
  int n = stoi(s);
  if (n <= 3) return false;
  if (n % 2 == 0) return true;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return true;
  }
  return false;
}
void solve() {
  string s;
  cin >> s;
  int n = s.size();
  int last_star = -1;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '*') last_star = i;
  }
  if (last_star == -1) {
    if (is_composite(s)) {
      cout << s << ln;
    } else {
      cout << "-1" << ln;
    }
  } else {
    int dsum = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '*' && i != last_star) s[i] = '1';
      if (i != last_star) dsum += (s[i] - '0');
    }
    s[last_star] = '0' + (9 - dsum % 9);
    cout << s << ln;
  }
}
int main() {
  iospeed;
  solve();
  return 0;
}