#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <array>

using namespace std;

void dfs(int v, vector<bool> &vis, const vector<vector<int>> &g) {
  vis[v] = true;
  for (int to : g[v]) if (!vis[to]) dfs(to, vis, g);
}

bool isConnected(int n, const set<array<int, 3>> &e) {
  vector<vector<int>>g(n + 1);
  for (auto [u, v, l] : e) {
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  vector<bool>vis(n + 1, false);
  dfs(1, vis, g);
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) return false;
  }
  return true;
}

const int MAX = 250000;
const int MAXS = 80000;
int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  string group = validator.group();

  int t = inf.readInt(1, 100, "t");
  inf.readEoln();

  int sum_n = 0;
  int sum_m = 0;
  int sum_k = 0;

  for (int i = 1; i <= t; ++i) {
    int n = inf.readInt(2, MAX, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, MAX, "m");
    inf.readSpace();
    int k = inf.readInt(2, MAX, "k");
    inf.readEoln();

    if (group != "6") {
      ensuref(n <= MAXS, "n exceeds local limit %d (actual: %d)", MAXS, n);
      ensuref(m <= MAXS, "m exceeds local limit %d (actual: %d)", MAXS, m);
      ensuref(k <= MAXS, "k exceeds local limit %d (actual: %d)", MAXS, k);
    }

    sum_n += n;
    sum_m += m;
    sum_k += k;

    if (group == "2") {
      ensuref(m == n - 1, "Subtask 2 requires m = n - 1, but got n=%d, m=%d", n, m);
    }
    if (group == "3") {
      ensuref(k == m, "Subtask 3 requires k = m, but got m=%d, k=%d", m, k);
    }
    if (group == "4") {
      ensuref(m == n, "Subtask 4 requires m = n, but got n=%d, m=%d", n, m);
    }

    set<array<int, 3>> edges;

    for (int j = 1; j <= m; ++j) {
      int u = inf.readInt(1, n, "u");
      inf.readSpace();
      int v = inf.readInt(1, n, "v");
      inf.readSpace();
      int c = inf.readInt(1, k, "c");
      inf.readEoln();

      ensuref(u != v, "Self-loops are not allowed (edge %d: %d to %d)", j, u, v);

      int min_u = min(u, v);
      int max_v = max(u, v);

      ensuref(edges.find({min_u, max_v, c}) == edges.end(), 
              "Same edge with the same label twice is not allowed: %d-%d with label %d", min_u, max_v, c);
      edges.insert({min_u, max_v, c});

      if (group == "3") {
        ensuref(c == j, "Subtask 3 requires the label of the %d-th edge to be exactly %d, but got %d", j, j, c);
      }
    }
    ensuref(isConnected(n, edges), "Fatal Error: The generated graph is not connected!");
  }

  inf.readEof();

  ensuref(sum_n <= MAX, "sum_n exceeds global limit %d (actual: %d)", MAX, sum_n);
  ensuref(sum_m <= MAX, "sum_m exceeds global limit %d (actual: %d)", MAX, sum_m);
  ensuref(sum_k <= MAX, "sum_k exceeds global limit %d (actual: %d)", MAX, sum_k);

  if (group == "1") {
    ensuref(sum_n <= 1000, "Subtask 1 requires sum_n <= 1000 (actual: %d)", sum_n);
    ensuref(sum_m <= 1000, "Subtask 1 requires sum_m <= 1000 (actual: %d)", sum_m);
    ensuref(sum_k <= 1000, "Subtask 1 requires sum_k <= 1000 (actual: %d)", sum_k);
  }
  return 0;
}