/*
	author Rashad Mammadov	
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int dx[] = {1, 0};
int dy[] = {0, 1};

bool okay(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int score(int n, int m, vector<string> &p) {
    int res = 0;
    for(int x = 0; x < n; ++x) {
        for(int y = 0; y < m; ++y) {
            for(int k = 0; k < 2; ++k) {
                if(okay(x + dx[k], y + dy[k], n, m) && p[x][y] != p[x + dx[k]][y + dy[k]]) {
                    ++res;
                }
            }
        }
    }
    return res;
}

bool Validate(ifstream &f, int n, int m, vector<int> &cnt, string &color, vector<string> &p) {
    vector<int>sol_cnt(3, 0);
    for(int i = 0; i < n; ++i) {
   	if(f.eof()) {
      	    return false;
    	}
    	getline(f, p[i]);
    	if(p[i].back() == '\r') p[i].pop_back();
    	if(p[i].back() == '\n') p[i].pop_back();
    	if((int)p[i].size() != m) {
    	    return false;
    	}
        for(int j = 0; j < m; ++j) {
            if(p[i][j] == color[0]) {
                ++sol_cnt[0];
            }else if(p[i][j] == color[1]) {
                ++sol_cnt[1];
            }else if(p[i][j] == color[2]) {
                ++sol_cnt[2];
            }else {
                return false;
            }
        }
    }
    for(int i = 0; i < 3; ++i) {
        if(sol_cnt[i] != cnt[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
	
    ifstream fout, fin, fans;
    fout.open(argv[3]);
    fans.open(argv[2]);
    fin.open(argv[1]);

    int Judge_Score;
    fans >> Judge_Score;

    int n, m;
    vector<int>cnt(3);
    string color = "qyg";

    fin >> n >> m;
    fin >> cnt[0] >> cnt[1] >> cnt[2];

    vector<string>painting(n);
    if(!Validate(fout, n, m, cnt, color, painting)) {
        fprintf(stderr, "Output isn't correct\n");
        printf("0.0\n");
    }else {
        int Sol_Score = score(n, m, painting);
	if(Sol_Score > Judge_Score) {
	    fprintf(stderr, "Output is super correct!\n");
            printf("1.0\n");
        }else if (Sol_Score == Judge_Score) {
            fprintf(stderr, "Output is correct\n");
            printf("1.0\n");
        } else {
            fprintf(stderr, "Output is partially correct\n");
            long double eps = (long double)Sol_Score / (long double)Judge_Score;
            eps = eps * eps;
            printf("%.3Lf\n", eps);
        }
    }
    return 0;
}
