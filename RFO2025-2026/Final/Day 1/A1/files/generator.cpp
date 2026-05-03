#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

char rand_digit(bool allow_zero) {
  if (allow_zero) {
    return char('0' + rnd.next(0, 9));
  } else {
    return char('0' + rnd.next(1, 9));
  }
}

char rand_char(bool allow_zero, int star_percent = 40) {
  if (rnd.next(1, 100) <= star_percent) {
    return '*';
  }
  return rand_digit(allow_zero);
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  // Type definitions:
  // 0: General random pattern
  // 1: Ends with '*'
  // 2: Starts with '*'
  // 3: Exactly two characters long
  // 4: Ends with an odd digit
  // 5. No '*' in the input
  int type = atoi(argv[1]); 
  int len = atoi(argv[2]);

  string s = "";
  if (type == 1) {
    // Requirement 1: Ends with '*'
    for (int i = 0; i < len - 1; ++i) {
      s += rand_char(i > 0);
    }
    s += '*';
  } else if (type == 2) {
    // Requirement 2: Starts with '*'
    s += '*';
    for (int i = 1; i < len; ++i) {
      s += rand_char(i > 0);
    }
  } else if (type == 3) {
    // Requirement 3: Pattern consists of exactly two characters
    len = 2;
    for (int i = 0; i < len; ++i) {
      s += rand_char(i > 0);
    }
  } else if (type == 4) {
    // Requirement 4: Ends with an odd digit
    for (int i = 0; i < len - 1; ++i) {
      s += rand_char(i > 0);
    }
    int odd_digits[] = {1, 3, 5, 7, 9};
    s += char('0' + odd_digits[rnd.next(0, 4)]);
  } else if (type == 5) {
    // Requirement 5: No '*' character
    for (int i = 0; i < len; ++i) {
      s += rand_digit(i > 0);
    }
  } else {
    // General fallback: completely random pattern
    for (int i = 0; i < len; ++i) {
      s += rand_char(i > 0);
    }
  }

  println(s);
  return 0;
}