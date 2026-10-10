#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using orderedset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long
#define ld long double
#define endl '\n'
#define fast_io                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}


void solve(int tc) {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &i: a)cin >> i;
    vector<vector<int> > dist(n, vector<int>(m, -1));
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    auto valid = [&](int i, int j) {
        return i >= 0 and i < n and j >= 0 and j < m and a[i][j] != '#';
    };
    queue<pair<int, int> > q;
    pair<int, int> en;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'A')q.emplace(i, j), dist[i][j] = 0;
            if (a[i][j] == 'B')en = {i, j};
        }
    }
    vector<vector<int> > par(n, vector<int>(m, -1));
    while (q.size()) {
        auto [x,y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!valid(nx, ny) or dist[nx][ny] != -1)continue;
            dist[nx][ny] = dist[x][y] + 1;
            par[nx][ny] = k;
            q.emplace(nx, ny);
        }
    }
    char dir_char[] = {'U', 'D', 'R', 'L'};
    auto [x,y] = en;
    if (dist[x][y] == -1)cout << "NO\n";
    else {
        cout << "YES\n";
        cout << dist[en.first][en.second] << endl;
        string path = "";
        int cx = en.first, cy = en.second;
        while (a[cx][cy] != 'A') {
            int k = par[cx][cy];
            path += dir_char[k];
            cx -= dx[k];
            cy -= dy[k];
        }
        reverse(path.begin(), path.end());
        cout << path << endl;
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
