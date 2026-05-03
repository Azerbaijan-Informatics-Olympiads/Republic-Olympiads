#include <iostream>

using namespace std;

long long power(long long base, long long exp) {
  long long res = 1;
  base %= 998244353;
  while (exp > 0) {
    if (exp % 2 == 1) res = (res * base) % 998244353;
    base = (base * base) % 998244353;
    exp /= 2;
  }
  return res;
}

int main() {
  long long n;
  cin >> n;
  
  long long MOD = 998244353;
  long long part1 = ((n - 1) % MOD * (n + 2) % MOD) % MOD;
  part1 = (part1 * power(2, MOD - 2)) % MOD; // Divide by 2 modulo
  
  long long part2 = (power(2, n) - n + MOD) % MOD;
  
  cout << (part1 + part2) % MOD << "\n";
  return 0;
}