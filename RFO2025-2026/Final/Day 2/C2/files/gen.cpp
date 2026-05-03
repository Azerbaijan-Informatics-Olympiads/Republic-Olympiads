// gen.cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static inline int rndInt(int l, int r) { return rnd.next(l, r); }
static inline ll rndLL(ll l, ll r) { return rnd.next(l, r); }

static void die_fail(const string& msg) { quitf(_fail, "%s", msg.c_str()); }
static void require_or_die(bool cond, const string& msg) { if (!cond) die_fail(msg); }

static pair<bool, int> safe_random_insertion_with_pos(vector<ll>& v, vector<char>& is_orig, ll lim_b) {
    int k = (int)v.size();
    if (k < 2) return {false, -1};

    for (int it = 0; it < 80; ++it) {
        int i = rndInt(0, k - 2);
        ll x = v[i], y = v[i + 1];
        if (x + y <= lim_b) {
            int pos = i + 1;
            v.insert(v.begin() + pos, x + y);
            is_orig.insert(is_orig.begin() + pos, 0);
            return {true, pos};
        }
    }
    for (int i = 0; i + 1 < k; ++i) {
        ll x = v[i], y = v[i + 1];
        if (x + y <= lim_b) {
            int pos = i + 1;
            v.insert(v.begin() + pos, x + y);
            is_orig.insert(is_orig.begin() + pos, 0);
            return {true, pos};
        }
    }
    return {false, -1};
}

static bool buildYES_random_safe_with_flags(const vector<ll>& a, int m, ll lim_b, vector<ll>& b, vector<char>& is_orig) {
    b = a;
    is_orig.assign((int)a.size(), 1);
    while ((int)b.size() < m) {
        auto res = safe_random_insertion_with_pos(b, is_orig, lim_b);
        if (!res.first) return false;
    }
    return true;
}

