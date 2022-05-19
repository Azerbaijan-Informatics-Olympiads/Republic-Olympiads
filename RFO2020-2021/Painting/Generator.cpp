#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int, int>
#define f first
#define s second

using namespace std;

ifstream in;
ofstream out;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


int get_in_range(int l, int r) {
    return rng() % (r - l + 1) + l;
}

string get_path(string directory, int sub, int test_id, string ext) {
    string path = directory;
    path += to_string(sub);
    path += '_';
    if(test_id < 10) {
        path += '0';
    }
    path += to_string(test_id);
    path += ext;
    return path;
}


/// Generation starts

/*
    Generation Plan:
        ...

*/


void Print_Test(int n, vector<int> &v) {
    out << n << '\n';
    for(int i = 0; i < n; ++i) {
        if(i > 0) out << ' ';
        out << v[i];
    }
    out << '\n';
}

/// Generators start
    /// tests created by hand
/// Generators end

void Generate_Test(int sub, int test_id) {
    string path = get_path("tests/sub", sub, test_id, ".in");
    out.open(path);

    out.close();
}


/// solution starts
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool okay(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}
int score(int n, int m, vector<vector<char>> &p) {
    int res = 0;
    for(int x = 0; x < n; ++x) {
        for(int y = 0; y < m; ++y) {
            for(int k = 0; k < 4; ++k) {
                if(okay(x + dx[k], y + dy[k], n, m) && p[x][y] != p[x + dx[k]][y + dy[k]]) {
                    ++res;
                }
            }
        }
    }
    return res / 2;
}

int brute(int n, int m, vector<int> &cnt, string &color) {
    vector<vector<char>>board(n, vector<char>(m));
    vector<char>order;
    for(int k = 0; k < 3; ++k) {
        for(int i = 0; i < cnt[k]; ++i) {
            order.pb(color[k]);
        }
    }
    sort(order.begin(), order.end());
    int best_score = 0;
    do{
        int ptr = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                board[i][j] = order[ptr];
                ++ptr;
            }
        }
        best_score = max(best_score, score(n, m, board));
    }while(next_permutation(order.begin(), order.end()));
    return best_score;
}
void construct(int n, int m, vector<int> &cnt, string &color, vector<vector<char>> &res, int parity) {
    int done = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if((i + j) % 2 == parity) {
                res[i][j] = color[2];
                ++done;
            }
        }
    }
    /// first look at corners
    vector<int>row{0, n - 1}; /// maybe the same
    vector<int>col{0, m - 1}; /// maybe the same

    for(int r = 0; r < 2 && done < cnt[2]; ++r){
        for(int c = 0; c < 2 && done < cnt[2]; ++c) {
            if(res[row[r]][col[c]] == '?') {
                res[row[r]][col[c]] = color[2];
                ++done;
            }
        }
    }
    /// then sides
    for(int i = 0; i < m && done < cnt[2]; ++i) {
        if(res[0][i] == '?') {
            res[0][i] = color[2];
            ++done;
        }
    }
    for(int i = 0; i < m && done < cnt[2]; ++i) {
        if(res[n - 1][i] == '?') {
            res[n - 1][i] = color[2];
            ++done;
        }
    }
    for(int i = 0; i < n && done < cnt[2]; ++i) {
        if(res[i][0] == '?') {
            res[i][0] = color[2];
            ++done;
        }
    }
    for(int i = 0; i < n && done < cnt[2]; ++i) {
        if(res[i][m - 1] == '?') {
            res[i][m - 1] = color[2];
            ++done;
        }
    }

    /// then any
    for(int i = 0; i < n && done < cnt[2]; ++i) {
        for(int j = 0; j < m && done < cnt[2]; ++j) {
            if(res[i][j] == '?') {
                res[i][j] = color[2];
                ++done;
            }
        }
    }

    /// put color 1 & 0
    done = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(res[i][j] == '?') {
                if(done < cnt[1]) {
                    res[i][j] = color[1];
                    ++done;
                }else {
                    res[i][j] = color[0];
                }
            }
        }
    }
}
void solve() {
    string color = "qyg";
    int n, m;
    vector<int>cnt(3);
    in >> n >> m;
    in >> cnt[0] >> cnt[1] >> cnt[2];
    assert(cnt[0] + cnt[1] + cnt[2] == n * m);
    assert(cnt[0] != n * m && cnt[1] != n * m && cnt[2] != n * m);
    assert(cnt[0] >= 0 && cnt[1] >= 0 && cnt[2] >= 0);
    /// sort starts
    if(cnt[0] > cnt[1]) {
        swap(cnt[0], cnt[1]);
        swap(color[0], color[1]);
    }
    if(cnt[1] > cnt[2]) {
        swap(cnt[1], cnt[2]);
        swap(color[1], color[2]);
    }
    if(cnt[0] > cnt[1]) {
        swap(cnt[0], cnt[1]);
        swap(color[0], color[1]);
    }
    /// sort ends

    int best_score = 0;
    vector<vector<char>>res(n, vector<char>(m));
    if(cnt[2] * 2 >= n * m) {
        vector<vector<char>>odd(n, vector<char>(m, '?')), even(n, vector<char>(m, '?'));
        construct(n, m, cnt, color, odd, 1);
        construct(n, m, cnt, color, even, 0);

        int score_odd = score(n, m, odd);
        int score_even = score(n, m, even);

        if(score_odd > score_even) {
            res = odd;
            best_score = score_odd;
        }else {
            res = even;
            best_score = score_even;
        }
    }else {
        /// this one is easy, we get all pairs of cells in different colors
        /// there is a problem when n = 2 (except 2x2, this case is always handled above). So make n >= m
        bool rotated = false;
        if(n < m) {
            rotated = true;
            swap(n, m);
        }

        swap(cnt[0], cnt[1]);       /// put smallest in the middle (so no collision)
        swap(color[0], color[1]);

        vector<char>order;
        for(int k = 0; k < 3; ++k) {
            for(int i = 0; i < cnt[k]; ++i) {
                order.pb(color[k]);
            }
        }
        int ptr = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if((i + j) % 2 == 0) {
                    if(rotated) {
                        res[m - 1 - j][i] = order[ptr];
                    }else{
                        res[i][j] = order[ptr];
                    }
                    ++ptr;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if((i + j) % 2 == 1) {
                    if(rotated) {
                        res[m - 1 - j][i] = order[ptr];
                    }else{
                        res[i][j] = order[ptr];
                    }
                    ++ptr;
                }
            }
        }
        if(rotated) {
            swap(n, m);  /// rotate back
        }
        best_score = score(n, m, res);
        assert(best_score == n * (m - 1) + m * (n - 1));
    }
    ///assert(brute(n, m, cnt, color) == best_score);
    out << best_score << '\n';
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            out << res[i][j];
        }
        out << '\n';
    }
}
/// solution ends

void solve(int sub, int test_id) {
    string path_in = get_path("tests/sub", sub, test_id, ".in");
    string path_out = get_path("tests/sub", sub, test_id, ".out");
    in.open(path_in);
    out.open(path_out);

    /// call solution
        solve();

    in.close();
    out.close();
}

void Generate() {
    for(int sub = 1; sub <= 5; ++sub) {
        int test_count = 17;
        if(sub == 3) test_count = 20;
        if(sub == 5) test_count = 22;
        for(int test_id = 0; test_id < test_count; ++test_id) {
            cerr << sub << " " << test_id << endl;
            solve(sub, test_id);
        }
    }
}
/// Generation ends

int main(){
    Generate();
    return 0;
}
