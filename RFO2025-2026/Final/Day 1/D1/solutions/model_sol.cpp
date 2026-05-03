#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;
const int mod = 1e9 + 7, MAX = 5005;
int dp[MAX][MAX], s[MAX][MAX], p[MAX][MAX];

void solve() {
    int n;
    cin >> n;
    int a[n + 1];
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) dp[0][i] = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dp[i][j] = -inf;

    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= n; j++){
            if(i == n) p[i][j] = n + 1, s[i][j] = n + 1;
            else p[i][j] = p[i + 1][j], s[i][j] = s[i + 1][j];
        }
        p[i][a[i]] = i;
        s[i][a[i]] = i;
        for(int j = n - 1; j >= 1; j--) s[i][j] = min(s[i][j], s[i][j + 1]);
        for(int j = 2; j <= n; j++) p[i][j] = min(p[i][j], p[i][j - 1]);
    }

    for(int i = 0; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if(i == n) break;
        int nw[n + 1];
        for(int j = 1; j <= n; j++){
            nw[j] = -inf;
            for(int k = j - 1; k <= j + 1; k++){
                if(1 <= k && k <= n)
                    nw[j] = max(nw[j], dp[i][k]);
            }
        }

        for(int j = 1; j <= n; j++){
            int r = max(p[i + 1][j], s[i + 1][j]);
            if(r == n + 1) continue;
            dp[r][j] = max(dp[r][j], nw[j] + 1);
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