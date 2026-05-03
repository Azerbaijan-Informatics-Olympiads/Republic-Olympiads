#include <iostream>
#include <vector>
#include <set>
#include <tuple>

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

  // Step 1: Find all naturally occurring peaks in array 'a' and protect those triplets.
  set<tuple<long long, long long, long long>> valid_triplets;
  for (int i = 1; i < n - 1; i++) {
    if (a[i] == a[i - 1] + a[i + 1]) {
      valid_triplets.insert(make_tuple(a[i - 1], a[i], a[i + 1]));
    }
  }

  vector<long long> st;

  for (int i = 0; i < m; i++) {
    st.push_back(b[i]);

    while (st.size() >= 3) {
      int sz = st.size();
      long long x = st[sz - 3];
      long long y = st[sz - 2];
      long long z = st[sz - 1];

      if (y == x + z) {
        // THE FLAW: Global Triplet Protection
        // If this triplet mathematically matches a peak that exists anywhere in 'a',
        // we blindly assume it is the base array and refuse to reduce it.
        if (valid_triplets.count(make_tuple(x, y, z))) {
          break; 
        }

        // Otherwise, it's a generated peak. Reduce it.
        long long right_neighbor = st.back();
        st.pop_back(); // Pop z
        st.pop_back(); // Pop y
        st.push_back(right_neighbor); // Put z back
      } else {
        break;
      }
    }
  }

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