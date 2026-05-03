#include "testlib.h"
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int subtask = 7;
    if (!validator.group().empty()) {
        subtask = stoi(validator.group());
    }

    int max_n = 5000;
    if (subtask == 1) {
        max_n = 6;
    } else if (subtask == 2) {
        max_n = 10;
    } else if (subtask == 3) {
        max_n = 20;
    } else if (subtask == 5) {
        max_n = 500;
    } else if (subtask == 6) {
        max_n = 1000;
    }

    int n = inf.readInt(1, max_n, "n");
    inf.readEoln();
    
    int ai_max = n;
    if (subtask == 4) {
        ai_max = min(n, 3);
    }
    
    for (int i = 1; i <= n; i++) {
        inf.readInt(1, ai_max, "a_i");

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}