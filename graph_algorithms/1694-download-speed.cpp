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
int cap[N][N];
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

void solve(int tc) {
    cin >> n;
    int m;
    cin >> m;
    n += 10;
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        cap[u][v] += c;
    }
    int src = 1, sink = n - 10;
    cout << maxflow(src, sink) << endl;;
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
