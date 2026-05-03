#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  // Initialize the validator
  registerValidation(argc, argv);

  // readWord reads a string until whitespace. 
  // The regex "[0-9\\*]{1,9}" ensures it only contains digits or '*', 
  // and is exactly between 1 and 9 characters long.
  string s = inf.readWord("[0-9\\*]{1,9}", "s");

  // Enforce the "no leading zeros" rule for lengths greater than 1
  if (s.length() > 1) {
    ensuref(s[0] != '0', "A number with length > 1 cannot start with '0'.");
  }

  // Ensure there is exactly one newline after the input string
  inf.readEoln();
  
  // Ensure there is no trailing garbage data at the end of the file
  inf.readEof();

  return 0;
}