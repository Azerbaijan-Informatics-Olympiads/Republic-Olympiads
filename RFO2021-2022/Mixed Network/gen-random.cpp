#include "testlib.h"
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

void addEdges(int startNode, int endNode, int numEdges, set<pii> &edges) {
  while (numEdges) {
    int u = rnd.next(startNode, endNode);
    int v = rnd.next(startNode, endNode);
    if (u != v && edges.find(mpr(u, v)) == edges.end()) {
      edges.insert(mpr(u, v));
      --numEdges;
    }
  }
}

void divideIntoK(int N, int K, vector<int> &components) {
  // partition N into K parts
	// create a vector with (N - K) 1s and (K - 1) 0s, then shuffle it
  vector<int>bits;
  for (int i = 0; i < N - K; ++i) {
    bits.eb(1);
  }
  for (int i = 1; i < K; ++i) {
    bits.eb(0);
  }
  shuffle(all(bits));
  int currentComponent = 1;
  int ptr = 0;
  bits.eb(0); // to add last component
  for (int b : bits) {
    if (b == 0) {
      components[ptr++] = currentComponent;
      currentComponent = 1;
    } else {
      ++currentComponent;
    }
  }
}

void dfs(int v, vi &visited, vvi &g, vi &component) {
  visited[v] = 1;
  for (int to : g[v]) {
    if (!visited[to]) {
      dfs(to, visited, g, component);
    }
  }
  component.eb(v);
}

void findSCC(int v, vi &color, vvi &g_rev) {
  color[v] = 2;
  for (int to : g_rev[v]) {
    if (color[to] != 2) {
      findSCC(to, color, g_rev);
    }
  }
}

int solve(vi &component, vvi &g, vvi &g_rev, vi &color) {
  vector<int>order;
  for (int node : component) {
    if (!color[node]) {
      dfs(node, color, g, order);
    }
  }
  reverse(all(order));
  int SCCs = 0;
  for (int node : order) {
    if (color[node] != 2) {
      findSCC(node, color, g_rev);
      ++SCCs;
    }
  }
  return size(component) - SCCs;
}

const int MAX_XY = 1e9;

void solveXY(int n, int m, set<pii> &edges, int &X, int &Y) {
  vvi g(n + 1), g_rev(n + 1), g_uni(n + 1);
  for (pii e : edges) {
    int u = e.f, v = e.s;
    g[u].eb(v);
    g_rev[v].eb(u);
    g_uni[u].eb(v);
    g_uni[v].eb(u);
  }
  vector<int>visited(n + 1, 0);
  vector<int>color(n + 1, 0);
  vector<int>component;
  set<int>XYdecider;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i, visited, g_uni, component); // finds connected component in undirected graph
      XYdecider.insert(solve(component, g, g_rev, color));
      component.clear();
    }
  }
  int l = (*XYdecider.begin());
  int r = (*XYdecider.rbegin());
  if (r == 0) {
    X = rnd.next(1, MAX_XY);
    Y = rnd.next(1, MAX_XY);
  } else {
    if (l == 0) ++l;
    int t = rnd.next(l, r);
    Y = MAX_XY / (t + 1) * (t + 1);
    X = MAX_XY / (t + 1) * t;
    X += rnd.next(1, min(100, (Y - X) / 2));
  }
}
int main(int argc, char* argv[]){
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]); // number of nodes
	int M = atoi(argv[2]); // number of edges
	int K = atoi(argv[3]); // number of undirected components (roughly)
  int divisionType = atoi(argv[4]);
  int X = atoi(argv[5]);  // calculate below if X = Y = 0
  int Y = atoi(argv[6]);

  vector<int>components(K);
  if (divisionType <= 2) {  // almost same
    for (int i = 0; i < K; ++i) {
      components[i] = N / K;
    }
    for (int i = 0; i < N % K; ++i) {
      ++components[i];
    }
    if (divisionType == 2) { // one big
      for (int i = 1; i < K; ++i) {
        if (components[i] > 1) {
          ++components[0];
          --components[i];
        }
      }
    }
  } else {
    divideIntoK(N, K, components);
  }

	vector<int>numEdges(K, 0);
	int totalEdges = 0;
	for (int i = 0; i < K; ++i) {
    if (components[i] > 1) {
      numEdges[i] = (1ll * M * components[i]) / N;
      totalEdges += numEdges[i];
    }
	}
	while (totalEdges < M) {
	  int id = rnd.next(0, K - 1);
    if (components[id] > 1) {
      ++numEdges[id];
      ++totalEdges;
    }
	}

  set<pii>edges;

  int startNode = 0;
  for (int i = 0; i < K; ++i) {
    int endNode = startNode + components[i];
    addEdges(startNode, endNode - 1, numEdges[i], edges);
    startNode = endNode;
  }
  if (X == 0) {
    solveXY(N, M, edges, X, Y);
  }
  // shuffling and printing
  vi p(N);
  for (int i = 0; i < N; ++i) {
    p[i] = i + 1;
  }
  shuffle(all(p));

  cout << N << ' ' << M << ' ' << X << ' ' << Y << ln;
  for (pii e : edges) {
    cout << p[e.f] << ' ' << p[e.s] << ln;
  }
  return 0;
}
