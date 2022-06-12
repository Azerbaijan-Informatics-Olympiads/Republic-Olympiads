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
	int T = atoi(argv[1]);
	int MAXN = atoi(argv[2]);
	int LBound = atoi(argv[3]); // LBound = 1 means L >= ceil(N / 3)
	int RBound = atoi(argv[4]); // L <= N / Rbond

	vector<int>N(T), L(T);
	for (int i = 0; i < T; ++i) {
    N[i] = rnd.next(1, MAXN);
    if (LBound) L[i] = rnd.next(max(1, N[i] / 3), max(1, N[i] / RBound));
    else L[i] = rnd.next(1, max(1, N[i] / RBound));
	}

	cout << T << ln;
  for (int i = 0; i < T; ++i) {
    cout << N[i] << ' ' << L[i] << ln;
  }
  return 0;
}
