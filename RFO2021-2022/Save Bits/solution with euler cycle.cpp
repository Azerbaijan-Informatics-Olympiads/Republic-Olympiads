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

const int up = (1 << 19);
bool visited[up][2];
int fullMask;

string euler = "";

void eulerCycle(int node, string bit) {
  for (int i = 0; i <= 1; ++i) {
    if (!visited[node][i]) {
      visited[node][i] = true;
      eulerCycle(((node & fullMask) << 1) + i, to_string(i));
    }
  }
  euler += bit;
}
void solve() {
  int n;
  cin >> n;
  if (n == 1) {
    cout << "01\n";
  } else {
    fullMask = (1 << (n - 2)) - 1;
    eulerCycle(0, string(n - 1, '0'));
    reverse(all(euler));
    cout << euler << ln;
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
