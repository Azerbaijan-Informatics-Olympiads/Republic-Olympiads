#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2e18;

// Represents a valid state in our Pareto frontier
struct State {
  int k;
  long long Max_m;
  long long Min_M;
};

// Adds a state to the frontier, filtering out strictly dominated states
void add_state(vector<State>& frontier, State s) {
  vector<State> next_frontier;
  
  for (const auto& existing : frontier) {
    // If the new state is completely dominated by an existing one, discard it
    if (existing.k >= s.k && existing.Max_m <= s.Max_m && existing.Min_M >= s.Min_M) {
      return;
    }
    // If the existing state is dominated by the new one, we drop the existing one
    // (by simply not adding it to next_frontier)
    if (s.k >= existing.k && s.Max_m <= existing.Max_m && s.Min_M >= existing.Min_M) {
      continue;
    }
    next_frontier.push_back(existing);
  }
  
  next_frontier.push_back(s);
  frontier = move(next_frontier);
}

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

  // dp[i] stores the Pareto frontier of valid states ending at index i
  vector<vector<State>> dp(n + 1);
  
  // Base case: 0 segments, infinitely permissive bottlenecks
  dp[0].push_back({0, -INF, INF});

  for (int i = 1; i <= n; ++i) {
    long long m = a[i];
    long long M = a[i];
    
    // Expand the current segment a[j+1 ... i] to the left
    for (int j = i - 1; j >= 0; --j) {
      m = min(m, a[j + 1]);
      M = max(M, a[j + 1]);

      for (const auto& prev : dp[j]) {
        int k = prev.k + 1;
        
        // 1. Check global sequence validity using the Lipschitz theorem
        if (m - k <= prev.Min_M && M + k >= prev.Max_m) {
          
          // 2. Compute the new running bottlenecks for the sequence
          long long new_Max_m = max(prev.Max_m, m + k);
          long long new_Min_M = min(prev.Min_M, M - k);

          // 3. Ensure the current segment has a valid mathematical intersection
          if (new_Max_m - k <= new_Min_M + k) {
            add_state(dp[i], {k, new_Max_m, new_Min_M});
          }
        }
      }
    }
  }

  // Find the maximum segments k we could form for the entire array
  int max_k = 0;
  for (const auto& s : dp[n]) {
    max_k = max(max_k, s.k);
  }

  // Minimum operations is the total elements minus the number of remaining buckets
  cout << n - max_k << "\n";

  return 0;
}