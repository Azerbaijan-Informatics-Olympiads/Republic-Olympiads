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
  // is_pref[k] will be true if st[0..k-1] exactly matches a[0..k-1]
  vector<bool> is_pref;
  is_pref.push_back(true); // Base case: prefix of size 0 always matches

  for (int i = 0; i < m; i++) {
    st.push_back(b[i]);
    int k = st.size();
    bool current_match = false;
    
    if (k <= n && is_pref[k - 1] && st.back() == a[k - 1]) {
      current_match = true;
    }
    is_pref.push_back(current_match);

    // Try to reduce the stack if the top 3 elements form x, x+z, z
    while (st.size() >= 3) {
      int sz = st.size();
      
      // Do not reduce if the current stack perfectly matches a prefix of 'a'
      if (sz <= n && is_pref[sz]) {
        break;
      }
      
      if (st[sz - 2] == st[sz - 3] + st[sz - 1]) {
        // Pop the top element and the reducible middle element
        long long last = st.back();
        st.pop_back();
        is_pref.pop_back();

        st.pop_back();
        is_pref.pop_back();

        // Push the top element back and re-evaluate the prefix match
        st.push_back(last);
        int new_k = st.size();
        bool match = false;
        
        if (new_k <= n && is_pref[new_k - 1] && st.back() == a[new_k - 1]) {
          match = true;
        }
        is_pref.push_back(match);
      } else {
        break;
      }
    }
  }

  // If the reduced stack exactly matches 'a', the transformation is valid
  if (st == a) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  // Optimize standard I/O operations for performance
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}