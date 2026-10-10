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

const int N = 500 + 20;
int n;
int par[N];
vector<int> adj[N];
int cap[N][N], org[N][N];
int getflow(int src,int sink) {
    for (int i = 0; i <= n; i++)par[i] = -1;
    par[src] = -2;
    queue<pair<int,int> > q; // node, flow
    q.emplace(src, 1e18);
    while (q.size()) {
        auto [node , flow] = q.front();
        q.pop();
        for (auto child: adj[node]) {
            if (par[child] == -1 and cap[node][child] > 0) {
                par[child] = node;
                int nflow = min(flow, cap[node][child]);
                if (child == sink)return nflow;
                q.emplace(child, nflow);
            }
        }
    }
    return 0;
}

int maxflow(int src,int sink) {
    int flow = 0;
    while (true) {
        int nflow = getflow(src, sink);
        if (nflow == 0)break;
        flow += nflow;
        int cur = sink;
        while (cur != src) {
            int parent = par[cur];
            cap[parent][cur] -= nflow;
            cap[cur][parent] += nflow;
            cur = par[cur];
        }
    }
    return flow;
}

vector<vector<int> > buildpaths(int src,int sink) {
    vector<vector<int> > ret;
    while (true) {
        vector<int> path;
        path.emplace_back(src);
        function<bool(int)> dfs = [&](int node) {
            if (node == sink)return 1;
            for (auto child: adj[node]) {
                if (org[node][child] > cap[node][child]) {
                    org[node][child]--;
                    path.emplace_back(child);
                    if (dfs(child))return 1;
                    path.pop_back();
                    org[node][child]++;
                }
            }
            return 0;
        };
        if (!dfs(src))break; /*
        path.emplace_back(sink);*/
        ret.emplace_back(path);
    }
    return ret;
}

void solve(int tc) {
    cin >> n;
    int m;
    cin >> m;
    n += 10;
    vector<pair<int,int> > edges;
    while (m--) {
        int u, v, c = 1;
        cin >> u >> v;
        edges.emplace_back(u, v);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        cap[u][v] += c, cap[v][u] += c;;
        org[u][v] += c;
    }
    int src = 1, sink = n - 10;
    cout << maxflow(src, sink) << endl;
    vector<bool> vis(n + 20, 0);
    function<void(int)> dfs = [&](int node) {
        vis[node] = 1;
        for (auto child: adj[node]) {
            if (!vis[child] and cap[node][child] > 0) {
                dfs(child);
            }
        }
    };
    dfs(src);
    for (auto [u,v]: edges) {
        if (vis[u] != vis[v]) {
            cout << u << " " << v << endl;
        }
    }
}

signed main() {
    wady
    files();
    int t = 1;
    // cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
