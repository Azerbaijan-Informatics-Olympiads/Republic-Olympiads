#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int, int>
#define x first
#define y second

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
        constraints:
            1 <= n <= 1e5
            -1e9 <= s[i] <= 1e9
            0 <= d <= 1e9

        subtask 1:
            n <= 100

        subtask 2:
            n <= 1000

        subtask 3:
            -1000 <= s[i] <= 1000

        subtask 4:
            general

*/


void Print_Test(int n, int d, vector<int> &s) {
    out << n << ' ' << d << '\n';
    for(int i = 0; i < n; ++i) {
        if(i > 0) out << ' ';
        out << s[i];
    }
}

/// Generators start

int MaxN = 1e5;
int MaxD = 1e9;

void Cool_Test(int sub, int div) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d;
    if(sub == 3) {
        d = get_in_range(100, 1000);
    }else {
        d = get_in_range(100, MaxD / div);
    }

    vector<int>s(n);
    s[0] = get_in_range(-MaxD / 2, 0);
    for(int i = 1; i < n / 3; ++i) {
        if(i < n / 12) {
            s[i] = s[i - 1] + get_in_range(1, 2);
        }else if(i < n / 6) {
            s[i] = s[i - 1] + get_in_range(0, 1);
        }else if(i < n / 4) {
            s[i] = s[i - 1] + get_in_range(1, 2);
        }else {
            s[i] = s[i - 1] + get_in_range(0, 1);
        }
        if(s[i] > MaxD) {
            s[i] = get_in_range(-MaxD, MaxD);
        }
    }

    s[n - 1] = get_in_range(0, MaxD / 2);
    for(int i = n - 1; i >= n - n / 3; --i) {
        if(i >= n - n / 12) {
            s[i] = s[i - 1] + get_in_range(0, 1);
        }else if(i >= n - n / 6) {
            s[i] = s[i - 1] + get_in_range(1, 2);
        }else if(i >= n - n / 4) {
            s[i] = s[i - 1] + get_in_range(0, 1);
        }else {
            s[i] = s[i - 1] + get_in_range(1, 2);
        }
        if(s[i] > MaxD) {
            s[i] = get_in_range(-MaxD, MaxD);
        }
    }
    for(int i = n / 3; i < n - n / 3; ++i) {
        s[i] = get_in_range(-MaxD, MaxD);
    }
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_1(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    n = min(n, MaxD);
    int d = get_in_range(1, MaxD / n);

    vector<int>s(n);
    s[0] = -MaxD;
    for(int i = 1; i < n; ++i) {
        s[i] = s[i - 1] + get_in_range(d + 1, 2 * d);
    }
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_2(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    n = min(n, MaxD);
    int d = get_in_range(1, MaxD / n);

    vector<int>s(n);
    s[0] = -MaxD;
    for(int i = 1; i < n; ++i) {
        s[i] = s[i - 1] + get_in_range(d + 1, 2 * d);
    }
    s[n / 3] = s[n / 3 - 1] + d;
    s[2 * n / 3] = s[2 * n / 3 - 1] + d - 1;
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_3(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    n = min(n, MaxD);
    int d = get_in_range(1, MaxD / n);

    vector<int>s(n);
    s[0] = -MaxD;
    for(int i = 1; i < n; ++i) {
        s[i] = s[i - 1] + get_in_range(d + 1, 2 * d);
    }
    s[n / 3] = s[n / 3 - 1] + d;

    s[2 * n / 3] = s[2 * n / 3 - 1] + d / 2;
    s[2 * n / 3 + 1] = s[2 * n / 3] + d / 2;
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_N(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d = get_in_range(MaxD - 10, MaxD);

    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = get_in_range(0, MaxD) % (d + 1);
    }
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_N_1_pref(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d = get_in_range(MaxD / 2 - 10, MaxD / 2);

    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = get_in_range(0, MaxD) % (d + 1);
    }
    sort(s.begin(), s.end());
    s[n - 1] = s[0] + d + 1;
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_N_1_suff(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d = get_in_range(MaxD / 2 - 10, MaxD / 2);

    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = get_in_range(0, MaxD) % (d + 1);
    }
    sort(s.begin(), s.end());
    s[0] = s[n - 1] - (d + 1);
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_N_2_pref(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d = get_in_range(MaxD / 2 - 10, MaxD / 2);

    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = get_in_range(0, MaxD) % (d + 1);
    }
    sort(s.begin(), s.end());
    s[n - 2] = s[1] + d + 1;
    s[n - 1] = s[n - 2] + 1;
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_N_2_suff(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d = get_in_range(MaxD / 2 - 10, MaxD / 2);

    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = get_in_range(0, MaxD) % (d + 1);
    }
    sort(s.begin(), s.end());
    s[1] = s[n - 2] - (d + 1);
    s[0] = s[1] - 1;
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}

void Ans_N_2_mid(int sub) {
    int n = get_in_range(MaxN - 10, MaxN);
    int d = get_in_range(MaxD / 2 - 10, MaxD / 2);

    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        s[i] = get_in_range(0, MaxD) % (d + 1);
    }
    sort(s.begin(), s.end());
    s[0] = -(MaxD - 1);
    s[n - 1] = s[1] + d + 1;
    shuffle(s.begin(), s.end(), rng);
    Print_Test(n, d, s);
}
/// Generators end

void Generate_Test(int sub, int test_id) {
    string path = get_path("tests/sub", sub, test_id, ".in");
    out.open(path);

    if(test_id <= 2) {
        Cool_Test(sub, 100);
    }else if(test_id <= 4) {
        Cool_Test(sub, 100000);
    }else if(test_id == 5) {
        Ans_1(sub);
    }else if(test_id == 6) {
        Ans_2(sub);
    }else if(test_id == 7) {
        Ans_3(sub);
    }else if(test_id == 8) {
        Ans_N(sub);
    }else if(test_id == 9) {
        Ans_N_1_pref(sub);
    }else if(test_id == 10) {
        Ans_N_1_suff(sub);
    }else if(test_id == 11) {
        Ans_N_2_pref(sub);
    }else if(test_id == 12) {
        Ans_N_2_suff(sub);
    }else if(test_id == 13) {
        Ans_N_2_mid(sub);
    }

    out.close();
}

/// solution starts
void solve() {
    int n, d;
    in >> n >> d;
    assert(n >= 1 && n <= MaxN);
    assert(d >= 0 && d <= MaxD);
    vector<int>s(n);
    for(int i = 0; i < n; ++i) {
        in >> s[i];
        assert(s[i] >= -MaxD && s[i] <= MaxD);
    }
    sort(s.begin(), s.end());
    int max_range = 0;
    int l = 0, r = 0;
    while(l < n) {
        while(r < n && s[r] - s[l] <= d) {
            max_range = max(max_range, r - l + 1);
            ++r;
        }
        ++l;
    }
    out << max_range << '\n';
    cerr << "n = " << n << " ans = " << max_range << '\n';
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
    for(int sub = 1; sub <= 4; ++sub) {
        if(sub == 1) {
            MaxN = 100;
            MaxD = 1e9;
        }else if(sub == 2) {
            MaxN = 1000;
            MaxD = 1e9;
        }else if(sub == 3) {
            MaxN = 1e5;
            MaxD = 1000;
        }else {
            MaxN = 1e5;
            MaxD = 1e9;
        }
        int test_cnt = 13;
        for(int test_id = 1; test_id <= test_cnt; ++test_id) {
            Generate_Test(sub, test_id);
            cerr << sub << " " << test_id << " ";
            solve(sub, test_id);
        }
    }
}
/// Generation ends

int main(){
    //Generate();
    return 0;
}
