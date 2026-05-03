#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;

// A state represents a valid configuration at a given prefix
struct State {
  int len; // Number of segments formed so far
  int L;   // Minimum valid intensity for the last segment
  int R;   // Maximum valid intensity for the last segment
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n)) return 0;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  // dp[i] stores the Pareto frontier of valid states for prefix i
  vector<vector<State>> dp(n + 1);
  
  // Base case: 0 segments, infinitely permissive bounds
  dp[0].push_back({0, -INF, INF});

  for (int i = 1; i <= n; ++i) {
    vector<State> candidates;
    int m = a[i];
    int M = a[i];

    // Iterate backwards to define the current segment a[j+1 ... i]
    for (int j = i - 1; j >= 0; --j) {
      m = min(m, a[j + 1]);
      M = max(M, a[j + 1]);

      // Attempt to extend every valid state from the previous boundary j
      for (const auto& prev : dp[j]) {
        // Expand previous bounds by 1 to satisfy |x_i - x_{i+1}| <= 1
        int exp_L = (prev.L == -INF) ? -INF : prev.L - 1;
        int exp_R = (prev.R == INF) ? INF : prev.R + 1;

        // The intersection of the expanded previous bounds and current internal bounds
        int new_L = max(m, exp_L);
        int new_R = min(M, exp_R);

        if (new_L <= new_R) {
          candidates.push_back({prev.len + 1, new_L, new_R});
        }
      }
    }

    // 1. Sort candidates: primary by len (descending), secondary by L (ascending)
    sort(candidates.begin(), candidates.end(), [](const State& a, const State& b) {
      if (a.len != b.len) return a.len > b.len;
      if (a.L != b.L) return a.L < b.L;
      return a.R < b.R;
    });

    // 2. Merge overlapping or touching intervals that have the SAME length
    vector<State> merged;
    for (const auto& cand : candidates) {
      if (merged.empty()) {
        merged.push_back(cand);
      } else {
        // If same length and intervals touch/overlap (e.g., [0, 4] and [5, 6])
        if (merged.back().len == cand.len && merged.back().R + 1 >= cand.L) {
          merged.back().R = max(merged.back().R, cand.R);
        } else {
          merged.push_back(cand);
        }
      }
    }

    // 3. Filter dominated states to construct the Pareto frontier for dp[i]
    for (const auto& cand : merged) {
      bool dominated = false;
      for (const auto& dom : dp[i]) {
        // Since we process in len descending order, dom.len is guaranteed >= cand.len
        // If the existing state's interval completely covers the candidate, drop candidate
        if (dom.L <= cand.L && dom.R >= cand.R) {
          dominated = true;
          break;
        }
      }
      if (!dominated) {
        dp[i].push_back(cand);
      }
    }
  }

  // Find the maximum segments we could form globally
  int max_k = 0;
  for (const auto& state : dp[n]) {
    max_k = max(max_k, state.len);
  }

  cout << n - max_k << "\n";

  return 0;
}