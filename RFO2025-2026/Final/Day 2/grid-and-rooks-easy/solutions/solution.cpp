#include <bits/stdc++.h>
using namespace std;


void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    int r[k], c[k];
    for (int i = 0; i < k; i++) cin >> r[i] >> c[i];
    int ans = n + m - 2;
    for (int i = 0; i < k; i++) ans = min(ans, r[i] + c[i] - 2 + (r[i] != n) + (c[i] != m));
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    for (int cs = 1; cs <= t; cs++)
        solve();
}