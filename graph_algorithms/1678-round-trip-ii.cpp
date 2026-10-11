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
    vector<vector<int> > adj(n + 5);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    int start = 0, finish = 0;
    vector<int> vis(n + 5), par(n + 5);
    function<void(int node)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v: adj[u]) {
            if (vis[v] == 0) {
                par[v] = u;
                dfs(v);
                if (start)
                    return;
            } else if (vis[v] == 1) {
                finish = u;
                start = v;
                return;
            }
        }
        vis[u] = 2;
    };

    for (int i = 1; i <= n and !start; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    if (!start)return cout << "IMPOSSIBLE\n", void();
    vector<int> ans;
    ans.emplace_back(start);
    for (int u = finish; u != start; u = par[u]) {
        ans.emplace_back(u);
    }
    ans.emplace_back(start);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto &i: ans)cout << i << " ";
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
