#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<pii>coins(q);
    for(int i = 0; i < q; ++i) {
        cin >> coins[i].x >> coins[i].y;
    }
    sort(coins.begin(), coins.end());
    multiset<int>ys;
    ys.insert(coins[0].y);
    for(int i = 1; i < q; ++i) {
        auto itr = ys.upper_bound(coins[i].y);
        if(itr != ys.begin()) {
            --itr;
            ys.erase(itr);
        }
        ys.insert(coins[i].y);
    }
    cout << (int)ys.size() << '\n';
}
int main() {
    solve();
    return 0;
}
