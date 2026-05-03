#include <iostream>
#include <vector>
#include <map>

using namespace std;

void solve() {
  int n, m;
  if (!(cin >> n >> m)) return;

  vector<long long> a(n);
  map<long long, int> freq_a;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    freq_a[a[i]]++;
  }

  vector<long long> b(m);
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  vector<long long> st;
  map<long long, int> freq_st;

  for (int i = 0; i < m; i++) {
    st.push_back(b[i]);
    freq_st[b[i]]++;

    while (st.size() >= 3) {
      int sz = st.size();
      long long x = st[sz - 3];
      long long y = st[sz - 2];
      long long z = st[sz - 1];

      if (y == x + z) {
        // THE FLAWED HEURISTIC: Global Frequency Protection
        // If our stack currently has less than or equal to the amount of 'y' 
        // that array 'a' needs, we blindly assume THIS 'y' is the base element.
        if (freq_st[y] <= freq_a[y]) {
          break; // Refuse to reduce
        }

        // Otherwise, it's an excess 'y', meaning it must be a generated peak. Reduce it.
        st.pop_back(); // Remove z
        st.pop_back(); // Remove y
        freq_st[y]--;  // Update our running frequency to reflect the deletion
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