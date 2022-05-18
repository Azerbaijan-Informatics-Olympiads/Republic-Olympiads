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

string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()[]{}";
int main(int argc, char* argv[]){
	registerGen(argc, argv, 1);
	int len = atoi(argv[1]);
	string S = "";
	for (int i = 0; i < len; ++i) {
    S += charset[rnd.next(0, size(charset) - 1)];
	}
	cout << S << ln;
  return 0;
}
