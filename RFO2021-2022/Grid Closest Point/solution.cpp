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

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int n, int m, vvi &dist) {
  queue<pii>q;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (dist[x][y] == 0) {
        q.push(mpr(x, y));
      }
    }
  }
  while (!q.empty()) {
    pii p = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int x = p.x + dx[i];
      int y = p.y + dy[i];
      if (x >= 0 && x < n && y >= 0 && y < m && dist[x][y] > dist[p.x][p.y] + 1) {
        dist[x][y] = dist[p.x][p.y] + 1;
        q.push(mpr(x, y));
      }
    }
  }
}

void solve() {
  const int d = 5000;
  int n, m, q, type, x, y;
  cin >> n >> m >> q;
  vvi dist(n, vi(m, oo));
  vector<pii>lazy;
  for (int i = 1; i <= q; ++i) {
    cin >> type >> x >> y;
    --x;
    --y;
    if (type == 1) {
      lazy.eb(mpr(x,y));
    } else {
      int res = dist[x][y];
      for (pii p : lazy) {
        int d = abs(x - p.x) + abs(y - p.y);
        res = min(res, d);
      }
      cout << res << ln;
    }
    if (size(lazy) == d) {
      for (pii p : lazy) {
        dist[p.x][p.y] = 0;
      }
      lazy.clear();
      bfs(n, m, dist);
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
