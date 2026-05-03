#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Read command line arguments
    int n = opt<int>("n");
    int q = opt<int>("q");
    int k = opt<int>("k");
    bool no_updates = opt<bool>("no_updates", false);
    bool point_updates = opt<bool>("point_updates", false);

    cout << n << " " << q << " " << k << endl;

    // Generate initial array A
    for (int i = 1; i <= n; i++) {
        cout << rnd.next(0, k - 1);
        if (i < n) cout << " ";
    }
    cout << endl;

    // Generate Queries
    for (int i = 1; i <= q; i++) {
        int type;
        if (no_updates) {
            type = 2;
        } else {
            type = rnd.next(1, 2); 
        }

        int l = rnd.next(1, n);
        int r = rnd.next(l, n);

        if (type == 1 && point_updates) {
            r = l; // Force L = R for point updates
        }

        cout << type << " " << l << " " << r << endl;
    }

    return 0;
}