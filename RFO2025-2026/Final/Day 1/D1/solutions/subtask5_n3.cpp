#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define inf 0x3F3F3F3F3F3F3F3F
const int mod = 1e9 + 7;
 
void solve() {
    int n;
    cin >> n;
    int a[n + 1];
    for(int i = 1; i <= n; i++) cin >> a[i];
 
    int mn[n + 1][n + 1], mx[n + 1][n + 1];
    for(int i = 1; i <= n; i++){
        mn[i][i] = mx[i][i] = a[i];
        for(int j = i + 1; j <= n; j++){
            mn[i][j] = min(mn[i][j - 1], a[j]);
            mx[i][j] = max(mx[i][j - 1], a[j]);
        }
    }
 
    int dp[n + 1][n + 1];
    for(int i = 0; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = -inf;
 
    for(int j = 1; j <= n; j++) dp[0][j] = 0;
 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 0; k < i; k++){
                if(mn[k + 1][i] <= j && j <= mx[k + 1][i]){
                    for(int x = j - 1; x <= j + 1; x++){
                        if(1 <= x && x <= n)
                            dp[i][j] = max(dp[i][j], dp[k][x] + 1);
                    }
                }
            }
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