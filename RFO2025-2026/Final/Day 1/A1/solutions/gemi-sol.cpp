#include <iostream>
#include <string>

using namespace std;

// Fast check to see if a number is composite
bool is_composite(int n) {
  // 0 and 1 are not composite. 2 and 3 are prime.
  if (n <= 3) return false; 
  
  // Quick checks for multiples of 2 and 3
  if (n % 2 == 0 || n % 3 == 0) return true;
  
  // Check remaining odd numbers up to the square root of n
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return true;
    }
  }
  
  return false; // If we made it here, it's prime
}

string solve(string s) {
  int last_star_idx = -1;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '*') {
      last_star_idx = i;
    }
  }

  // If there are no '*' to replace, check if the integer is composite
  if (last_star_idx == -1) {
    int val = stoi(s);
    if (is_composite(val)) {
      return s;
    } else {
      return "-1";
    }
  }

  // Edge case: single character
  if (s == "*") {
    return "4"; 
  }

  // Replace all '*' except the last one
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '*' && i != last_star_idx) {
      if (i == 0) {
        s[i] = '1'; // Prevent leading zeros
      } else {
        s[i] = '0'; // Minimize sum
      }
    }
  }

  // Calculate the sum of all known digits
  int current_sum = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (i != last_star_idx) {
      current_sum += (s[i] - '0');
    }
  }

  // Find a valid digit for the final '*' to make the whole number % 3 == 0
  int start_digit = (last_star_idx == 0) ? 1 : 0;
  for (int d = start_digit; d <= 9; ++d) {
    if ((current_sum + d) % 3 == 0) {
      s[last_star_idx] = d + '0';
      break;
    }
  }

  return s;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  if (cin >> s) {
    cout << solve(s) << "\n";
  }
  
  return 0;
}