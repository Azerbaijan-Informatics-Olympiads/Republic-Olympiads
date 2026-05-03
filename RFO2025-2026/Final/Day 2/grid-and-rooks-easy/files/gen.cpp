#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Test {
    ll n, m;
    vector<pair<ll,ll>> rooks;
};

set<pair<ll,ll>> used;

void add(vector<pair<ll,ll>>& v, ll n, ll m, ll r, ll c) {
    if (r < 1 || r > n || c < 1 || c > m) return;
    if (used.insert({r, c}).second) v.push_back({r, c});
}

void addRandom(vector<pair<ll,ll>>& v, ll n, ll m, int need) {
    while ((int)v.size() < need) {
        ll r = rnd.next(1LL, n);
        ll c = rnd.next(1LL, m);
        add(v, n, m, r, c);
    }
}

Test makeCase(ll n, ll m, vector<pair<ll,ll>> cells) {
    used.clear();
    vector<pair<ll,ll>> v;
    for (auto [r, c] : cells) add(v, n, m, r, c);
    return {n, m, v};
}

void printTests(vector<Test> tests) {
    println((int)tests.size());
    for (auto &tc : tests) {
        println(tc.n, tc.m, (int)tc.rooks.size());
        for (auto [r, c] : tc.rooks) println(r, c);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int id = atoi(argv[1]);
    vector<Test> tests;

    if (id == 1) {
        tests.push_back(makeCase(1, 1, {}));
        tests.push_back(makeCase(1, 2, {}));
        tests.push_back(makeCase(2, 1, {{1,1}}));
        tests.push_back(makeCase(2, 2, {{1,1}, {2,2}}));
        tests.push_back(makeCase(3, 3, {{1,2}, {2,2}, {3,2}}));
    }

    else if (id == 2) {
        tests.push_back(makeCase(1000000000LL, 1000000000LL, {}));
        tests.push_back(makeCase(1, 1000000000LL, {}));
        tests.push_back(makeCase(1000000000LL, 1, {}));
        tests.push_back(makeCase(123456789, 987654321, {}));
    }

    else if (id == 3) {
        tests.push_back(makeCase(10, 10, {{1,1}}));
        tests.push_back(makeCase(10, 10, {{10,10}}));
        tests.push_back(makeCase(10, 10, {{1,10}}));
        tests.push_back(makeCase(10, 10, {{10,1}}));
        tests.push_back(makeCase(1000000000LL, 1000000000LL, {{1,1}}));
    }

    else if (id == 4) {
        for (int n = 1; n <= 6; n++) {
            for (int m = 1; m <= 6; m++) {
                vector<pair<ll,ll>> v;
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= m; j++)
                        v.push_back({i, j});
                tests.push_back(makeCase(n, m, v));
            }
        }
    }

    else if (id == 5) {
        vector<pair<ll,ll>> v;
        for (int i = 1; i <= 50000; i++) v.push_back({1, i});
        tests.push_back(makeCase(1, 1000000000LL, v));
    
        v.clear();
        for (int i = 1; i <= 50000; i++) v.push_back({i, 1});
        tests.push_back(makeCase(1000000000LL, 1, v));
    }

    else if (id == 6) {
        vector<pair<ll,ll>> v;
        for (int i = 1; i <= 100000; i++) {
            v.push_back({i * 10000LL, i * 10000LL});
        }
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));
    }

    else if (id == 7) {
        vector<pair<ll,ll>> v;
        ll r = 1, c = 1;
        for (int i = 0; i < 50000; i++) {
            v.push_back({r, c});
            c += 10000;
            v.push_back({r, c});
            r += 10000;
        }
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));
    }

    else if (id == 8) {
        vector<pair<ll,ll>> v;
        for (int i = 1; i <= 100000; i++) {
            v.push_back({500000000LL, i * 9999LL});
        }
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));
    }

    else if (id == 9) {
        vector<pair<ll,ll>> v;
        for (int i = 1; i <= 100000; i++) {
            v.push_back({i * 9999LL, 500000000LL});
        }
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));
    }

    else if (id == 10) {
        vector<pair<ll,ll>> v;
        for (int i = 1; i <= 50000; i++) v.push_back({i, i + 10});
        for (int i = 1; i <= 50000; i++) v.push_back({999900000LL + i, 999800000LL + i});
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));
    }

    else if (id == 11) {
        for (int tc = 0; tc < 100; tc++) {
            ll n = rnd.next(1, 30);
            ll m = rnd.next(1, 30);
            int lim = min<ll>(n * m, 100);
            int k = rnd.next(0, lim);
            used.clear();
            vector<pair<ll,ll>> v;
            addRandom(v, n, m, k);
            tests.push_back({n, m, v});
        }
    }

    else if (id == 12) {
        for (int tc = 0; tc < 20; tc++) {
            ll n = rnd.next(1000LL, 1000000LL);
            ll m = rnd.next(1000LL, 1000000LL);
            int k = 5000;
            used.clear();
            vector<pair<ll,ll>> v;
            addRandom(v, n, m, k);
            tests.push_back({n, m, v});
        }
    }

    else if (id == 13) {
        for (int tc = 0; tc < 10; tc++) {
            ll n = rnd.next(900000000LL, 1000000000LL);
            ll m = rnd.next(900000000LL, 1000000000LL);
            int k = 10000;
            used.clear();
            vector<pair<ll,ll>> v;
            addRandom(v, n, m, k);
            tests.push_back({n, m, v});
        }
    }

    else if (id == 14) {
        used.clear();
        vector<pair<ll,ll>> v;
        addRandom(v, 1000000000LL, 1000000000LL, 100000);
        tests.push_back({1000000000LL, 1000000000LL, v});
    }

    else if (id == 15) {
        vector<ll> rows, cols;
        for (int i = 0; i < 400; i++) rows.push_back(1 + i * 2500000LL);
        for (int i = 0; i < 400; i++) cols.push_back(1 + i * 2500000LL);

        used.clear();
        vector<pair<ll,ll>> v;
        while ((int)v.size() < 100000) {
            ll r = rows[rnd.next(0, (int)rows.size() - 1)];
            ll c = cols[rnd.next(0, (int)cols.size() - 1)];
            add(v, 1000000000LL, 1000000000LL, r, c);
        }
        tests.push_back({1000000000LL, 1000000000LL, v});
    }

    else if (id == 16) {
        vector<pair<ll,ll>> v = {
            {1,1}, {1,2}, {2,1}, {2,2},
            {999999999LL,1000000000LL},
            {1000000000LL,999999999LL},
            {1000000000LL,1000000000LL}
        };
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));

        v.clear();
        for (int i = 1; i <= 49996; i++) {
            v.push_back({1, i});
            v.push_back({1000000000LL, 1000000000LL - i + 1});
        }
        tests.push_back(makeCase(1000000000LL, 1000000000LL, v));
    }

    else if (id == 17) {
        vector<pair<ll,ll>> v;
        ll r = 1, c = 1;
        for (int i = 0; i < 30000; i++) {
            add(v, 1000000000LL, 1000000000LL, r, c);
            add(v, 1000000000LL, 1000000000LL, r, c + 7);
            add(v, 1000000000LL, 1000000000LL, r + 11, c + 7);
            r += 11;
            c += 7;
        }
        addRandom(v, 1000000000LL, 1000000000LL, 100000);
        tests.push_back({1000000000LL, 1000000000LL, v});
    }

    else if (id == 18) {
        for (int tc = 0; tc < 10000; tc++) {
            ll n = rnd.next(1LL, 1000000000LL);
            ll m = rnd.next(1LL, 1000000000LL);
            tests.push_back(makeCase(n, m, {}));
        }
    }

    else if (id == 19) {
        int total = 0;
        for (int tc = 0; tc < 1000; tc++) {
            ll n = rnd.next(100LL, 1000000000LL);
            ll m = rnd.next(100LL, 1000000000LL);
            int k = 100;
            total += k;
            used.clear();
            vector<pair<ll,ll>> v;
            addRandom(v, n, m, k);
            tests.push_back({n, m, v});
        }
    }

    else if (id == 20) {
        vector<pair<ll,ll>> v;
        ll n = 999999937LL, m = 999999929LL;

        for (int i = 0; i < 25000; i++) {
            add(v, n, m, 1, i * 37LL + 1);
            add(v, n, m, i * 41LL + 1, 1);
            add(v, n, m, n, m - i * 43LL);
            add(v, n, m, n - i * 47LL, m);
        }

        tests.push_back({n, m, v});
    }

    printTests(tests);
}