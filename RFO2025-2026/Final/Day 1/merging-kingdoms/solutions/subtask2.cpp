#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

map<vector<pair<int,int>>, int> dp;

bool possible(vector<pair<int,int>> v) {
    int L = v[0].first;
    int R = v[0].second;

    for(int i = 1; i < (int)v.size(); i++) {
        int nL = max(v[i].first, L - 1);
        int nR = min(v[i].second, R + 1);

        if(nL > nR) return false;

        L = nL;
        R = nR;
    }

    return true;
}

int solve(vector<pair<int,int>> v) {
    if(possible(v)) return 0;
    if(dp.count(v)) return dp[v];

    int ans = INF;
    int m = v.size();

    for(int i = 0; i + 1 < m; i++) {
        vector<pair<int,int>> nxt;

        for(int j = 0; j < i; j++) nxt.push_back(v[j]);

        int L = min(v[i].first, v[i + 1].first);
        int R = max(v[i].second, v[i + 1].second);
        nxt.push_back({L, R});

        for(int j = i + 2; j < m; j++) nxt.push_back(v[j]);

        ans = min(ans, solve(nxt) + 1);
    }

    return dp[v] = ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v[i] = {x, x};
    }

    cout << solve(v) << '\n';
}