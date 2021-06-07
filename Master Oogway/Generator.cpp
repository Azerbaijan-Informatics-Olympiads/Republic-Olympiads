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
            1 <= n, m <= 1e9
            1 <= q <= 1e5
            1 <= x[i] <= n
            1 <= y[i] <= m
            (x[i], y[i]) pairs are unique

        1) random coordinates --> 2 tests in all subtasks
        2) increasing x, decreasing y, form point 1 to point q --> 1 test in all subtasks
        3) almost increasing x, decreasing y --> 1 test in all subtasks
        4) some increasing x, decreasing y --> 1 tests in all subtsaks
        5) Small answer --> 2 test in all subtasks
        6) 10, 30, 60% Full board --> 1 test in subtasks {2, 3, 4}
        subtask 1:
            constraints:
                q <= 10

        subtask 2:
            constraints:
                n, m <= 10

        subtask 3:
            constraints:
                n, m <= 50

        subtask 4:
            constraints:
                n, m <= 1000

        subtask 5:
            constraints:
                general


*/


void Print_Test(int n, int m, int q, vector<pii> &coins) {
    out << n << ' ' << m << '\n';
    out << q << '\n';
    for(int i = 0; i < q; ++i) {
        out << coins[i].x << ' ' << coins[i].y;
        if(i < q - 1) out << '\n';
    }
}

/// Generators start

int MaxNM = 1e9;
int MaxQ = 1e5;

void Random(int sub) {
    int n = get_in_range(2 * MaxNM / 3, MaxNM);
    int m = get_in_range(2 * MaxNM / 3, MaxNM);
    int q = get_in_range(2 * MaxQ / 3, MaxQ);
    if(sub == 2 || sub == 3) {
        q = min(q, n * m / 4);
    }
    set<pii>uni;
    vector<pii>coins(q);
    int i = 0;
    while(i < q) {
        coins[i].x = get_in_range(1, n);
        coins[i].y = get_in_range(1, m);
        if(uni.find(coins[i]) == uni.end()) {
            uni.insert(coins[i]);
            ++i;
        }
    }
    Print_Test(n, m, q, coins);
}

void IncX_decY(int sub, int inc_dec_level) {   /// level = 0 all inc_dec, level = 1, almost inc_dec, level = 2, some inc_dec
    int n = get_in_range(2 * MaxNM / 3, MaxNM);
    int m = get_in_range(2 * MaxNM / 3, MaxNM);
    int q = get_in_range(2 * MaxQ / 3, MaxQ);
    q = min(q, min(n, m));

    set<pii>uni;
    vector<pii>coins(q);
    vector<int>x, y;
    int q2;
    if(inc_dec_level == 0) {
        q2 = q;
    }else if(inc_dec_level == 1) {
        q2 = 2 * q / 3;
    }else {
        q2 = q / 3;
    }
    coins[0].x = get_in_range(1, 3);
    coins[0].y = get_in_range(m - 2, m);
    for(int i = 1; i < q2; ++i) {
        int rnd = get_in_range(0, 1);
        coins[i].x = coins[i - 1].x + rnd;
        coins[i].y = coins[i - 1].y - (1 - rnd);
        uni.insert(coins[i]);
    }
    assert((int)uni.size() != q2);
    int i = q2;
    /// from here on random
    while(i < q) {
        coins[i].x = get_in_range(1, n);
        coins[i].y = get_in_range(1, m);
        if(uni.find(coins[i]) == uni.end()) {
            uni.insert(coins[i]);
            ++i;
        }
    }
    shuffle(coins.begin(), coins.end(), rng);
    Print_Test(n, m, q, coins);
}

