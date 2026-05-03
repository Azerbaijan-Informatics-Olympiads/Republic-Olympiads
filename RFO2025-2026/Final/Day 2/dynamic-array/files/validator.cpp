#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 100'000 + 5;

ll a[N], b[N];

static bool is_yes_possible(int n, int m) {
    vector<ll> st;
    st.reserve(m);

    for (int i = 0; i < m; i++) {
        st.push_back(b[i]);
        while ((int)st.size() >= 3) {
            int k = (int)st.size();
            ll x = st[k - 3];
            ll y = st[k - 2];
            ll z = st[k - 1];
            if (y == x + z) {
                st[k - 2] = st[k - 1];
                st.pop_back();
            } else break;
        }
    }

    if ((int)st.size() != n) return false;
    for (int i = 0; i < n; i++) if (st[i] != a[i]) return false;
    return true;
}

static bool shallow_matches_a(int n, int m) {
    if (!(m >= n && m <= 2 * n - 1)) return false;

    int j = 0;
    if (b[j] != a[0]) return false;

    for (int i = 0; i < n - 1; i++) {
        if (j >= m) return false;
        if (b[j] != a[i]) return false;

        ll sum = a[i] + a[i + 1];

        if (j + 1 >= m) return false;

        if (b[j + 1] == sum) {
            if (j + 2 >= m) return false;
            if (b[j + 2] != a[i + 1]) return false;
            j += 2;
        } else {
            if (b[j + 1] != a[i + 1]) return false;
            j += 1;
        }
    }

    if (j != m - 1) return false;
    if (b[j] != a[n - 1]) return false;

    return true;
}

static bool valid_for_second_subtask(int n, int m) {
    // Subtask 2: If answer is YES -> shallow; if NO -> always valid.
    bool yes = is_yes_possible(n, m);
    if (!yes) return true;
    return shallow_matches_a(n, m);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100'000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100'000, "m");
    inf.readEoln();

    string group = validator.group();

    // Mapping (your current table):
    // 1: n,m <= 9
    // 2: (if YES -> shallow)
    // 3: n = 2
    // 4: n,m <= 2000
    // 5: all a_i = 1
    // 6: none

    if (group == "1")
        ensuref(n <= 9 && m <= 9, "Subtask 1 requires n,m <= 8.");

    if (group == "3")
        ensuref(n == 2, "Subtask 3 requires n = 2.");

    if (group == "4")
        ensuref(n <= 2'000 && m <= 2'000, "Subtask 4 requires n,m <= 2000.");

    for (int i = 0; i < n; i++) {
        a[i] = inf.readLong(1LL, 1'000'000'000LL, "a_i");
        if (group == "5")
            ensuref(a[i] == 1, "Subtask 5 requires all a_i = 1.");
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        b[i] = inf.readLong(1LL, 1'000'000'000LL, "b_i");
        if (i + 1 < m) inf.readSpace();
    }
    inf.readEoln();

    if (group == "2")
        ensuref(valid_for_second_subtask(n, m),
                "Subtask 2 violated: if answer is YES then the instance must be shallow.");

    inf.readEof();
    return 0;
}