#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <cstdint> // For int8_t

using namespace std;

const int MAXN = 200005;

// The array is 8-bit to force maximum SIMD packing (32 elements per cycle)
int8_t a[MAXN]; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, k;
    if (!(cin >> n >> q >> k)) return 0;

    for (int i = 1; i <= n; ++i) {
        int temp;
        cin >> temp;
        a[i] = temp;
    }

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1) {
            // Update loop optimized to avoid branching if possible
            int8_t limit = k - 1;
            for (int j = l; j <= r; ++j) {
                a[j] = (a[j] == limit) ? 0 : a[j] + 1;
            }
        } else {
            if (l == r) {
                cout << 0 << "\n";
            } else {
                // The accumulator is 32-bit to prevent WA overflow
                int ans = 0; 
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