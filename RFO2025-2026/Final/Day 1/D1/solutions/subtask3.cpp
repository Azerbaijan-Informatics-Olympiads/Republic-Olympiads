#include <bits/stdc++.h>
using namespace std;

bool possible(vector<pair<int,int>> blocks) {
    int L = blocks[0].first;
    int R = blocks[0].second;

    for(int i = 1; i < (int)blocks.size(); i++) {
        int nL = max(blocks[i].first, L - 1);
        int nR = min(blocks[i].second, R + 1);

        if(nL > nR) return false;

        L = nL;
        R = nR;
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int ans = n - 1;

    for(int mask = 0; mask < (1 << (n - 1)); mask++) {
        vector<pair<int,int>> blocks;

        int mn = a[0];
        int mx = a[0];

        for(int i = 0; i < n - 1; i++) {
            if(mask & (1 << i)) {
                blocks.push_back({mn, mx});
                mn = a[i + 1];
                mx = a[i + 1];
            } else {
                mn = min(mn, a[i + 1]);
                mx = max(mx, a[i + 1]);
            }
        }

        blocks.push_back({mn, mx});

        if(possible(blocks)) {
            int cnt = blocks.size();
            ans = min(ans, n - cnt);
        }
    }

    cout << ans << '\n';
}