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


const int inf = 1e15;
struct Edge {
    int u, v, w;
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    vector<vector<int>> adj(n + 1), radj(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        edges[i] = {a, b, -x}; 
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    vector<long long> dist(n + 1, inf);
    dist[1] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (auto &e: edges) {
            if (dist[e.u] < inf and dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    vector<bool> reach1(n + 1), reachn(n + 1);
    {
        queue<int> q;
        q.push(1);
        reach1[1] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj[u])
                if (!reach1[v]) {
                    reach1[v] = true;
                    q.push(v);
                }
        }
    }
    {
        queue<int> q;
        q.push(n);
        reachn[n] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: radj[u])
                if (!reachn[v]) {
                    reachn[v] = true;
                    q.push(v);
                }
        }
    }

    for (auto &e: edges) {
        if (dist[e.u] < inf and dist[e.v] > dist[e.u] + e.w) {
            if (reach1[e.u] and reachn[e.v]) {
                cout << -1 << "\n";
                return;
            }
        }
    }

    cout << -dist[n] << "\n";
}

signed main() {
    wady
//    files();
    int tt = 1;
    //cin >> tt;
    while (tt--) solve();
}
