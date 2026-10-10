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
bool match[N];
int ans = 0;

void dfs(int node,int par) {
    for (auto child: adj[node]) {
        if (child == par)continue;;
        dfs(child, node);
        if (!match[node] and !match[child]) {
            match[node] = match[child] = 1;
            ans++;
        }
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
    dfs(1, 0);
    cout << ans << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
