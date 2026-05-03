#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <random>

using namespace std;

const int MAX = 2026;

int main() {
  // Fast I/O
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<pair<int, int>> pts;
  set<int> diffs;

  // 1. Seed the board with the 12-piece 2D Staircase
  long long sx = 1;
  long long sy = 1;
  long long step = 1;
  
  pts.push_back({(int)sx, (int)sy});
  for (int i = 0; i < 11; ++i) {
    if (i % 2 == 0) sx += step;
    else sy += step;
    pts.push_back({(int)sx, (int)sy});
    step *= 2;
  }

  // Calculate existing distances for the seed
  for (int i = 0; i < pts.size(); ++i) {
    for (int j = i + 1; j < pts.size(); ++j) {
      diffs.insert(abs(pts[i].first - pts[j].first) + abs(pts[i].second - pts[j].second));
    }
  }

  // 2. Greedy search for pieces 13 to 50
  mt19937 rng(1337); 
  
  // Attempt to find new pieces until we hit the goal or run out of tries
  for (int attempts = 0; attempts < 500000 && pts.size() < 50; ++attempts) {
    int nx = rng() % MAX + 1;
    int ny = rng() % MAX + 1;
    
    bool ok = true;
    vector<int> new_distances;
    
    // Check against current pieces
    for (const auto& p : pts) {
      int d = abs(nx - p.first) + abs(ny - p.second);
      
      // Reject if distance is 0 (duplicate cell) or already exists
      if (d == 0 || diffs.count(d)) {
        ok = false;
        break;
      }
      new_distances.push_back(d);
    }
    
    // Check for internal distance collisions within the new set
    if (ok) {
      set<int> unique_check;
      for (int d : new_distances) {
        if (!unique_check.insert(d).second) {
          ok = false;
          break;
        }
      }
    }
    
    // If valid, commit the piece and update the distance set
    if (ok) {
      pts.push_back({nx, ny});
      for (int d : new_distances) {
        diffs.insert(d);
      }
    }
  }

  // 3. Final Output
  cout << pts.size() << "\n";
  for (const auto& p : pts) {
    cout << p.first << " " << p.second << "\n";
  }

  return 0;
}