#include <iostream>
#include <vector>

using namespace std;

// Function to check if two vectors are identical
bool areEqual(const vector<long long>& v1, const vector<long long>& v2) {
  if (v1.size() != v2.size()) return false;
  for (int i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) return false;
  }
  return true;
}

bool canTransform(vector<long long> current, const vector<long long>& target, int m) {
  // Base Case: If size matches, check for equality
  if (current.size() == m) {
    return areEqual(current, target);
  }

  // Try inserting the sum between every pair of adjacent elements
  for (int i = 0; i < (int)current.size() - 1; i++) {
    vector<long long> next_state;
    
    // Build the next array state
    for (int j = 0; j <= i; j++) next_state.push_back(current[j]);
    next_state.push_back(current[i] + current[i+1]); // The sum operation
    for (int j = i + 1; j < (int)current.size(); j++) next_state.push_back(current[j]);

    // Recurse
    if (canTransform(next_state, target, m)) return true;
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  if (!(cin >> n >> m)) return 0;

  vector<long long> a(n), b(m);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];

  // For Subtask 1, m < n is an immediate NO
  if (m < n) {
    cout << "NO" << endl;
    return 0;
  }

  if (canTransform(a, b, m)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}