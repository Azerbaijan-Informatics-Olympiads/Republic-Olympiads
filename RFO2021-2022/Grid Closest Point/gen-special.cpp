#include "testlib.h"
#include <bits/stdc++.h>
#define pii pair<int, int>
#define piii pair<pii, int>
#define vi vector<int>
#define vvi vector<vi>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define x first
#define y second
#define oo 1000000001
#define eb emplace_back
#define pb push_back
#define mpr make_pair
#define size(v) (int)v.size()
#define ln '\n'
#define ull unsigned long long
#define ll long long
#define all(v) v.begin(), v.end()

using namespace std;

/*
creates test like
    2..................*
    ..................**
    .................***
    ................****
    ...............*****
    ..............******
    .............*******
    ............********
    ...........*********
    1.........**********

    2 is a rangeAsk x rangeAsk rectangle for ask queries
    1 is a rangeClosest x rangeClosest rectangle for the closest red cells
    *s are red cells but not the closest

*/

bool cmp_dr1(pii p1, pii p2) {
  return p1.x + p1.y > p2.x + p2.y;
}

vector<pii> order_updates(int dr, int N, int M, int Q1, int rangeAsk, int rangeClosest) {
  if (dr == 2) {
    swap(N, M);
	}

  vector<pii>closestReds;
  for (int i = N; i > N - rangeClosest; --i) {
    for (int j = rangeClosest; j >= 1; --j) {
      closestReds.eb(mpr(i, j));
    }
  }
  sort(all(closestReds), cmp_dr1);

  vector<pii>forUpdate;
  int row_id = 1;
  vector<vector<int>>s(N + 1);
  int sizeClosest = size(closestReds);
  int d = (Q1 + sizeClosest - 1) / sizeClosest;
  for (int i = 0; i < Q1; ++i) {
    if (i % d == 0) {
      forUpdate.eb(closestReds[i / d]);
    } else {
      while (row_id <= N) {
        int y;
        if (s[row_id].empty()) {
          y = M;
        } else {
          y = s[row_id].back() - 1;
        }
        if (row_id + y > closestReds[i / d].x + closestReds[i / d].y + rangeAsk) {
          forUpdate.eb(mpr(row_id, y));
          s[row_id].eb(y);
          ++row_id; if (row_id == N + 1) row_id = 1;
          break;
        } else {
          ++row_id; if (row_id == N + 1) row_id = 1;
        }
      }
    }
  }
  if (dr == 2) {
    swap(N, M);
    for (pii &p : forUpdate) {
      swap(p.x, p.y);
    }
  }
  return forUpdate;
}
int main(int argc, char* argv[]){
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int Q1 = atoi(argv[3]); // number of type1 queries
	int Q2 = atoi(argv[4]); // number of type2 queries
	int preQ1 = Q1 - atoi(argv[5]); // number of type1 queries at the beginning
  int Q = Q1 + Q2;

	int dr = atoi(argv[6]); // dr = 1 against row based set solution, dr = 2 against column based set solution in subtask5
	int rangeAsk = atoi(argv[7]);  // rangeAsk x rangeAsk rectangle for ask queries
	int rangeClosest = atoi(argv[8]); // rangeClosest x rangeClosest rectangle for the closest red cells

	vector<pii>forAsk;
  for (int i = 1; i <= rangeAsk; ++i) {
    for (int j = 1; j <= rangeAsk; ++j) {
      forAsk.eb(mpr(i, j));
    }
  }
  vector<pii>forUpdate = order_updates(dr, N, M, Q1, rangeAsk, rangeClosest);
  int sizeUpd = size(forUpdate);
  int sizeAsk = size(forAsk);

  vector<int>t(Q), x(Q), y(Q);
  if (Q1 == Q2 && preQ1 == 0) {
    for (int i = 0; i < Q1; ++i) {
      t[i * 2] = 1;
      x[i * 2] = forUpdate[i % sizeUpd].x;
      y[i * 2] = forUpdate[i % sizeUpd].y;

      int idx = rnd.next(1, sizeAsk) - 1;
      t[i * 2 + 1] = 2;
      x[i * 2 + 1] = forAsk[idx].x;
      y[i * 2 + 1] = forAsk[idx].y;
    }
  } else {
    vector<int>pos(Q);
    for (int i = 0; i < Q; ++i) {
      pos[i] = i;
    }
    shuffle(pos.begin() + preQ1, pos.end()); // ensure t[0...preQ1-1] = 1
    for (int i = 0; i < Q; ++i) {
      if (i < Q1) t[pos[i]] = 1;
      else t[pos[i]] = 2;
    }
    int ptr1 = 0;
    for (int i = 0; i < Q; ++i) {
      if (t[i] == 1) {
        x[i] = forUpdate[ptr1].x;
        y[i] = forUpdate[ptr1++].y;
        if (ptr1 == sizeUpd) ptr1 = 0;
      } else {
        int idx = rnd.next(1, sizeAsk) - 1;
        x[i] = forAsk[idx].x;
        y[i] = forAsk[idx].y;
      }
    }
  }
  cout << N << ' ' << M << ' ' << Q << ln;
  for (int i = 0; i < Q; ++i) {
    cout << t[i] << ' ' << x[i] << ' ' << y[i] << ln;
  }
  return 0;
}
