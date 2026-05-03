#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Initialize testlib
    registerGen(argc, argv, 1);
    
    // Read command line arguments
    int n = opt<int>("n");
    int q = opt<int>("q");
    int k = opt<int>("k");
    string type = opt<string>("type");

    cout << n << " " << q << " " << k << "\n";
    
    // 1. Generate the highly specific initial array state
    for(int i = 0; i < n; i++){
        if (type == "flat") {
            cout << 0 << (i == n - 1 ? "" : " ");
        } else if (type == "stairs") {
            cout << (i % k) << (i == n - 1 ? "" : " ");
        } else if (type == "sawtooth") {
            cout << (i % 2 == 0 ? 0 : k - 1) << (i == n - 1 ? "" : " ");
        } else {
            // For micro, lazy_stress, and small_ranges, standard random is fine
            cout << rnd.next(0, k - 1) << (i == n - 1 ? "" : " ");
        }
    }
    cout << "\n";

    // 2. Generate the highly specific queries to break the tree
    for(int i = 0; i < q; i++){
        if (type == "flat" || type == "stairs" || type == "sawtooth") {
            // Avoid the "Root Node Trap". 
            // Use massive ranges, but randomize the edges slightly so the queries 
            // are forced to split across multiple internal Segment Tree nodes, 
            // brutally testing the pull()/merge() boundary logic.
            int l = rnd.next(1, min(500, n));
            int r = rnd.next(max(1, n - 500), n);
            
            if (l > r) swap(l, r);
            
            if (i % 2 == 0) cout << "1 " << l << " " << r << "\n";
            else cout << "2 " << l << " " << r << "\n";
            
        } else if (type == "micro") {
            // Randomly attack the extreme left edge or extreme right edge
            int op = rnd.next(1, 2);
            if (rnd.next(1, 2) == 1) { // Attack Left Edge
                int l = rnd.next(1, min(3, n));
                int r = rnd.next(l, min(5, n));
                cout << op << " " << l << " " << r << "\n";
            } else { // Attack Right Edge
                int l = rnd.next(max(1, n - 4), n);
                int r = rnd.next(l, n);
                cout << op << " " << l << " " << r << "\n";
            }
            
        } else if (type == "lazy_stress") {
            // "The Lazy Avalanche"
            // Slowly slide the update bounds to force continuous lazy tag collisions.
            // This maximizes O(log N) tree depth traversal and tests for integer overflow in the lazy array.
            if (i % 2 == 0) {
                int shift = i % max(1, (n / 4));
                cout << "1 " << 1 + shift << " " << min(n, (n / 2) + shift) << "\n";
            } else {
                cout << "2 1 " << n << "\n";
            }
            
        } else if (type == "small_ranges") {
            // "Needle in a Haystack"
            // Tiny ranges force the Segment Tree to bypass early returns and dive to the deepest leaf nodes.
            // This crashes Segment Trees with bad memory management or heavy recursive overhead.
            int l = rnd.next(1, n - 5);
            int r = rnd.next(l, l + 5);
            int op = rnd.next(1, 2);
            cout << op << " " << l << " " << r << "\n";
        }
    }
    return 0;
}