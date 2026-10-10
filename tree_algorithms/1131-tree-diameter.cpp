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

const int N = 2e5 + 20;
vector<int> adj[N];
int mxnode = 0, mxdepth = 0;

void dfs(int node,int par,int d) {
    if (d > mxdepth) {
        mxdepth = d;
        mxnode = node;
    }
    for (auto child: adj[node]) {
        if (child == par)continue;
        dfs(child, node, d + 1);
    }
}


void solve(int tc) {
    int n;
    cin >> n;
    int m = n - 1;
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    mxnode = -1, mxdepth = -1;
    dfs(1, 0, 0);
    mxdepth = -1;
    dfs(mxnode, 0, 0);
    cout << mxdepth << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
