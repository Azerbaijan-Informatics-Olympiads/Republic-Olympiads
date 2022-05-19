#include <bits/stdc++.h>

using namespace std;

void solve() {
    long long k, l, a, b;
    cin >> k >> l;
    if((k + l) % 2ll == 0) {
        a = (k + l) / 2ll;
        b = k - a;
        cout << a << ' ' << b << '\n';
    }else {
        cout << "X\n";
    }
}
int main() {
    solve();
    return 0;
}
