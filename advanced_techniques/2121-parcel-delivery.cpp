#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using orderedset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define ll long long
#define ld long double
#define endl '\n'
#define wady                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}


struct Edge {
    int u, v;
    int cap, cost;
    int rev;
};

struct MCMF {
    int n, src, sink;
    vector<vector<Edge> > adj;
    vector<int> dist;
    vector<int> par_v, par_e;

    const ll INF = (ll) 4e18;

    MCMF(int n,int src,int sink) : n(n), src(src), sink(sink) {
        adj.assign(n + 2, {});
        dist.assign(n + 2, 0);
        par_v.assign(n + 2, -1);
        par_e.assign(n + 2, -1);
    }

    void add_edge(int u,int v,int cap,int cost) {
        adj[u].push_back({u, v, cap, cost, (int) adj[v].size()});
        adj[v].push_back({v, u, 0, -cost, (int) adj[u].size() - 1});
    }

    void SPFA() {
        dist.assign(n + 2, INF);
        par_v.assign(n + 2, -1);
        par_e.assign(n + 2, -1);
        vector<bool> inq(n + 2, false);

        queue<int> q;
        dist[src] = 0;
        q.push(src);
        inq[src] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            inq[node] = false;

            for (int i = 0; i < (int) adj[node].size(); i++) {
                auto &e = adj[node][i];
                if (e.cap > 0 and dist[e.v] > dist[node] + e.cost) {
                    dist[e.v] = dist[node] + e.cost;
                    par_v[e.v] = node;
                    par_e[e.v] = i;
                    if (!inq[e.v]) {
                        inq[e.v] = true;
                        q.push(e.v);
                    }
                }
            }
        }
    }

    pair<int,int> mincostflow(int k) {
        int flow = 0;
        int fcost = 0;

        while (flow < k) {
            SPFA();
            if (dist[sink] == INF) break;
            int f = k - flow;
            for (int cur = sink; cur != src; cur = par_v[cur])
                f = min(f, adj[par_v[cur]][par_e[cur]].cap);
            flow += f;
            fcost += f * dist[sink];
            for (int cur = sink; cur != src; cur = par_v[cur]) {
                auto &e = adj[par_v[cur]][par_e[cur]];
                e.cap -= f;
                adj[e.v][e.rev].cap += f;
            }
        }

        if (flow < k) return {-1, -1};
        return {flow, fcost};
    }
};


void solve(int tc) {
    int n, m, k;
    cin >> n >> m >> k;
    MCMF flows(n + 5, 1, n);
    while (m--) {
        int u, v, r, c;
        cin >> u >> v >> r >> c;
        flows.add_edge(u, v, r, c);
    }
    auto [flow,cost] = flows.mincostflow(k);
    cout << cost << endl;
}

signed main() {
    wady
    files();
    int t = 1;
    //  cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