// Shallow exact length m (m in [n..2n-1]) with flags.
static void buildShallowExactWithFlags(const vector<ll>& a, ll lim_b, int m, vector<ll>& b, vector<char>& is_orig) {
    int n = (int)a.size();
    require_or_die(m >= n, "Shallow: must have m >= n.");
    require_or_die(m <= 2 * n - 1, "Shallow: must have m <= 2n-1.");

    int need = m - n;
    vector<int> good;
    good.reserve(max(0, n - 1));

    for (int i = 0; i + 1 < n; i++) {
        if (a[i] + a[i + 1] <= lim_b) good.push_back(i);
    }
    require_or_die((int)good.size() >= need,
                   "Shallow: not enough valid gaps with a[i]+a[i+1] <= lim_b to reach requested m.");

    uint32_t mtseed = (uint32_t)rnd.next(1, (int)1'000'000'000);
    std::mt19937 mt(mtseed);
    shuffle(good.begin(), good.end(), mt);

    vector<char> ins(max(0, n - 1), 0);
    for (int k = 0; k < need; k++) ins[good[k]] = 1;

    b.clear();
    is_orig.clear();
    b.reserve(m);
    is_orig.reserve(m);

    for (int i = 0; i < n; i++) {
        b.push_back(a[i]);
        is_orig.push_back(1);
        if (i + 1 < n && ins[i]) {
            b.push_back(a[i] + a[i + 1]);
            is_orig.push_back(0);
        }
    }
    require_or_die((int)b.size() == m, "Internal error: shallow size mismatch.");
}

// YES_STRESS_GENERAL (type=4)
static void buildYES_stress_general(int n, int m, ll lim_b, vector<ll>& a, vector<ll>& b, vector<char>& is_orig) {
    require_or_die(n >= 2, "YES_STRESS_GENERAL requires n >= 2.");
    require_or_die(m >= n, "YES_STRESS_GENERAL requires m >= n.");
    int t = m - n;
    require_or_die((ll)t + 1 <= lim_b, "YES_STRESS_GENERAL needs (m-n+1) <= lim_b.");

    a.assign(n, 1);
    b.clear();
    is_orig.clear();
    b.reserve(m);
    is_orig.reserve(m);

    b.push_back(1);
    is_orig.push_back(1);

    for (int x = t + 1; x >= 2; --x) {
        b.push_back(x);
        is_orig.push_back(0);
    }
    for (int i = 0; i < n - 1; i++) {
        b.push_back(1);
        is_orig.push_back(1);
    }
    require_or_die((int)b.size() == m, "Internal error: stress_general size mismatch.");
}

static void make_NO_REDUCE_from_YES(vector<ll>& b, const vector<char>& is_orig, ll lim_b) {
    int m = (int)b.size();
    vector<int> cand;
    for (int i = 1; i <= m - 2; i++) if (!is_orig[i]) cand.push_back(i);
    require_or_die(!cand.empty(), "NO_REDUCE requires at least one inserted element (use m>n).");

    int i = cand[rndInt(0, (int)cand.size() - 1)];
    ll x = b[i - 1], y = b[i + 1];
    ll sum = x + y;

    ll target;
    if (sum <= lim_b) {
        target = (sum < lim_b ? sum + 1 : sum - 1);
        if (target == b[i]) target = (target > 1 ? target - 1 : target + 1);
        require_or_die(1 <= target && target <= lim_b, "Internal error: target out of bounds (sum<=lim_b).");
    } else {
        if (lim_b == 1) target = 1;
        else target = (b[i] == 1 ? 2 : 1);
    }
    b[i] = target;
}

static void validate_subtask(int subtask, int n, int m) {
    if (subtask == 1) require_or_die(n <= 8 && m <= 8, "Subtask 1 requires n,m <= 8.");
    else if (subtask == 3) require_or_die(n == 2, "Subtask 3 requires n = 2.");
    else if (subtask == 4) require_or_die(n <= 2'000 && m <= 2'000, "Subtask 4 requires n,m <= 2000.");
    else if (subtask == 2 || subtask == 5 || subtask == 6) return;
    else die_fail("Unknown subtask id.");
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    require_or_die(argc >= 7, "Usage: gen <seed> <subtask> <n> <m> <type> <lim_a> [lim_b]");

    int seed = atoi(argv[1]);
    int subtask = atoi(argv[2]);
    int n = atoi(argv[3]);
    int m = atoi(argv[4]);
    int type = atoi(argv[5]);
    ll lim_a = atoll(argv[6]);
    ll lim_b = (argc >= 8 ? atoll(argv[7]) : 1'000'000'000LL);

    rnd.setSeed(seed);

    require_or_die(1 <= n && n <= 100'000, "n must satisfy 1 <= n <= 100000.");
    require_or_die(1 <= m && m <= 100'000, "m must satisfy 1 <= m <= 100000.");
    require_or_die(0 <= type && type <= 4, "type must be in {0,1,2,3,4}.");
    require_or_die(1 <= lim_b && lim_b <= 1'000'000'000LL, "lim_b must satisfy 1 <= lim_b <= 1e9.");
    require_or_die(1 <= lim_a && lim_a <= lim_b, "lim_a must satisfy 1 <= lim_a <= lim_b.");

    validate_subtask(subtask, n, m);

    vector<ll> a(n), b;
    vector<char> is_orig;

    // Subtask 5: force all a_i = 1
    if (subtask == 5) {
        for (int i = 0; i < n; i++) a[i] = 1;
    } else {
        for (int i = 0; i < n; i++) a[i] = rndLL(1, lim_a);
    }

    if (type == 0) {
        require_or_die(m >= n, "YES_RANDOM requires m >= n.");
        require_or_die(n >= 2 || m == n, "YES_RANDOM with n=1 and m>n is impossible.");

        if (subtask == 2) {
            require_or_die(m <= 2 * n - 1, "Subtask 2 (YES) requires m <= 2n-1.");
            ll cap = min(lim_a, lim_b / 2);
            require_or_die(cap >= 1, "Subtask 2 YES: lim_b too small.");
            for (int i = 0; i < n; i++) a[i] = rndLL(1, cap);
            buildShallowExactWithFlags(a, lim_b, m, b, is_orig);
        } else {
            bool ok = buildYES_random_safe_with_flags(a, m, lim_b, b, is_orig);
            require_or_die(ok, "YES_RANDOM: cannot build YES under lim_b.");
        }
    }
    else if (type == 1) {
        // NO_SUBSEQ
        if (subtask == 5) {
            if (m < n) b.assign(m, 1);
            else {
                require_or_die(lim_b >= 2, "NO_SUBSEQ (subtask 5, m>=n) requires lim_b >= 2.");
                b.assign(m, 2);
            }
        } else {
            b.assign(m, 1);
            if (m >= n) {
                require_or_die(lim_a >= 2, "NO_SUBSEQ with m>=n requires lim_a >= 2 (or use m<n).");
                a[rndInt(0, n - 1)] = 2;
            }
        }
    }
    else if (type == 2) {
        // NO_REDUCE
        require_or_die(m > n, "NO_REDUCE intended non-trivial; use m>n.");
        require_or_die(n >= 2, "NO_REDUCE requires n>=2.");

        if (subtask == 2) {
            require_or_die(m <= 2 * n - 1, "Subtask 2 requires m <= 2n-1.");
            ll cap = min(lim_a, lim_b / 2);
            require_or_die(cap >= 1, "Subtask 2: lim_b too small.");
            for (int i = 0; i < n; i++) a[i] = rndLL(1, cap);
            buildShallowExactWithFlags(a, lim_b, m, b, is_orig);
        } else {
            bool ok = buildYES_random_safe_with_flags(a, m, lim_b, b, is_orig);
            require_or_die(ok, "NO_REDUCE: cannot build base YES.");
        }
        make_NO_REDUCE_from_YES(b, is_orig, lim_b);
    }
    else if (type == 3) {
        // YES_STRESS_SHALLOW
        require_or_die(n >= 2, "YES_STRESS_SHALLOW requires n >= 2.");
        require_or_die(m >= n, "YES_STRESS_SHALLOW requires m >= n.");
        require_or_die(m <= 2 * n - 1, "YES_STRESS_SHALLOW requires m <= 2n-1.");
        require_or_die(lim_b >= 2, "YES_STRESS_SHALLOW needs lim_b >= 2.");

        for (int i = 0; i < n; i++) a[i] = 1;
        buildShallowExactWithFlags(a, lim_b, m, b, is_orig);
    }
    else if (type == 4) {
        // YES_STRESS_GENERAL
        buildYES_stress_general(n, m, lim_b, a, b, is_orig);
        require_or_die(lim_a >= 1, "YES_STRESS_GENERAL needs lim_a >= 1.");
    }

    require_or_die((int)b.size() == m, "Internal error: b size mismatch.");
    for (ll x : a) require_or_die(1 <= x && x <= lim_b, "Internal error: a out of bounds.");
    for (ll x : b) require_or_die(1 <= x && x <= lim_b, "Internal error: b out of bounds.");

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
    for (int i = 0; i < m; i++) {
        if (i) cout << " ";
        cout << b[i];
    }
    cout << "\n";
    return 0;
}