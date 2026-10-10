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

const int N = 3001;
char g[N][N];
bool vis[N][N];
int dx[]{0, 1};
int dy[]{1, 0};

void solve(int tc) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    vector<pair<int, int> > temp;
    string res;
    temp.emplace_back(0, 0);
    vis[0][0] = true;
    while (res.size() != 2 * n - 1) {
        res += g[temp[0].first][temp[0].second];
        int mn = 'Z';
        vector<pair<int, int> > n_available;
        for (auto &[i , j]: temp) {
            for (int k = 0; k < 2; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 and ni < n and nj >= 0 and nj < n and !vis[ni][nj]) {
                    vis[ni][nj] = true;
                    if (g[ni][nj] < mn) mn = g[ni][nj], n_available.clear(), n_available.emplace_back(ni, nj);
                    else if (g[ni][nj] == mn) {
                        n_available.emplace_back(ni, nj);
                    }
                }
            }
        }
        temp.swap(n_available);
    }
    cout << res << '\n';
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
    return 0;
}
