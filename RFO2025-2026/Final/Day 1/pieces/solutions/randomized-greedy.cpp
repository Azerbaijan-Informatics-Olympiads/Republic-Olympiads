#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <random>

using namespace std;

const int MAX = 2026;

int main() {
  vector<pair<int, int>> pts;
  set<int> diffs;
  
  mt19937 rng(1337); // Fixed seed for deterministic output
  
  // Try 100,000 random placements
  for (int attempts = 0; attempts < 100000 && pts.size() < 50; ++attempts) {
    int nx = rng() % MAX + 1;
    int ny = rng() % MAX + 1;
    
    bool ok = true;
    vector<int> new_diffs;
    
    // Check against all currently placed pieces
    for (auto p : pts) {
      int d = abs(nx - p.first) + abs(ny - p.second);
      
      // If distance is 0 (same cell) or distance is already used, reject
      if (d == 0 || diffs.count(d)) {
        ok = false;
        break;
      }
      new_diffs.push_back(d);
    }
    
    // Check for internal collisions (e.g. the new point is exactly 
    // the same distance from two different existing points)
    if (ok) {
      set<int> unique_new(new_diffs.begin(), new_diffs.end());
      if (unique_new.size() < new_diffs.size()) {
        ok = false;
      }
    }
    
    // If it passed all checks, place the piece!
    if (ok) {
      pts.push_back({nx, ny});
      for (int d : new_diffs) {
        diffs.insert(d);
      }
    }
  }
  
  // Output results
  cout << pts.size() << "\n";
  for (auto p : pts) {
    cout << p.first << " " << p.second << "\n";
  }
  
  return 0;
}