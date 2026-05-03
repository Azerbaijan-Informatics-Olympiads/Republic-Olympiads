#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T, typename key = less<T>>
using ordered_set = tree<T, null_type, key, rb_tree_tag, tree_order_statistics_node_update>;

void solve()
{
    ll n;
    cin >> n;
    ll a[n + 1];
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    ll dp[n + 1][n + 1];
    for (ll i = 0; i <= n; i++)
        dp[0][i] = 0;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= n; j++)
            dp[i][j] = dp[i - 1][j];
        dp[i][a[i]]++;
        if (a[i] - 1 > 0)
            dp[i][a[i]] = max(dp[i - 1][a[i] - 1] + 1, dp[i][a[i]]);
        if (a[i] + 1 <= n)
            dp[i][a[i]] = max(dp[i - 1][a[i] + 1] + 1, dp[i][a[i]]);
        ll l = a[i], r = a[i];
        for (ll j = i - 1; j >= 1; j--)
        {
            if (a[j] < l)
            {
                for (ll x = a[j]; x < l; x++)
                {
                    if (x - 1 > 0)
                        dp[i][x] = max(dp[j - 1][x - 1] + 1, dp[i][x]);
                    if (x + 1 <= n)
                        dp[i][x] = max(dp[j - 1][x + 1] + 1, dp[i][x]);
                    dp[i][x] = max(dp[i][x], dp[j - 1][x] + 1);
                }
                l = a[j];
            }
            else if (a[j] > r)
            {
                for (ll x = r + 1; x <= a[j]; x++)
                {
                    if (x - 1 > 0)
                        dp[i][x] = max(dp[j - 1][x - 1] + 1, dp[i][x]);
                    if (x + 1 <= n)
                        dp[i][x] = max(dp[j - 1][x + 1] + 1, dp[i][x]);
                    dp[i][x] = max(dp[i][x], dp[j - 1][x] + 1);
                }
                r = a[j];
            }
        }
    }
    ll ans = n + 1;
    for (ll i = 1; i <= n; i++)
        ans = min(ans, n - dp[n][i]);
    cout << ans << endl;
}
/*


*/
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t = 1;
    // precomp();
    // cin >> t;
    for (ll cs = 1; cs <= t; cs++)
        solve();
    // cerr << "\nTime elapsed: " << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n";
}