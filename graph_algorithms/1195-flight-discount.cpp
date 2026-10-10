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

#define int ll

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int> > > adj(n + 2);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
       // adj[v].emplace_back(u, c);
    }
    vector<array<int, 2> > dist(n + 2);
    for (int i = 0; i <= n; i++) {
        dist[i] = {(int) 1e18, (int) 1e18};
    }
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<> > pq;
    pq.emplace(0, 1, 0);
    dist[1][0] = 0;
    while (pq.size()) {
        auto [cost,node,state] = pq.top();
        pq.pop();
        if (cost > dist[node][state])continue;
        for (auto [child,cos]: adj[node]) {
            int ncost = cost + cos;
            if (ncost < dist[child][state]) {
                dist[child][state] = ncost;
                pq.emplace(ncost, child, state);
            }
            if (state == 0) {
                ncost = cost + cos / 2;
                int nstate = 1;
                if (ncost < dist[child][nstate]) {
                    dist[child][nstate] = ncost;
                    pq.emplace(ncost, child, nstate);
                }
            }
        }
    }
    int ans = min(dist[n][0], dist[n][1]);
    if (ans >= (int)1e18) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    //  cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
