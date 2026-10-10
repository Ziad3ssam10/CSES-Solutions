#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define endl '\n'
#define wady ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1), radj(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    vector<int> vis(n + 1, 0);
    function<void(int, const vector<vector<int>> &)> dfs = [&](int node, const vector<vector<int>> &g) {
        vis[node] = 1;
        for (auto u: g[node]) if (!vis[u]) dfs(u, g);
    };
    dfs(1, adj);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cout << "NO" << endl << 1 << " " << i << endl;
            return;
        }
    }
    fill(vis.begin(), vis.end(), 0);
    dfs(1, radj);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cout << "NO" << endl << i << " " << 1 << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

signed main() {
    wady
    files();
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
