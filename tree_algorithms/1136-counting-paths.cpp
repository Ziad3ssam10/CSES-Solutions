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

const int N = 2e5 + 10, LG = 22;
int n;
int parent[N][LG];
int lvl[N];
vector<int> adj[N];

void build(int node, int par, int d) {
    parent[node][0] = par;
    lvl[node] = d;
    for (int i = 1; i < LG; i++) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }
    for (auto &child: adj[node]) {
        if (child == par)continue;
        build(child, node, d + 1);
    }
}

int kth(int node, int k) {
    for (int i = LG - 1; i >= 0; i--) {
        if (k >> i & 1) {
            node = parent[node][i];
        }
    }
    return node;
}

int LCA(int u, int v) {
    if (lvl[u] < lvl[v])swap(u, v);
    u = kth(u, lvl[u] - lvl[v]);
    if (u == v)return u;
    for (int i = LG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i])u = parent[u][i], v = parent[v][i];
    }
    return parent[u][0];
}

int dist(int u, int v) {
    int lc = LCA(u, v);
    return lvl[u] + lvl[v] - 2 * lvl[lc];
}

int dp[N];

void dfs(int node,int par) {
    for (auto child: adj[node]) {
        if (child == par)continue;
        dfs(child, node);
        dp[node] += dp[child];
    }
}

void solve(int tc) {
    cin >> n;
    int q;
    cin >> q;
    int m = n - 1;
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    build(1, 0, 0);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int lc = LCA(a, b);
        dp[a]++, dp[b]++;
        dp[lc]--;
        dp[parent[lc][0]]--;
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)cout << dp[i] << " ";
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
