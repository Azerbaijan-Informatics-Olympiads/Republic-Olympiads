#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1e9 + 7, inf = 1e9 + 7, MAX = 5005;
 
int dp[MAX][MAX];
void solve() {
    int n;
    cin >> n;
    int a[n + 1];
    for(int i = 1; i <= n; i++) cin >> a[i];
 
    int lg[n + 1];
    lg[1] = 0;
    for(int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
 
    int K = lg[n] + 1;
    vector<vector<int>> mn(K, vector<int>(n + 1));
    vector<vector<int>> mx(K, vector<int>(n + 1));
 
    for(int i = 1; i <= n; i++) mn[0][i] = mx[0][i] = a[i];
 
    for(int k = 1; k < K; k++) {
        for(int i = 1; i + (1 << k) - 1 <= n; i++) {
            mn[k][i] = min(mn[k - 1][i], mn[k - 1][i + (1 << (k - 1))]);
            mx[k][i] = max(mx[k - 1][i], mx[k - 1][i + (1 << (k - 1))]);
        }
    }
 
    auto getMin = [&](int l, int r) {
        int k = lg[r - l + 1];
        return min(mn[k][l], mn[k][r - (1 << k) + 1]);
    };
 
    auto getMax = [&](int l, int r) {
        int k = lg[r - l + 1];
        return max(mx[k][l], mx[k][r - (1 << k) + 1]);
    };
 
    for(int i = 1; i <= n; i++) dp[0][i] = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dp[i][j] = -inf;
 
    for(int i = 0; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if(i == n) break;
 
        int nw[n + 1];
        for(int j = 1; j <= n; j++) {
            nw[j] = -inf;
            for(int k = j - 1; k <= j + 1; k++) {
                if(1 <= k && k <= n)
                    nw[j] = max(nw[j], dp[i][k]);
            }
        }
 
        for(int j = 1; j <= n; j++) {
            int l = i + 1, r = n, r1 = n + 1, r2 = n + 1;
 
            while(l <= r) {
                int mid = (l + r) >> 1;
                if(getMin(i + 1, mid) <= j) {
                    r1 = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
 
            l = i + 1, r = n;
            while(l <= r) {
                int mid = (l + r) >> 1;
                if(getMax(i + 1, mid) >= j) {
                    r2 = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
 
            int ans = max(r1, r2);
            if(ans == n + 1) continue;
            dp[ans][j] = max(dp[ans][j], nw[j] + 1);
        }
    }
 
    cout << n - *max_element(dp[n] + 1, dp[n] + n + 1) << '\n';
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}