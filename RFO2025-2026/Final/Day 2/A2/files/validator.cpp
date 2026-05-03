#include <bits/stdc++.h>
#include "testlib.h"

#define ll long long
#define endl "\n"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int testCount = inf.readInt(1, 10'000, "testCount");
    inf.readEoln();
    ll sum = 0;
    for (int i = 0; i < testCount; i++) {
        setTestCase(i + 1);
        int n = inf.readInt(1, 1'000'000'000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1'000'000'000, "m");
        inf.readSpace();
        int k = inf.readInt(0, min(1ll * n * m, (ll)100'000), "k");
        inf.readEoln();
        sum += k;
        ensuref(sum <= 100'000, "The total sum of k exceeds 10^5");
        while (k--)
        {
            int r = inf.readInt(1, n, "r_i");
            inf.readSpace();
            int c = inf.readInt(1, m, "c_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}