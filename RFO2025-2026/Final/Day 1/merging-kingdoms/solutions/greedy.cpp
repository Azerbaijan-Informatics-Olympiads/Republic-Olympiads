#include <bits/stdc++.h>
using namespace std;

static bool beautiful(const vector<int>& a) {
    for (int i = 0; i + 1 < (int)a.size(); i++) {
        if (abs(a[i] - a[i + 1]) > 1) return false;
    }
    return true;
}

static int bad_edges(const vector<int>& a) {
    int cnt = 0;
    for (int i = 0; i + 1 < (int)a.size(); i++) {
        if (abs(a[i] - a[i + 1]) > 1) cnt++;
    }
    return cnt;
}

static vector<int> merge_at(const vector<int>& a, int i, int x) {
    vector<int> b;
    b.reserve((int)a.size() - 1);
    for (int j = 0; j < i; j++) b.push_back(a[j]);
    b.push_back(x);
    for (int j = i + 2; j < (int)a.size(); j++) b.push_back(a[j]);
    return b;
}

static int clamp_mid(int l, int r) {
    return (l + r) / 2;
}

static int run_first_bad_midpoint(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int pos = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            if (abs(a[i] - a[i + 1]) > 1) {
                pos = i;
                break;
            }
        }
        if (pos == -1) break;
        int l = min(a[pos], a[pos + 1]);
        int r = max(a[pos], a[pos + 1]);
        int x = clamp_mid(l, r);
        a = merge_at(a, pos, x);
        ops++;
    }
    return ops;
}

static int run_first_bad_min(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int pos = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            if (abs(a[i] - a[i + 1]) > 1) {
                pos = i;
                break;
            }
        }
        if (pos == -1) break;
        int x = min(a[pos], a[pos + 1]);
        a = merge_at(a, pos, x);
        ops++;
    }
    return ops;
}

static int run_first_bad_max(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int pos = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            if (abs(a[i] - a[i + 1]) > 1) {
                pos = i;
                break;
            }
        }
        if (pos == -1) break;
        int x = max(a[pos], a[pos + 1]);
        a = merge_at(a, pos, x);
        ops++;
    }
    return ops;
}

static int run_largest_bad_midpoint(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int pos = -1, best = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            int d = abs(a[i] - a[i + 1]);
            if (d > 1 && d > best) {
                best = d;
                pos = i;
            }
        }
        if (pos == -1) break;
        int l = min(a[pos], a[pos + 1]);
        int r = max(a[pos], a[pos + 1]);
        int x = clamp_mid(l, r);
        a = merge_at(a, pos, x);
        ops++;
    }
    return ops;
}

static int run_largest_bad_min(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int pos = -1, best = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            int d = abs(a[i] - a[i + 1]);
            if (d > 1 && d > best) {
                best = d;
                pos = i;
            }
        }
        if (pos == -1) break;
        int x = min(a[pos], a[pos + 1]);
        a = merge_at(a, pos, x);
        ops++;
    }
    return ops;
}

static int run_largest_bad_max(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int pos = -1, best = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            int d = abs(a[i] - a[i + 1]);
            if (d > 1 && d > best) {
                best = d;
                pos = i;
            }
        }
        if (pos == -1) break;
        int x = max(a[pos], a[pos + 1]);
        a = merge_at(a, pos, x);
        ops++;
    }
    return ops;
}

// Choose the move that minimizes the number of bad edges after one operation.
// Ties: fewer resulting max diff, then earliest pair, then smaller x.
static int run_best_local_move(vector<int> a) {
    int ops = 0;
    while (!beautiful(a)) {
        int bestBad = (int)1e9;
        int bestMaxDiff = (int)1e9;
        int bestPos = -1;
        int bestX = -1;
        vector<int> bestArr;

        for (int i = 0; i + 1 < (int)a.size(); i++) {
            int l = min(a[i], a[i + 1]);
            int r = max(a[i], a[i + 1]);
            for (int x = l; x <= r; x++) {
                vector<int> b = merge_at(a, i, x);
                int bbad = bad_edges(b);
                int mx = 0;
                for (int j = 0; j + 1 < (int)b.size(); j++) {
                    mx = max(mx, abs(b[j] - b[j + 1]));
                }
                if (bbad < bestBad ||
                    (bbad == bestBad && mx < bestMaxDiff) ||
                    (bbad == bestBad && mx == bestMaxDiff && i < bestPos) ||
                    (bbad == bestBad && mx == bestMaxDiff && i == bestPos && x < bestX)) {
                    bestBad = bbad;
                    bestMaxDiff = mx;
                    bestPos = i;
                    bestX = x;
                    bestArr = move(b);
                }
            }
        }

        if (bestPos == -1) break;
        a = move(bestArr);
        ops++;
    }
    return ops;
}

// bogus formula-like baselines
static int heuristic_bad_edges(const vector<int>& a) {
    return bad_edges(a);
}

static int heuristic_half_bad_edges(const vector<int>& a) {
    return (bad_edges(a) + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << min({run_first_bad_midpoint(a),
            run_first_bad_min(a),
            run_first_bad_max(a),
            run_largest_bad_midpoint(a),
            run_largest_bad_min(a),
            run_largest_bad_max(a),
            run_best_local_move(a),
            heuristic_bad_edges(a),
            heuristic_half_bad_edges(a)});
    return 0;
}