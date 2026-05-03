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


void makeTree(int n, vector<array<int, 3>> &e) {
  for (int i = 1; i < n; ++i) {
    int pa = rnd.next(0, i - 1);
    e.pb({pa, i, 0});
  }
}

void makeWideTree(int n, vector<array<int, 3>> &e, int per) {
  for (int i = 1; i < n; ++i) {
    int pa;
    if (rnd.next(0, 99) < per) pa = rnd.next(0, min(4, i - 1));
    else pa = rnd.next(0, i - 1);
    e.pb({pa, i, 0});
  }
}

void makeChain(int n, vector<array<int, 3>> &e) {
  for (int i = 1; i < n; ++i) {
    e.pb({i - 1, i, 0});
  }
}

void makeStar(int n, vector<array<int, 3>> &e) {
  for (int i = 1; i < n; ++i) {
    e.pb({0, i, 0});
  }
}

void makeLongTree(int n, vector<array<int, 3>> &e, int len) {
  for (int i = 1; i < len; ++i) {
    e.pb({i - 1, i, 0});
  }
  for (int i = len; i < n; ++i) {
    int pa = rnd.next(0, i - 1);
    e.pb({pa, i, 0});
  }
}

void makeBinTree(int n, vector<array<int, 3>> &e) {
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
    e.pb({pa, i, 0});
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

void makeBalancedBinTree(int n, vector<array<int, 3>> &e) {
  for (int i = 1; i < n; ++i) {
    int pa = (i - 1) / 2;
    e.pb({pa, i, 0});
  }
}

void makeLongBinTree(int n, vector<array<int, 3>> &e, int len) {
  const int B = 512;
  vi deg(n, 0);
  vvi cand(1);
  cand[0].eb(0);
  int cnt = 1;
  for (int i = 1; i < len; ++i) {
    e.pb({i - 1, i, 0});
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
    e.pb({pa, i, 0});
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


void makePseudoTree(int n, vector<array<int, 3>> &e, int cycle_len, vi& cycle_edges, vi& branch_edges) {
  for (int i = 0; i < cycle_len; ++i) {
    e.pb({i, (i + 1) % cycle_len, 0});
    cycle_edges.pb(e.size() - 1);
  }
  for (int i = cycle_len; i < n; ++i) {
    int pa = rnd.next(0, i - 1);
    e.pb({pa, i, 0});
    branch_edges.pb(e.size() - 1);
  }
}

void makeSemifinalGraph(int n, int k, vector<array<int, 3>> &e) {
  int center = 0;
  for (int i = 1; i < n; i += (k - 1)) {
    int u = center;
    int label = 1;
    int v = i;
    while (label < k && v < n) {
      e.pb({u, v, label});
      u = v;
      ++v;
      ++label;
    }
    e.pb({u, center, k});
  }
}


void assignLabelsRandom(vector<array<int, 3>> &e, int k) {
  for (auto &edge : e) {
    if (edge[2] == 0) edge[2] = rnd.next(1, k);
  }
}

void addEdges(int n, int m, int k, vector<array<int, 3>> &e, bool allow_multi) {
  ll max_uv = 1ll * n * (n - 1) / 2;
  ll capacity = allow_multi ? max_uv * k : max_uv;
  
  set<array<int, 2>> seen_uv;
  set<array<int, 3>> seen_uvc;

  for (auto [u, v, c] : e) {
    if (u > v) swap(u, v);
    seen_uv.insert({u, v});
    if (c != 0) seen_uvc.insert({u, v, c});
  }

  ll add = m - e.size();
  if (add <= 0) return;

  ll current_size = allow_multi ? seen_uvc.size() : seen_uv.size();
  if (add > capacity - current_size) {
    add = capacity - current_size;
  }

  if (5ll * add > capacity - current_size) {
    vector<array<int, 3>> rem;
    for (int u = 0; u < n; ++u) {
      for (int v = u + 1; v < n; ++v) {
        if (!allow_multi) {
          if (seen_uv.find({u, v}) == seen_uv.end()) {
            rem.pb({u, v, rnd.next(1, k)});
          }
        } else {
          for (int c = 1; c <= k; ++c) {
            if (seen_uvc.find({u, v, c}) == seen_uvc.end()) {
              rem.pb({u, v, c});
            }
          }
        }
      }
    }
    shuffle(rem.begin(), rem.end());
    e.insert(e.end(), rem.begin(), rem.begin() + add);
  } 
  else {
    while (add > 0) {
      int u = rnd.next(0, n - 1);
      int v = rnd.next(0, n - 1);
      if (u == v) continue;
      if (u > v) swap(u, v);
      
      if (!allow_multi) {
        if (seen_uv.find({u, v}) != seen_uv.end()) continue;
        int c = rnd.next(1, k);
        e.pb({u, v, c});
        seen_uv.insert({u, v});
        --add;
      } else {
        int c = rnd.next(1, k);
        if (seen_uvc.find({u, v, c}) != seen_uvc.end()) continue;
        e.pb({u, v, c});
        seen_uvc.insert({u, v, c});
        --add;
      }
    }
  }
}

void applySubtask4Labeling(vector<array<int, 3>> &e, int k, vi &cycle_edges, vi &branch_edges) {
  int c_size = cycle_edges.size();
  int b_size = branch_edges.size();
  
  shuffle(cycle_edges.begin(), cycle_edges.end());
  shuffle(branch_edges.begin(), branch_edges.end());
  
  int unique = rnd.next(0, min(k / 3, min(c_size, b_size) / 10 + 1));
  int pairs = rnd.next(0, min(k - 1 - 2 * unique, min(c_size, b_size) / 10 + 1));
  int cur_label = 0;

  for (int i = 0; i < unique; ++i) {
    e[cycle_edges[i]][2] = cur_label++;
  }
  for (int i = 0; i < unique; ++i) {
    e[branch_edges[i]][2] = cur_label++;
  }

  for (int i = unique; i < unique + pairs; ++i) {
    e[cycle_edges[i]][2] = cur_label;
    e[branch_edges[i]][2] = cur_label;
    cur_label++;
  }
  
  for(int i = unique + pairs; i < c_size; ++i) {
    e[cycle_edges[i]][2] = rnd.next(cur_label, k - 1);
  }
  for(int i = unique + pairs; i < b_size; ++i) {
    e[branch_edges[i]][2] = rnd.next(cur_label, k - 1);
  }
  vi ord(k);
  iota(all(ord), 1);
  shuffle(all(ord));
  for (auto &edge : e) {
    edge[2] = ord[edge[2]];
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

bool isConnected(int n, const vector<array<int, 3>> &e, int offset = 0) {
  DSU dsu(n);
  for (auto [u, v, l] : e) {
    dsu.Union(u - offset, v - offset);
  }
  return dsu.components == 1;
}


int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int subtask = opt<int>("subtask");
  int t = opt<int>("t");
  int exact_n = opt<int>("n");
  int exact_m = opt<int>("m");
  int exact_k = opt<int>("k");
  int type = opt<int>("type");

  cout << t << "\n";

  for (int i = 0; i < t; ++i) {
    int n = exact_n;
    int m = exact_m;
    int k = exact_k;

    if (m < n - 1) m = n - 1; 

    if (subtask == 2) {
      m = n - 1;
    } else if (subtask == 3) {
      k = m; 
    } else if (subtask == 4) {
      m = n;
    }

    vector<array<int, 3>> e;

    auto build_tree_base = [&]() {
      if (type == 0) makeTree(n, e);
      else if (type == 1) makeChain(n, e);
      else if (type == 2) makeStar(n, e);
      else if (type == 3) makeWideTree(n, e, 80);
      else if (type == 4) makeLongTree(n, e, max(2, (int)(n * 0.8)));
      else if (type == 5) makeBinTree(n, e);
      else if (type == 6) makeBalancedBinTree(n, e);
      else if (type == 7) makeLongBinTree(n, e, max(2, (int)(n * 0.8)));
    };

    if (type <= 7) {
      build_tree_base();
      if (subtask != 3) assignLabelsRandom(e, k);

      if (m > n - 1) {
        addEdges(n, m, k, e, subtask != 3); 
      }
    } 
    else if (type == 8) {
      int cycle_len = (rnd.next(0, 1) ? rnd.next(max(3, n / 2), n): rnd.next(3, max(3, n/4)));
      vi cycle_edges, branch_edges;
      makePseudoTree(n, e, cycle_len, cycle_edges, branch_edges);
      
      if (subtask == 4) {
        applySubtask4Labeling(e, k, cycle_edges, branch_edges);
      } else if (subtask != 3) {
        assignLabelsRandom(e, k);
      }

      if (m > n) {
        addEdges(n, m, k, e, subtask != 3);
      }
    } 
    else if (type >= 9) {
      makeSemifinalGraph(n, k, e);
      if (type == 10) {
        int state = rnd.next(1, 3);
        if ((state & 1)) {
          int extras = rnd.next(1, min(10, n / 10 + 1));
          addEdges(n, e.size() + extras, k, e, true);
        }
        
        if ((state & 2)) { 
          int target_deletes = rnd.next(1, min(3, (int)e.size() / 10));
          int successful_deletes = 0;
          int attempts = 0;

          while (successful_deletes < target_deletes && attempts < 50) {
            attempts++;
            int idx = rnd.next(0, (int)e.size() - 1);
            
            array<int, 3> removed_edge = e[idx];
            swap(e[idx], e.back());
            e.pop_back();
            
            if (isConnected(n, e)) {
              successful_deletes++;
            } else {
              e.push_back(removed_edge);
              swap(e[idx], e.back());
            }
          }
        }
      }
      m = e.size();
    }

    vi p(n);
    iota(all(p), 1);
    shuffle(all(p));
    shuffle(all(e));
    for (auto& edge : e) {
      edge[0] = p[edge[0]];
      edge[1] = p[edge[1]];
      if (rnd.next(0, 1)) swap(edge[0], edge[1]);
    }

    // make sure the label of the i-th edge is exactly i
    if (subtask == 3) {
      for (int j = 0; j < m; ++j) {
        e[j][2] = j + 1; 
      }
    }
    ensuref(isConnected(n, e, 1), "Fatal Error: The generated graph is not connected!");

    cout << n << " " << m << " " << k << "\n";
    for (auto [u, v, l] : e) {
      cout << u << " " << v << " " << l << "\n";
    }
  }
  return 0;
}