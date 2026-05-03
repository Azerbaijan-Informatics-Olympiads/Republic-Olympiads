#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  // Optimize standard I/O operations
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n)) return 0;

  vector<long long> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // dp[i][j] = max segments for prefix 1...i, where the last segment is a[j+1...i]
  // Initialize to -1 to represent unreachable states
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

  // Base case
  dp[0][0] = 0; 

  for (int i = 1; i <= n; ++i) {
    long long m2 = a[i];
    long long M2 = a[i];
    
    // j is the start of the current segment (segment is j+1 ... i)
    for (int j = i - 1; j >= 0; --j) {
      m2 = min(m2, a[j + 1]);
      M2 = max(M2, a[j + 1]);

      if (j == 0) {
        // The entire prefix is taken as one single segment
        dp[i][0] = 1;
        continue;
      }

      long long m1 = a[j];
      long long M1 = a[j];
      
      // p is the start of the previous segment (segment is p+1 ... j)
      for (int p = j - 1; p >= 0; --p) {
        m1 = min(m1, a[p + 1]);
        M1 = max(M1, a[p + 1]);

        // If the previous state is valid, try to transition
        if (dp[j][p] != -1) {
          
          // THE FATAL FLAW: 
          // We only check local overlap between the current segment [m2, M2]
          // and the immediate previous segment [m1, M1]. 
          // We assume M1 can be anything in its range, completely ignoring 
          // that it might be heavily restricted by the segment before it!
          long long overlap_L = max(m1, m2 - 1);
          long long overlap_R = min(M1, M2 + 1);

          if (overlap_L <= overlap_R) { // Local overlap exists
            dp[i][j] = max(dp[i][j], dp[j][p] + 1);
          }
        }
      }
    }
  }

  // Find the maximum segments we could form
  int max_k = 0;
  for (int j = 0; j < n; ++j) {
    max_k = max(max_k, dp[n][j]);
  }

  cout << n - max_k << "\n";

  return 0;
}