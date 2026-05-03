#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Default to Subtask 5 (full constraints) if no group is specified
    int subtask = 5; 
    if (!validator.group().empty()) {
        subtask = stoi(validator.group());
    }

    // Determine max N and Q based on subtask
    int max_nq = 200000;
    if (subtask == 1) {
        max_nq = 1000;
    }

    // Determine exact K bounds based on subtask
    int max_k = 10;
    if (subtask == 4) {
        max_k = 2;
    }

    // Read N, Q, K
    int n = inf.readInt(1, max_nq, "N");
    inf.readSpace();
    int q = inf.readInt(1, max_nq, "Q");
    inf.readSpace();
    
    // If subtask 4, min K and max K are both 2. Otherwise 2 to 10.
    int min_k = (subtask == 4) ? 2 : 2; 
    int k = inf.readInt(min_k, max_k, "K");
    inf.readEoln();

    // Read initial tree heights
    for (int i = 1; i <= n; i++) {
        inf.readInt(0, k - 1, "A_i");
        if (i < n) inf.readSpace();
    }
    inf.readEoln();

    // Read queries
    for (int i = 1; i <= q; i++) {
        int min_type = 1;
        int max_type = 2;
        
        // Subtask 2: No events of type 1
        if (subtask == 2) {
            min_type = 2; 
        }

        int type = inf.readInt(min_type, max_type, "type");
        inf.readSpace();

        int l = inf.readInt(1, n, "L");
        inf.readSpace();

        int max_r = n;
        
        // Subtask 3: For all events of type 1, L = R
        if (subtask == 3 && type == 1) {
            max_r = l;
        }

        int r = inf.readInt(l, max_r, "R");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}