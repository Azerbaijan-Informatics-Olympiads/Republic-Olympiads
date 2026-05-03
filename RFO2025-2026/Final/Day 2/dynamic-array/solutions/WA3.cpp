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

    while (st.size() >= 3) {
      int sz = st.size();
      
      // THE SUBTLE BUG: Shallow Prefix Checking
      // We check if the last element matches, but we FAIL to verify
      // if the rest of the stack actually matches the prefix of 'a'.
      if (sz <= n && st.back() == a[sz - 1]) {
        break;
      }

      long long x = st[sz - 3];
      long long y = st[sz - 2];
      long long z = st[sz - 1];

      if (y == x + z) {
        // Perform the reduction
        st.pop_back(); // Remove z
        st.pop_back(); // Remove y
        st.push_back(z); // Put z back
      } else {
        break;
      }
    }
  }

  // Final check
  if (st == a) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}