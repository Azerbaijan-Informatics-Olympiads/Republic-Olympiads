#include <bits/stdc++.h>

using namespace std;

const int S = 450; // Block size
int n, q, k;
vector<int> a;
vector<int> block_shift;       // Tracks the +1 shifts applied to a whole block
vector<vector<int>> block_ans; // block_ans[b][s] = harmonious pairs in block 'b' if shifted by 's'

// Gets the true value of element i by adding its block's shift
inline int val(int i) {
    return (a[i] + block_shift[i / S]) % k;
}

// Recalculates the internal answers for a single block
void rebuild_block(int b) {
    int l = b * S;
    int r = min(n, l + S);
    fill(block_ans[b].begin(), block_ans[b].end(), 0);
    
    for (int i = l; i < r - 1; ++i) {
        for (int s = 0; s < k; ++s) {
            if ((a[i] + s) % k < (a[i + 1] + s) % k) {
                block_ans[b][s]++;
            }
        }
    }
}

// Applies the block's shift to its individual elements before a partial update
void flatten_block(int b) {
    if (block_shift[b] == 0) return;
    int l = b * S;
    int r = min(n, l + S);
    for (int i = l; i < r; ++i) {
        a[i] = (a[i] + block_shift[b]) % k;
    }
    block_shift[b] = 0;
}

void update(int l, int r) {
    int b_l = l / S;
    int b_r = r / S;

    if (b_l == b_r) {
        // Entire update is within a single block
        flatten_block(b_l);
        for (int i = l; i <= r; ++i) a[i] = (a[i] + 1) % k;
        rebuild_block(b_l);
    } else {
        // Update left boundary
        flatten_block(b_l);
        for (int i = l; i < (b_l + 1) * S; ++i) a[i] = (a[i] + 1) % k;
        rebuild_block(b_l);

        // Update middle blocks in O(1)
        for (int b = b_l + 1; b < b_r; ++b) {
            block_shift[b] = (block_shift[b] + 1) % k;
        }

        // Update right boundary
        flatten_block(b_r);
        for (int i = b_r * S; i <= r; ++i) a[i] = (a[i] + 1) % k;
        rebuild_block(b_r);
    }
}

int query(int l, int r) {
    if (l == r) return 0;
    int b_l = l / S;
    int b_r = r / S;
    int res = 0;

    if (b_l == b_r) {
        // Entire query is within a single block
        for (int i = l; i < r; ++i) {
            if (val(i) < val(i + 1)) res++;
        }
    } else {
        // Query left boundary
        for (int i = l; i < (b_l + 1) * S - 1; ++i) {
            if (val(i) < val(i + 1)) res++;
        }
        
        // Count pair spanning left block and first middle block
        if (val((b_l + 1) * S - 1) < val((b_l + 1) * S)) res++;

        // Query middle blocks in O(1)
        for (int b = b_l + 1; b < b_r; ++b) {
            res += block_ans[b][block_shift[b]];
            // Count pair spanning this block and the next block
            if (val((b + 1) * S - 1) < val((b + 1) * S)) res++;
        }

        // Query right boundary
        for (int i = b_r * S; i < r; ++i) {
            if (val(i) < val(i + 1)) res++;
        }
    }
    return res;
}

int main() {
    if (!(cin >> n >> q >> k)) return 0;
    
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int num_blocks = (n + S - 1) / S;
    block_shift.assign(num_blocks, 0);
    block_ans.assign(num_blocks, vector<int>(k, 0));

    // Initial build for all blocks
    for (int b = 0; b < num_blocks; ++b) {
        rebuild_block(b);
    }

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;
        l--; r--; // Convert to 0-indexed for array operations
        
        if (type == 1) {
            update(l, r);
        } else {
            cout << query(l, r) << "\n";
        }
    }
    return 0;
}