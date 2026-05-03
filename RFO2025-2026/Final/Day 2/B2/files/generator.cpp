#include "testlib.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <array>

#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define eb emplace_back
#define pb push_back
#define all(v) v.begin(), v.end()

using namespace std;
typedef long long ll;


void makeTree(int n, vector<array<int, 2>> &e) {
  for (int i = 1; i < n; ++i) {
    int pa = rnd.next(0, i - 1);
    e.pb({pa, i});
  }
}

void makeWideTree(int n, vector<array<int, 2>> &e, int per) {
  for (int i = 1; i < n; ++i) {
    int pa;
    if (rnd.next(0, 99) < per) pa = rnd.next(0, min(4, i - 1));
    else pa = rnd.next(0, i - 1);
    e.pb({pa, i});
  }
}

void makeChain(int n, vector<array<int, 2>> &e) {
  for (int i = 1; i < n; ++i) {
    e.pb({i - 1, i});
  }
}

void makeStar(int n, vector<array<int, 2>> &e) {
  for (int i = 1; i < n; ++i) {
    e.pb({0, i});
  }
}

void makeLongTree(int n, vector<array<int, 2>> &e, int len) {
  for (int i = 1; i < len; ++i) {
    e.pb({i - 1, i});
  }
  for (int i = len; i < n; ++i) {
    int pa = rnd.next(0, i - 1);
    e.pb({pa, i});
  }
}

void makeBinTree(int n, vector<array<int, 2>> &e) {
  const int B = 512;
  vi deg(n, 0);
  vvi cand(1);
  cand[0].eb(0);
  int cnt = 1;
  for (int i = 1; i < n; ++i) {
    int pos = rnd.next(0, cnt - 1);
    int j = 0;
    while (cand[j].size() <= pos) {
      pos -= cand[j].size();
      ++j;
    }
    int pa = cand[j][pos];
    e.pb({pa, i});
    ++deg[pa];
    if (deg[pa] == 3) {
      cand[j].erase(cand[j].begin() + pos);
      --cnt;
    }
    ++deg[i];
    if (cand.back().size() == B) {
      cand.pb({});
    }
    cand.back().eb(i);
    ++cnt;
  }
}

void makeBalancedBinTree(int n, vector<array<int, 2>> &e) {
  for (int i = 1; i < n; ++i) {
    int pa = (i - 1) / 2;
    e.pb({pa, i});
  }
}

void makeLongBinTree(int n, vector<array<int, 2>> &e, int len) {
  const int B = 512;
  vi deg(n, 0);
  vvi cand(1);
  cand[0].eb(0);
  int cnt = 1;
  for (int i = 1; i < len; ++i) {
    e.pb({i - 1, i});
    deg[i - 1]++;
    deg[i]++;
    if (cand.back().size() == B) cand.pb({});
    cand.back().eb(i);
    ++cnt;
  }
  for (int i = len; i < n; ++i) {
    int pos = rnd.next(0, cnt - 1);
    int j = 0;
    while (cand[j].size() <= pos) {
      pos -= cand[j].size();
      ++j;
    }
    int pa = cand[j][pos];
    e.pb({pa, i});
    ++deg[pa];
    if (deg[pa] == 3) {
      cand[j].erase(cand[j].begin() + pos);
      --cnt;
    }
    ++deg[i];
    if (cand.back().size() == B) cand.pb({});
    cand.back().eb(i);
    ++cnt;
  }
}


struct DSU {
  int components;
  vector<int>par;
  DSU(int n) {
    par.assign(n, -1);
    components = n;
  }
  int Find(int u) {
    if (par[u] < 0) return u;
    else return par[u] = Find(par[u]);
  }
  bool Union(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u != v) {
      if (par[u] > par[v]) {
        swap(u, v);
      }
      par[u] += par[v];
      par[v] = u;
      --components;
      return true;
    } else {
      return false;
    }
  }
};

bool isTree(int n, const vector<array<int, 2>> &e, int offset = 0) {
  if (e.size() != n - 1) return false;
  DSU dsu(n);
  for (auto [u, v] : e) {
    dsu.Union(u - offset, v - offset);
  }
  return dsu.components == 1;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int subtask = opt<int>("subtask");
  int n = opt<int>("n");
  int type = opt<int>("type");

  if (subtask == 3) type = 2;
  if (subtask == 4) type = 1;

  vector<array<int, 2>>e;

  if (type == 0) makeTree(n, e);
  else if (type == 1) makeChain(n, e);
  else if (type == 2) makeStar(n, e);
  else if (type == 3) makeWideTree(n, e, 80);
  else if (type == 4) makeLongTree(n, e, max(2, (int)(n * 0.8)));
  else if (type == 5) makeBinTree(n, e);
  else if (type == 6) makeBalancedBinTree(n, e);
  else if (type == 7) makeLongBinTree(n, e, max(2, (int)(n * 0.8)));

  if (subtask != 3 && subtask != 4) {
    vi p(n);
    iota(all(p), 1);
    shuffle(all(p));
    shuffle(all(e));
    for (auto& edge : e) {
      edge[0] = p[edge[0]];
      edge[1] = p[edge[1]];
      if (rnd.next(0, 1)) swap(edge[0], edge[1]);
    }
  } else {
    for (auto& edge : e) {
      edge[0] += 1;
      edge[1] += 1;
    }
  }

  ensuref(isTree(n, e, 1), "Fatal Error: The generated graph is not Tree!");

  cout << n << "\n";
  for (auto [u, v] : e) {
    cout << u << " " << v << "\n";
  }
  return 0;
}