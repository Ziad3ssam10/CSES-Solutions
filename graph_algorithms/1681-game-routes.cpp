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
    vector<int> dp(n + 5, 0);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.emplace(i);
    }
    const int MOD = 1e9 + 7;
    dp[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: adj[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
            in[v]--;
            if (in[v] == 0)
                q.push(v);
        }
    }
    cout << dp[n] << endl;
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
