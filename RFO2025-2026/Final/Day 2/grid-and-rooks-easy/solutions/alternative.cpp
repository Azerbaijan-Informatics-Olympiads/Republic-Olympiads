#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, m;
    int k;
    cin >> n >> m >> k;

    ll ans = n + m - 2;

    for (int i = 0; i < k; i++) {
        ll r, c;
        cin >> r >> c;

        ll cur = r + c - 2;

        if (r == n && c == m) {
            cur += 0;
        }
        else if (r == n || c == m) {
            cur += 1;
        }
        else {
            cur += 2;
        }

        ans = min(ans, cur);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}