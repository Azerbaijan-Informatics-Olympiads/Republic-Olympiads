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

  vector<int>t(Q), x(Q), y(Q);
  for (int i = 0; i < Q; ++i) {
    x[i] = rnd.next(1, N);
    y[i] = rnd.next(1, M);
  }
  vector<int>pos(Q);
  for (int i = 0; i < Q; ++i) {
    pos[i] = i;
  }
  shuffle(pos.begin() + 1, pos.end()); // ensure t[0] = 1
  for (int i = 0; i < Q; ++i) {
    if (i < Q1) t[pos[i]] = 1;
    else t[pos[i]] = 2;
  }

  cout << N << ' ' << M << ' ' << Q << ln;
  for (int i = 0; i < Q; ++i) {
    cout << t[i] << ' ' << x[i] << ' ' << y[i] << ln;
  }
  return 0;
}
