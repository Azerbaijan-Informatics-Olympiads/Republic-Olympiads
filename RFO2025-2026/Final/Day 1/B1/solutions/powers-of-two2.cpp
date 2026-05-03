#include <iostream>

using namespace std;

int main() {
  // Fast I/O
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // We are placing exactly 12 pieces using the 2D staircase method.
  cout << 12 << "\n";
  
  long long x = 1;
  long long y = 1;
  long long step = 1; // Represents the current power of 2
  
  // Print the first piece
  cout << x << " " << y << "\n";
  
  // Generate the next 11 pieces
  for (int i = 0; i < 11; ++i) {
    if (i % 2 == 0) {
      x += step; // Even iterations: move along X-axis
    } else {
      y += step; // Odd iterations: move along Y-axis
    }
    cout << x << " " << y << "\n";
    
    step *= 2; // Double the step size for the next power of 2
  }
  
  return 0;
}