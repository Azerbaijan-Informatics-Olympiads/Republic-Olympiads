#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, d;
    cin >> n >> d;
    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    sort(s.begin(), s.end());
    int max_range = 0;
    int l = 0, r = 0;
    while(l < n) {
        while(r < n && s[r] - s[l] <= d) {
            max_range = max(max_range, r - l + 1);
            ++r;
        }
        ++l;
    }
    cout << max_range << '\n';
}
int main() {
    solve();
    return 0;
}
