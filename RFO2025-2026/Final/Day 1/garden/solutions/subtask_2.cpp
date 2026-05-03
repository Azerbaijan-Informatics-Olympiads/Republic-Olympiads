#include <bits/stdc++.h>

using namespace std;

int main() {

    int n, q, k;
    if (!(cin >> n >> q >> k)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Precompute prefix sums of harmonious pairs
    vector<int> pref(n + 1, 0);
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i - 1];
        if (a[i] < a[i + 1]) {
            pref[i]++;
        }
    }

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;
        
        if (type == 2) {
            if (l == r) {
                cout << 0 << "\n";
            } else {
                cout << pref[r - 1] - pref[l - 1] << "\n";
            }
        }
        // We explicitly ignore type 1 queries because subtask 2 guarantees they do not exist
    }

    return 0;
}