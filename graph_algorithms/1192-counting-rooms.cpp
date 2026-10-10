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
    vector<vector<bool> > vis(n, vector<bool>(m));
    auto valid = [&](int i, int j) {
        return i >= 0 and i < n and j >= 0 and j < m and a[i][j] != '#';
    };
    int ans = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j])continue;
            if (a[i][j] == '#') continue;
            queue<pair<int, int> > q;
            q.emplace(i, j);
            while (q.size()) {
                auto [x,y] = q.front();
                q.pop();
                vis[x][y] = 1;
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (!valid(nx, ny) or vis[nx][ny])continue;
                    q.emplace(nx, ny);
                    vis[nx][ny] = 1;
                }
            }
            ans++;
        }
    }
    cout << ans << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
