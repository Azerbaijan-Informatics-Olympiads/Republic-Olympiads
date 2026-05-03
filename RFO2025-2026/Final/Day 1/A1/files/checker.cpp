#include "testlib.h"
#include <string>

using namespace std;

bool is_composite(int n) {
  if (n <= 3) return false;
  if (n % 2 == 0 || n % 3 == 0) return true;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return true;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  // Initialize the checker
  registerTestlibCmd(argc, argv);

  string input_str = inf.readWord("[0-9\\*]+", "input_str");
  string j_ans = ans.readWord("-1|[1-9][0-9]*", "j_ans");
  string p_ans = ouf.readWord("-1|[1-9][0-9]*", "p_ans");

  // If the participant claims no answer exists
  if (p_ans == "-1") {
    if (j_ans != "-1") {
      quitf(_wa, "Participant answered -1, but a valid number exists.");
    } else {
      quitf(_ok, "Both participant and jury found no answer (-1).");
    }
  }

  // The participant provided a number. We must verify it.
  if (p_ans.length() != input_str.length()) {
    quitf(_wa, "Output length (%d) does not match input length (%d).", 
          (int)p_ans.length(), (int)input_str.length());
  }

  // Check if it matches the pattern and contains only digits
  for (int i = 0; i < p_ans.length(); ++i) {
    if (p_ans[i] < '0' || p_ans[i] > '9') {
      quitf(_wa, "Output contains non-digit character at index %d.", i);
    }
    if (input_str[i] != '*' && input_str[i] != p_ans[i]) {
      quitf(_wa, "Output does not match the input pattern at index %d.", i);
    }
  }

  // Check for leading zero violation
  if (p_ans.length() > 1 && p_ans[0] == '0') {
    quitf(_wa, "Output contains a leading zero, which is not allowed.");
  }

  // Check if the number is composite
  int val = stoi(p_ans);
  if (!is_composite(val)) {
    quitf(_wa, "Output %d is not a composite number.", val);
  }

  // If the participant found a valid answer but the jury claimed it was impossible
  if (j_ans == "-1") {
    quitf(_fail, "Participant found a valid answer (%d), but jury answered -1.", val);
  }

  quitf(_ok, "Participant found a valid composite number matching the pattern.");
}