#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main() {
  int n;
  cin >> n;
  
  vector<long long> p2(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    p2[i] = (p2[i - 1] * 2) % MOD;
  }
  
  long long ans = 0;
  for (long long k = 1; k <= n; ++k) {
    long long subsets = p2[n - k];
    long long contribution = (k * subsets) % MOD;
    ans = (ans + contribution) % MOD;
  }
  
  cout << ans << "\n";
  return 0;
}