void Small_Ans(int sub) {
    int n = get_in_range(2 * MaxNM / 3, MaxNM);
    int m = get_in_range(2 * MaxNM / 3, MaxNM);
    int q = 0;

    vector<pii>coins;
    set<pii>uni;
    int x = 1, y = 1;
    while(x <= n && y <= m && q < MaxQ) {
        int rnd = get_in_range(1, 10);

        if(rnd == 1) {
            x -= get_in_range(0, 2);
            y += get_in_range(0, 2);
        }else if(rnd == 2) {
            y -= get_in_range(0, 2);
            x += get_in_range(0, 2);
        }else if(rnd == 3) {
            x -= get_in_range(0, 2);
            y -= get_in_range(0, 2);
        }else {
            x += get_in_range(0, 2);
            y += get_in_range(0, 2);
        }
        if(x > 0 && y > 0 && x <= n && y <= m && uni.find({x, y}) == uni.end()) {
            uni.insert({x, y});
            coins.pb({x, y});
            ++q;
        }
    }
    shuffle(coins.begin(), coins.end(), rng);
    Print_Test(n, m, q, coins);
}

void Full(int sub, int perc) {
    int q = MaxQ;
    int n, m;
    if(q == 10) {
        n = 2, m = 5;
    }else {
        n = 400, m = 250;
        n = min(n, MaxNM);
        m = min(m, MaxNM);
    }
    vector<pii>coins;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(get_in_range(1, 100) <= perc) {
                coins.pb({i, j});
            }
        }
    }
    q = (int)coins.size();
    shuffle(coins.begin(), coins.end(), rng);
    Print_Test(n, m, q, coins);
}
/// Generators end

void Generate_Test(int sub, int test_id) {
    string path = get_path("tests/sub", sub, test_id, ".in");
    out.open(path);
    if(sub == 1) {
        MaxNM = 1e9;
        MaxQ = 10;
    }else if(sub == 2) {
        MaxNM = 10;
        MaxQ = 1e5;
    }else if(sub == 3) {
        MaxNM = 50;
        MaxQ = 1e5;
    }else if(sub == 4) {
        MaxNM = 1000;
        MaxQ = 1e5;
    }else if(sub == 5) {
        MaxNM = 1e9;
        MaxQ = 1e5;
    }
    if(test_id <= 2) {
        Random(sub);
    }else if(test_id <= 5) {
        IncX_decY(sub, test_id - 3);
    }else if(test_id <= 7) {
        Small_Ans(sub);
    }else if(test_id == 8) {
        Full(sub, 10);
    }else if(test_id == 9) {
        Full(sub, 30);
    }else if(test_id == 10) {
        Full(sub, 60);
    }
    out.close();
}

/// solution starts
void solve() {
    int n, m, q;
    in >> n >> m >> q;
    assert(n >= 1 && n <= MaxNM && m >= 1 && m <= MaxNM);
    assert(q >= 1 && q <= MaxQ);
    set<pii>uni;
    vector<pii>coins(q);
    for(int i = 0; i < q; ++i) {
        in >> coins[i].x >> coins[i].y;
        assert(coins[i].x >= 1 && coins[i].x <= n && coins[i].y >= 1 && coins[i].y <= m);
        uni.insert(coins[i]);
    }
    assert((int)uni.size() == q);
    sort(coins.begin(), coins.end());
    multiset<int>ys;
    ys.insert(coins[0].y);
    for(int i = 1; i < q; ++i) {
        auto itr = ys.upper_bound(coins[i].y);
        if(itr != ys.begin()) {
            --itr;
            ys.erase(itr);
        }
        ys.insert(coins[i].y);
    }
    cerr << (int)ys.size() << endl;
    out << (int)ys.size() << '\n';
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
        if(sub == 1) {
            MaxNM = 1e9;
            MaxQ = 10;
        }else if(sub == 2) {
            MaxNM = 10;
            MaxQ = 1e5;
        }else if(sub == 3) {
            MaxNM = 50;
            MaxQ = 1e5;
        }else if(sub == 4) {
            MaxNM = 1000;
            MaxQ = 1e5;
        }else if(sub == 5) {
            MaxNM = 1e9;
            MaxQ = 1e5;
        }
        int test_cnt = 10;
        if(sub == 1) test_cnt = 7;
        if(sub == 5) test_cnt = 8;
        for(int test_id = 1; test_id <= test_cnt; ++test_id) {
            //Generate_Test(sub, test_id);
            cerr << sub << " " << test_id << " ";
            solve(sub, test_id);
        }
    }
}
/// Generation ends

int main(){
    Generate();
    return 0;
}
