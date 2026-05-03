#include "testlib.h"
#include <vector>
#include <set>
#include <cmath>

using namespace std;

const int MAX = 2026;

int readAndCheckAnswer(InStream& in) {
  // Allow the participant to submit up to 100 pieces
  int P = in.readInt(1, 100, "P");

  vector<pair<int, int>> s(P);
  set<pair<int, int>> cells;

  // Read coordinates and explicitly check for overlapping pieces
  for (int i = 0; i < P; ++i) {
    int x = in.readInt(1, MAX, "x");
    int y = in.readInt(1, MAX, "y");
    
    if (cells.count({x, y})) {
      in.quitf(_wa, "Invalid configuration: Duplicate piece at cell (%d, %d)", x, y);
    }
    cells.insert({x, y});
    s[i] = {x, y};
  }

  // Explicitly check for duplicate Manhattan distances
  set<int> diff;
  for (int i = 0; i < P; ++i) {
    for (int j = i + 1; j < P; ++j) {
      int d = abs(s[i].first - s[j].first) + abs(s[i].second - s[j].second);
      if (diff.count(d)) {
        in.quitf(_wa, "Invalid configuration: Manhattan distance %d is generated more than once", d);
      }
      diff.insert(d);
    }
  }

  return P;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int pans = readAndCheckAnswer(ouf);

  if (pans >= 50) {
    quitf(_ok, "Perfect! Participant placed %d pieces successfully", pans);
  } else if (pans > 0) {
    // Score = 2 * P. Ratio is Score / 100.
    double ratio = (2.0 * pans) / 100.0;
    quitp(ratio, "Partial score: Participant placed %d pieces successfully", pans);
  } else {
    // unnecessary
    quitf(_wa, "Participant placed 0 pieces");
  }
}