#include <bits/stdc++.h>
using namespace std;

#define double long double
#define int long long
#define ll int
#define MX LLONG_MAX
#define MN INT_MIN
#define endl '\n'
#define wady ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
int mod = 1e9+7;


void solve() {
    int n, m;cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, c;cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
    }

    vector<int> dist(n + 1, MX),mini(n + 1, n), maxi(n + 1, 0), nofways(n + 1, 0);
    vector<bool> vis(n + 1, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[1] = 0;
    nofways[1] = 1;
    mini[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (vis[node]) continue;
        vis[node] = true;

        for (auto [child, c] : adj[node]) {
            int newcost = c + dist[node];

            if (newcost == dist[child]) {
                nofways[child] = (nofways[child] + nofways[node]) % mod;
                mini[child] = min(mini[child], mini[node] + 1);
                maxi[child] = max(maxi[child], maxi[node] + 1);
            } else if (newcost < dist[child]) {
                dist[child] = newcost;
                nofways[child] = nofways[node];
                mini[child] = mini[node] + 1;
                maxi[child] = maxi[node] + 1;
                pq.push({dist[child], child});
            }
        }
    }

    cout << dist[n] << " " << nofways[n] << " " << mini[n] << " " << maxi[n] << endl;
}



signed main() {
    wady


#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int tt = 1; //cin >> tt;
    while(tt--) solve();
}
