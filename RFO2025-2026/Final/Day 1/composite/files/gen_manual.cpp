#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Fast O(sqrt(N)) primality test
bool is_prime(long long n) {
  if (n <= 3) return n > 1;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (long long i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  // You can change these parameters to hunt for different families
  int target_size = 7; 
  int length = 9;      

  // High-performance random number generation setup
  random_device rd;
  mt19937_64 gen(rd());
  uniform_int_distribution<int> dist_first(1, 9);
  uniform_int_distribution<int> dist_mid(0, 9);
  uniform_int_distribution<int> dist_star(1, length - 2);
  
  int last_digits[] = {1, 3, 7, 9};
  uniform_int_distribution<int> dist_last(0, 3);

  cout << "Hunting for a prime family of " << target_size 
       << " (Length: " << length << " digits)...\n";

  auto start_time = chrono::high_resolution_clock::now();
  long long attempts = 0;

  while (true) {
    attempts++;
    
    // 1. Generate the random pattern string
    string s = "";
    s += to_string(dist_first(gen));
    for (int i = 1; i < length - 1; ++i) {
      s += to_string(dist_mid(gen));
    }
    s += to_string(last_digits[dist_last(gen)]);

    // 2. Pick a random middle position for our '*'
    int star_idx = dist_star(gen);
    s[star_idx] = '*';

    // 3. Mathematical Optimization: 
    // Calculate the base number and the multiplier for the '*' position
    // Example: 224*417 -> base_num = 2240417, multiplier = 1000
    long long base_num = 0;
    long long multiplier = 1;
    long long current_pow = 1;
    
    for (int i = length - 1; i >= 0; --i) {
      if (i == star_idx) {
        multiplier = current_pow;
      } else {
        base_num += (s[i] - '0') * current_pow;
      }
      current_pow *= 10;
    }

    // 4. Test all 10 possibilities using fast integer math
    vector<long long> primes_found;
    for (long long d = 0; d <= 9; ++d) {
      long long candidate = base_num + (d * multiplier);
      if (is_prime(candidate)) {
        primes_found.push_back(candidate);
      }
    }

    // 5. Check if we hit our target!
    if (primes_found.size() >= target_size) {
      auto end_time = chrono::high_resolution_clock::now();
      chrono::duration<double> elapsed = end_time - start_time;

      cout << "\nSUCCESS! Found after " << attempts << " attempts (" 
           << elapsed.count() << " seconds)\n";
      cout << "Pattern: " << s << "\n";
      cout << "--------------------\n";
      for (long long p : primes_found) {
        cout << p << "\n";
      }
      break;
    }
  }

  return 0;
}