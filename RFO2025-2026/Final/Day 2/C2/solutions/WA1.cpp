#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n, m;
  if (!(cin >> n >> m)) return;

  vector<long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<long long> b(m);
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  vector<long long> st;
  
  for (int i = 0; i < m; i++) {
    st.push_back(b[i]);
    
    // Greedily and blindly reduce the stack whenever we see x, x+y, y
    while (st.size() >= 3) {
      int sz = st.size();
      if (st[sz - 2] == st[sz - 3] + st[sz - 1]) {
        // We found a reducible peak. Remove it.
        long long right_neighbor = st.back();
        st.pop_back(); // Pop the right neighbor
        st.pop_back(); // Pop the peak (x+y)
        st.push_back(right_neighbor); // Put the right neighbor back
      } else {
        break; // No more reductions possible locally
      }
    }
  }

  // If our blind reduction happens to match 'a', we assume it's valid
  if (st == a) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  // Fast I/O
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}