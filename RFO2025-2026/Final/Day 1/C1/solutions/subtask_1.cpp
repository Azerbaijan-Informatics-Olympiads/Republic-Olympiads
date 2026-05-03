#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>

using namespace std;

const int MAXN = 200005;
int a[MAXN];

int main() {
    // Fast I/O is critical for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, k;
    if (!(cin >> n >> q >> k)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1) {
            // Update without using the slow modulo (%) operator
            for (int j = l; j <= r; ++j) {
                a[j]++;
                if (a[j] == k) {
                    a[j] = 0;
                }
            }
        } else {
            if (l == r) {
                cout << 0 << "\n";
            } else {
                int ans = 0;
                // Query loop is simple enough for the compiler to auto-vectorize
                for (int j = l; j < r; ++j) {
                    if (a[j] < a[j + 1]) {
                        ans++;
                    }
                }
                cout << ans << "\n";
            }
        }
    }

    return 0;
}