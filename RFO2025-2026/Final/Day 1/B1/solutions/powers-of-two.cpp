#include <iostream>

using namespace std;

int main() {
  // We can place 11 pieces: 2^0 up to 2^10
  cout << 11 << "\n";
  int x = 1;
  for (int i = 0; i < 11; ++i) {
    cout << x << " 1\n";
    x *= 2;
  }
  return 0;
}