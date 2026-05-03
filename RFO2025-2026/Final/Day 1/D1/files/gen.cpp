#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static void print_case(const vector<int>& a) {
    int n = (int)a.size();
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>("n");
    int mode = opt<int>("mode", 0);

    vector<int> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; i++) a[i] = rnd.next(1, n);
    }
    else if (mode == 1) {
        for (int i = 0; i < n; i++) a[i] = rnd.next(1, min(3, n));
    }
    else if (mode == 2) {
        for (int i = 0; i < n; i++) a[i] = (i % 2 == 0 ? 1 : n);
    }
    else if (mode == 3) {
        a[0] = rnd.next(1, n);
        for (int i = 1; i < n; i++) a[i] = rnd.next(a[i - 1], n);
    }
    else if (mode == 4) {
        a[0] = rnd.next(1, n);
        for (int i = 1; i < n; i++) a[i] = rnd.next(1, a[i - 1]);
    }
    else if (mode == 5) {
        a[0] = rnd.next(1, n);
        for (int i = 1; i < n; i++) {
            int delta = rnd.next(-1, 1);
            int x = a[i - 1] + delta;
            x = max(1, min(n, x));
            a[i] = x;
        }
    }
    else if (mode == 6) {
        int i = 0;
        while (i < n) {
            int len = rnd.next(1, min(20, n - i));
            int val = rnd.next(1, n);
            for (int j = 0; j < len; j++) a[i++] = val;
        }
    }
    else if (mode == 7) {
        a[0] = rnd.next(1, n);
        for (int i = 1; i < n; i++) {
            if (rnd.next(0, 1)) {
                int dir = rnd.next(0, 1) ? 1 : -1;
                int jump = rnd.next(2, min(20, n - 1));
                int x = a[i - 1] + dir * jump;
                x = max(1, min(n, x));
                a[i] = x;
            } else {
                a[i] = rnd.next(1, n);
            }
        }
    }
    else if (mode == 8) {
        int split = rnd.next(1, n - 1);
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        while (y == x) y = rnd.next(1, n);
        for (int i = 0; i < split; i++) a[i] = x;
        for (int i = split; i < n; i++) a[i] = y;
    }
    else if (mode == 9) {
        vector<int> vals(n);
        iota(vals.begin(), vals.end(), 1);
        shuffle(vals.begin(), vals.end());
        a = vals;
    }
    else if (mode == 10) {
        int x = rnd.next(1, n);
        for (int i = 0; i < n; i++) a[i] = x;
    }
    else if (mode == 11) {
        for (int i = 0; i < n; i++) a[i] = (i % 2 == 0 ? 1 : min(n, 3));
    }
    else if (mode == 12) {
        a[0] = rnd.next(1, n);
        for (int i = 1; i < n; i++) {
            int x;
            if (rnd.next(0, 9) == 0) {
                x = rnd.next(1, n);
            } else {
                x = a[i - 1] + rnd.next(-1, 1);
                x = max(1, min(n, x));
            }
            a[i] = x;
        }
    }
    else {
        quitf(_fail, "Unknown mode");
    }

    print_case(a);
    return 0;
}