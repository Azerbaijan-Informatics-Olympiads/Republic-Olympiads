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
 
    int dp[n + 1][4], pref[n + 1][4];
    for(int i = 0; i <= n; i++){
        for(int j = 1; j <= 3; j++){
            dp[i][j] = -inf;
            pref[i][j] = -inf;
        }
    }
 
    for(int j = 1; j <= 3; j++) dp[0][j] = pref[0][j] = 0;
 
    int last1 = 0, last3 = 0, lastNot1 = 0, lastNot3 = 0;
 
    for(int i = 1; i <= n; i++){
        if(a[i] == 1) last1 = i;
        if(a[i] == 3) last3 = i;
        if(a[i] != 1) lastNot1 = i;
        if(a[i] != 3) lastNot3 = i;
 
        if(last1){
            int lim = last1 - 1;
            dp[i][1] = max(dp[i][1], max(pref[lim][1], pref[lim][2]) + 1);
        }
 
        if(last3){
            int lim = last3 - 1;
            dp[i][3] = max(dp[i][3], max(pref[lim][2], pref[lim][3]) + 1);
        }
 
        int lim = min(lastNot1, lastNot3) - 1;
        if(lim >= 0){
            dp[i][2] = max(dp[i][2], max({pref[lim][1], pref[lim][2], pref[lim][3]}) + 1);
        }
 
        for(int j = 1; j <= 3; j++)
            pref[i][j] = max(pref[i - 1][j], dp[i][j]);
    }
 
    cout << n - max({dp[n][1], dp[n][2], dp[n][3]}) << '\n';
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}