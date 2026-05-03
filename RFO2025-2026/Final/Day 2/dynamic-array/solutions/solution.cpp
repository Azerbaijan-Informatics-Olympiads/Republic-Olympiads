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
    ll n, m;
    cin >> n >> m;
    ll a[n], b[m];
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    for (ll i = 0; i < m; i++)
        cin >> b[i];
    bool ok[m];
    for (ll i = 0; i < m; i++)
        ok[i] = true;
    ll i = 0;
    set<pair<ll, ll>> s;
    vector<pair<ll, ll>> c;
    for (ll j = 0; j < m; j++)
    {
        s.insert(make_pair(j, b[j]));
        if (i < n and b[j] == a[i])
        i++, ok[j] = false;
        if (ok[j])
            c.push_back(make_pair(b[j], j));
    }
    if (i < n)
    {
        cout << "NO\n";
        return;
    }
    sort(c.begin(), c.end(), greater());
    for (auto [mx, ind] : c)
    {
        s.erase(make_pair(ind, mx));
        auto ub = s.upper_bound(make_pair(ind, 1e18));
        auto lb = s.lower_bound(make_pair(ind, -1));
        if (lb == s.begin() or ub == s.end())
        {
            cout << "NO\n";
            return;
        }
        lb--;
        if (lb->second + ub->second != mx)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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