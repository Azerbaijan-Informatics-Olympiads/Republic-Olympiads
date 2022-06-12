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

int main(int argc, char* argv[]){
	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int Q1 = atoi(argv[3]); // number of type1 queries
	int Q2 = atoi(argv[4]); // number of type2 queries
  int Q = Q1 + Q2;
  int diagonal = atoi(argv[5]); // diagonal = 1 is main diagonal
  int maxD1 = atoi(argv[6]); // maximum diagonal bound for update
  int minD2 = atoi(argv[7]); // minimum diagonal bound for ask

  vector<pii>forUpdate, forAsk;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      if ((diagonal == 1 && i + j <= maxD1) || (diagonal == 2 && N - i + 1 + j <= maxD1)) {
        forUpdate.eb(mpr(i, j));
      }
      if ((diagonal == 1 && i + j >= minD2) || (diagonal == 2 && N - i + 1 + j >= minD2)) {
        forAsk.eb(mpr(i, j));
      }
    }
  }

  shuffle(all(forUpdate));
  int sizeUpd = size(forUpdate);
  int sizeAsk = size(forAsk);

  vector<int>t(Q), x(Q), y(Q);
  if (Q1 == Q2) {
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
    shuffle(pos.begin() + 1, pos.end()); // ensure t[0] = 1
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
