#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

// DSU (Disjoint Set Union) for tree validation (checking cycles and connectivity)
struct DSU {
  vector<int> par;
  int components;

  DSU(int n) {
    par.assign(n + 1, -1);
    components = n;
  }

  int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]);
  }

  bool unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false; // Cycle detected
    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    components--;
    return true;
  }
};

int main(int argc, char* argv[]) {
  // Initialize testlib validator
  registerValidation(argc, argv);

  // Default max constraints for Group 5
  int max_n = 300'000;
  string group = validator.group();

  // Adjust max_n based on Group
  if (group == "1") max_n = 18;
  else if (group == "2") max_n = 2000;

  // Read n
  int n = inf.readInt(1, max_n, "n");
  inf.readEoln();

  DSU dsu(n);

  // Read n-1 edges
  for (int i = 1; i < n; ++i) {
    int u = inf.readInt(1, n, "u_i");
    inf.readSpace();
    int v = inf.readInt(1, n, "v_i");
    inf.readEoln();

    // Check for self-loops
    ensuref(u != v, "Self-loop found between %d and %d", u, v);
    
    // Check for cycles or multiple edges
    ensuref(dsu.unite(u, v), "Cycle or multiple edges found when adding edge %d-%d", u, v);

    // Group 3: Star graph centered at 1 (u_i=1, v_i=i+1 or vice versa)
    if (group == "3") {
      bool is_star_edge = (u == 1 && v == i + 1);
      ensuref(is_star_edge, "Group 3 violated: edges must be between 1 and i+1");
    }
    
    // Group 4: Line graph (u_i=i, v_i=i+1 or vice versa)
    if (group == "4") {
      bool is_line_edge = (u == i && v == i + 1);
      ensuref(is_line_edge, "Group 4 violated: edges must be between i and i+1");
    }
  }

  // Ensure the graph is fully connected (components == 1)
  // If n=1, components will be 1 initially and the loop won't run, which is correct.
  ensuref(dsu.components == 1, "Graph is not connected, isolated components exist.");

  // Ensure no extra characters or lines at the end of the file
  inf.readEof();

  return 0;
}