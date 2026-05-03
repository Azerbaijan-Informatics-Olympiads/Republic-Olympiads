#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    if (m < n) {
        cout << "NO\n";
        return 0;
    }

    // 1) Greedily match a as a subsequence of b -> mark "kept" positions
    vector<char> keep(m, 0);
    int p = 0;
    for (int i = 0; i < m && p < n; i++) {
        if (b[i] == a[p]) {
            keep[i] = 1;
            p++;
        }
    }
    if (p < n) {
        cout << "NO\n";
        return 0;
    }

    // 2) Reverse-reduction with a stack, never deleting kept elements
    // Stack items: (value, is_kept)
    vector<pair<long long, char>> st;
    st.reserve(m);

    auto try_reduce = [&]() {
        while ((int)st.size() >= 3) {
            auto [x, kx] = st[(int)st.size() - 3];
            auto [s, ks] = st[(int)st.size() - 2];
            auto [y, ky] = st[(int)st.size() - 1];
            if (!ks && s == x + y) {
                // delete the middle one
                st.erase(st.end() - 2);
            } else break;
        }
    };

    for (int i = 0; i < m; i++) {
        st.push_back({b[i], keep[i]});
        try_reduce();
    }

    // Final check: must equal a, and everything must be kept
    if ((int)st.size() != n) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (!st[i].second || st[i].first != a[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}