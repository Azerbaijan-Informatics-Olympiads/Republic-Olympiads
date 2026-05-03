#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
vector<int> a;

bool stable(vector<int> b) {
    for(int i = 0; i + 1 < (int)b.size(); i++) {
        if(abs(b[i] - b[i + 1]) > 1) return false;
    }
    return true;
}

int run_greedy(vector<int> b, int firstEnd, bool lookahead) {
    int n = b.size();

    vector<int> sufMin(n + 1, INF), sufMax(n + 1, -INF);
    for(int i = n - 1; i >= 0; i--) {
        sufMin[i] = min(sufMin[i + 1], b[i]);
        sufMax[i] = max(sufMax[i + 1], b[i]);
    }

    int L = INF, R = -INF;
    for(int i = 0; i <= firstEnd; i++) {
        L = min(L, b[i]);
        R = max(R, b[i]);
    }

    int blocks = 1;
    int pos = firstEnd + 1;

    while(pos < n) {
        int mn = INF, mx = -INF;
        bool found = false;

        for(int r = pos; r < n; r++) {
            mn = min(mn, b[r]);
            mx = max(mx, b[r]);

            int nL = max(mn, L - 1);
            int nR = min(mx, R + 1);

            if(nL <= nR) {
                bool ok = true;

                if(lookahead && r + 1 < n) {
                    ok = (sufMin[r + 1] <= nR + 1 && sufMax[r + 1] >= nL - 1);
                }

                if(ok) {
                    L = nL;
                    R = nR;
                    blocks++;
                    pos = r + 1;
                    found = true;
                    break;
                }
            }
        }

        if(!found) {
            // Greedy gives up separating the suffix.
            // Think of the remaining suffix as absorbed into the last block.
            break;
        }
    }

    return n - blocks;
}

int greedy_solution(vector<int> b) {
    int n = b.size();
    int ans = n - 1;

    for(int firstEnd = 0; firstEnd < n; firstEnd++) {
        ans = min(ans, run_greedy(b, firstEnd, false));
        ans = min(ans, run_greedy(b, firstEnd, true));
    }

    reverse(b.begin(), b.end());

    for(int firstEnd = 0; firstEnd < n; firstEnd++) {
        ans = min(ans, run_greedy(b, firstEnd, false));
        ans = min(ans, run_greedy(b, firstEnd, true));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    cout << greedy_solution(a) << '\n';
}