/*
	author Rashad Mammadov
*/
#include <bits/stdc++.h>
#define pb push_back

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int>a;
    a.pb(2);
    a.pb(3);
    if(n == 3) {
        a.pb(25);
    }else {
        int num = 4;
        int odds = 1;
        int evens_mod_three = 2;
        int last_2i = 0;
        int last_6i, last_3i = 1;
        while((int)a.size() < n) {
            if(num % 2 == 0) {
                a.pb(num);
                evens_mod_three = (evens_mod_three + num) % 3;
                if(num % 3 == 0) {
                    last_6i = (int)a.size() - 1;
                }else {
                    last_2i = (int)a.size() - 1;
                }
            }else if(num % 3 == 0) {
                a.pb(num);
                last_3i = (int)a.size() - 1;
                odds++;
            }
            ++num;
        }
        if(evens_mod_three != 0) {
            a[last_2i] = a[last_6i] + 6;
        }
        if(odds % 2 == 1) {
            a[last_6i] = a[last_3i] + 6;
        }
    }
    for(int x : a) {
        cout << x << ' ';
    }
    cout << '\n';
}
int main() {
    solve();
    return 0;
}
