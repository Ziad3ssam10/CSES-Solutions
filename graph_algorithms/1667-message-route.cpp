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
        adj[v].emplace_back(u);
    }
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    pq.emplace(0, 1);
    vector<int> dist(n + 5, 1e9);
    vector<int> par(n + 2, -1);
    dist[1] = 0;
    while (pq.size()) {
        auto [cost,node] = pq.top();
        pq.pop();
        for (auto child: adj[node]) {
            int ncost = cost + 1;
            if (ncost < dist[child]) {
                dist[child] = ncost;
                par[child] = node;
                pq.emplace(dist[child], child);
            }
        }
    }
    if (dist[n] == 1e9) {
        return cout << "IMPOSSIBLE\n", void();
    }
    cout << dist[n] + 1 << endl;
    int cut = n;
    vector<int> path;
    while (cut != -1) {
        path.emplace_back(cut);
        cut = par[cut];
    }
    reverse(path.begin(), path.end());
    for (auto &i: path)cout << i << " ";
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
