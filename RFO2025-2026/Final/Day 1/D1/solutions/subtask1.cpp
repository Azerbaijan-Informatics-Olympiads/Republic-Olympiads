#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

map<vector<int>, int> dp;

bool good(vector<int> a) {
    for(int i = 0; i + 1 < (int)a.size(); i++) {
        if(abs(a[i] - a[i + 1]) > 1) return false;
    }
    return true;
}

int solve(vector<int> a) {
    if(good(a)) return 0;
    if(dp.count(a)) return dp[a];

    int ans = INF;
    int m = a.size();

    for(int i = 0; i + 1 < m; i++) {
        int l = min(a[i], a[i + 1]);
        int r = max(a[i], a[i + 1]);

        for(int x = l; x <= r; x++) {
            vector<int> b;

            for(int j = 0; j < i; j++) b.push_back(a[j]);
            b.push_back(x);
            for(int j = i + 2; j < m; j++) b.push_back(a[j]);

            ans = min(ans, solve(b) + 1);
        }
    }

    return dp[a] = ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    cout << solve(a) << '\n';
}