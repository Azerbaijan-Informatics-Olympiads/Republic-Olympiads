#include <bits/stdc++.h>

using namespace std;

int n, q, k;
vector<int> a;
vector<int> bit;

// Adds delta to the BIT at index idx
void update(int idx, int delta) {
    if (idx <= 0 || idx >= n) return; // Only indices 1 to N-1 are valid pairs
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += delta;
    }
}

// Gets the prefix sum from 1 to idx
int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

// Checks if the pair (idx, idx+1) is harmonious
int check_pair(int idx) {
    if (idx <= 0 || idx >= n) return 0;
    return (a[idx] < a[idx + 1]) ? 1 : 0;
}

int main() {
    if (!(cin >> n >> q >> k)) return 0;

    a.resize(n + 1);
    bit.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Precalculate initial harmonious pairs
    for (int i = 1; i < n; ++i) {
        if (check_pair(i)) {
            update(i, 1);
        }
    }

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1) {
            // Subtask 3 guarantees l == r, so it's a single point update
            int idx = l;
            
            // 1. Calculate old status of adjacent pairs
            int old_left = check_pair(idx - 1);
            int old_right = check_pair(idx);

            // 2. Update the actual array element
            a[idx] = (a[idx] + 1) % k;

            // 3. Calculate new status of adjacent pairs
            int new_left = check_pair(idx - 1);
            int new_right = check_pair(idx);

            // 4. Add the difference (+1, 0, or -1) to the BIT
            update(idx - 1, new_left - old_left);
            update(idx, new_right - old_right);

        } else if (type == 2) {
            if (l == r) {
                cout << 0 << "\n";
            } else {
                // Range sum query for pairs
                cout << query(r - 1) - query(l - 1) << "\n";
            }
        }
    }

    return 0;
}