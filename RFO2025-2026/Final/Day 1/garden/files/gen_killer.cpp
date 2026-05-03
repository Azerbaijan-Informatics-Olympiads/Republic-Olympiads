#include "testlib.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int n = opt<int>("n");
    int q = opt<int>("q");
    int k = opt<int>("k");
    int st = opt<int>("st"); 

    cout << n << " " << q << " " << k << "\n";
    
    // Generate initial array
    for(int i = 0; i < n; i++){
        cout << rnd.next(0, k - 1) << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    for(int i = 0; i < q; i++){
        // Generate massive, but slightly varying bounds to break compiler optimizations
        int big_l = rnd.next(1, min(1000, n));
        int big_r = rnd.next(max(1, n - 999), n);
        
        if (st == 2) {
            // Group 2: Only massive, slightly shifting range queries
            cout << "2 " << big_l << " " << big_r << "\n";
        } else if (st == 3) {
            // Group 3:
            // This satisfies the subtask condition while maximizing the O(N) workload
            if (i % 20 == 0) {
                int pos = rnd.next(1, n);
                cout << "1 " << pos << " " << pos << "\n";
            } else {
                cout << "2 " << big_l << " " << big_r << "\n";
            }
        } else if (st == 4 || st == 5) {
            // Group 5: Alternate massive shifting range updates and queries
            if (i % 2 == 0) {
                cout << "1 " << big_l << " " << big_r << "\n";
            } else {
                cout << "2 " << big_l << " " << big_r << "\n";
            }
        }
    }
    return 0;
}