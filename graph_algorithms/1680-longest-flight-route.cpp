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
    vector<int> in(n + 5);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        in[v]++;
    }
    vector<int> dp(n + 5, -1);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.emplace(i);
    }
    vector<int> topo;
    while (q.size()) {
        auto node = q.front();
        q.pop();
        topo.emplace_back(node);
        for (auto child: adj[node]) {
            if (!(--in[child])) {
                q.emplace(child);
            }
        }
    }
    if (topo.size() != n) return cout << "IMPOSSIBLE\n", void();
    reverse(topo.begin(), topo.end());
    vector<int> par(n + 5);
    for (auto &u: topo) {
        dp[u] = (u == n ? 1 : -1);
        for (auto child: adj[u]) {
            if (dp[child] != -1) {
                dp[u] = max(dp[u], dp[child] + 1);
            }
        }
    }
    if (dp[1] == -1 or dp[1] == 0) return cout << "IMPOSSIBLE\n", void();
    int ans = dp[1];
    cout << ans << endl;

    int st = 1;

    for (int i = 0; i < ans; i++) {
        cout << st << " ";
        for (auto child: adj[st]) {
            if (dp[child] == dp[st] - 1) {
                st = child;
                break;
            }
        }
    }
    cout << endl;
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
