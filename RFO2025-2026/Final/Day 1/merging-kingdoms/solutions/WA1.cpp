#pragma GCC optimize ("O3")
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2e18;

struct Interval {
  long long l, r;
};

int main() {
  // Optimize standard I/O operations for performance
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n)) return 0;

  vector<long long> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // dp[i] stores the max segments for prefix 1...i
  vector<int> dp(n + 1, -1);
  
  // intervals[i] stores the union of valid ranges for the max dp[i]
  vector<vector<Interval>> intervals(n + 1);

  dp[0] = 0;
  intervals[0] = {{-INF, INF}}; // Base case can take any value

  for (int i = 1; i <= n; ++i) {
    long long m = a[i];
    long long M = a[i];
    
    for (int j = i - 1; j >= 0; --j) {
      m = min(m, a[j + 1]);
      M = max(M, a[j + 1]);

      if (dp[j] == -1) continue;

      // Check all valid intervals from the optimal state at j
      for (const auto& prev : intervals[j]) {
        long long L = prev.l;
        long long R = prev.r;

        // Expand previous valid range by 1 on both sides to account for |x_i - x_{i+1}| <= 1
        long long exp_L = (L == -INF) ? -INF : L - 1;
        long long exp_R = (R == INF) ? INF : R + 1;

        // The new segment intensity must be in the intersection of the expanded 
        // previous range and the current segment's internal min/max bounds
        long long new_L = max(m, exp_L);
        long long new_R = min(M, exp_R);

        if (new_L <= new_R) { // If the intersection is valid
          if (dp[j] + 1 > dp[i]) {
            // Found a strictly better k, discard previous intervals
            dp[i] = dp[j] + 1;
            intervals[i].clear();
            intervals[i].push_back({new_L, new_R});
          } else if (dp[j] + 1 == dp[i]) {
            // Found another path to the same max k, add the interval to the pool
            intervals[i].push_back({new_L, new_R});
          }
        }
      }
    }

    // Merge overlapping intervals to keep the state clean and minimal
    if (!intervals[i].empty()) {
      sort(intervals[i].begin(), intervals[i].end(), [](const Interval& x, const Interval& y) {
        return x.l < y.l;
      });
      
      vector<Interval> merged;
      merged.push_back(intervals[i][0]);
      for (size_t k = 1; k < intervals[i].size(); ++k) {
        if (intervals[i][k].l <= merged.back().r) {
          merged.back().r = max(merged.back().r, intervals[i][k].r);
        } else {
          merged.push_back(intervals[i][k]);
        }
      }
      intervals[i] = merged;
    }
  }

  // The minimum operations needed is the total elements minus the max segments
  cout << n - dp[n] << "\n";

  return 0;
}