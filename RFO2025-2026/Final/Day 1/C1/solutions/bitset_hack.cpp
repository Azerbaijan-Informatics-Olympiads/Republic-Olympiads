#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

int n, q, k;
bitset<200005> bs[10];
bitset<200005> mask_ones;

int main() {
    if (!(cin >> n >> q >> k)) return 0;
    
    // Create a bitset of all 1s
    mask_ones.set();
    
    // Read initial array into the K bitsets
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        bs[val].set(i);
    }
    
    for (int i = 0; i < q; i++) {
        int type, l, r;
        cin >> type >> l >> r;
        
        if (type == 1) {
            // Create a mask with 1s only in the range [l, r]
            bitset<200005> mask = (mask_ones << l) ^ (mask_ones << (r + 1));
            
            // Extract the bits in the current range
            bitset<200005> extracted[10];
            for (int s = 0; s < k; s++) {
                extracted[s] = bs[s] & mask;
            }
            
            // Shift everything up by 1 modulo K
            for (int s = 0; s < k; s++) {
                bs[(s + 1) % k] = (bs[(s + 1) % k] & ~mask) | extracted[s];
            }
            
        } else {
            if (l == r) {
                cout << 0 << "\n";
                continue;
            }
            
            // For a query [l, r], we only check left-side pairs up to r - 1
            bitset<200005> mask = (mask_ones << l) ^ (mask_ones << r);
            int ans = 0;
            
            // Pre-calculate right-shifted bitsets to align element (i+1) with element (i)
            bitset<200005> shifted[10];
            for (int s = 0; s < k; s++) {
                shifted[s] = bs[s] >> 1;
            }
            
            // Count pairs where A[i] = u and A[i+1] = v (where u < v)
            for (int u = 0; u < k; u++) {
                bitset<200005> active_u = bs[u] & mask;
                
                if (active_u.none()) continue; // Tiny optimization
                
                for (int v = u + 1; v < k; v++) {
                    ans += (active_u & shifted[v]).count();
                }
            }
            
            cout << ans << "\n";
        }
    }
    
    return 0;
}