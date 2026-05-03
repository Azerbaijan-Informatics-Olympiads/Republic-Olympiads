#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int SZ = n + 1;

    auto id = [&](int l, int r, int x) {
        return ((long long)l * SZ + r) * SZ + x;
    };

    vector<unsigned char> can((long long)SZ * SZ * SZ, 0);

    for(int l = 1; l <= n; l++) {
        int mn = n + 1, mx = 0;

        for(int r = l; r <= n; r++) {
            mn = min(mn, a[r]);
            mx = max(mx, a[r]);

            for(int x = 1; x <= n; x++) {
                if(mn <= x && x <= mx) {
                    can[id(l, r, x)] = 1;
                }
            }
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -INF));

    for(int x = 1; x <= n; x++) {
        dp[0][x] = 0;
    }

    for(int r = 1; r <= n; r++) {
        for(int l = 1; l <= r; l++) {
            for(int x = 1; x <= n; x++) {
                if(!can[id(l, r, x)]) continue;

                int best = dp[l - 1][x];

                if(x > 1) best = max(best, dp[l - 1][x - 1]);
                if(x < n) best = max(best, dp[l - 1][x + 1]);

                if(best != -INF) {
                    dp[r][x] = max(dp[r][x], best + 1);
                }
            }
        }
    }

    int best = 0;
    for(int x = 1; x <= n; x++) {
        best = max(best, dp[n][x]);
    }

    cout << n - best << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}