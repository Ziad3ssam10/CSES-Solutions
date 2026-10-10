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

vector<set<int>>vs;
vector<int>ans,col;
vector<vector<int>>adj;

void dfs(int node,int par) {
    vs[node].insert(col[node]);
    for (auto &child : adj[node]) {
        if (child == par) continue;
        dfs(child,node);
        if (vs[child].size() > vs[node].size())
            vs[child].swap(vs[node]);
        for (auto &item : vs[child]) {
            vs[node].insert(item);
        }
    }
    ans[node] = vs[node].size();
}

void solve(int tc) {
    int n;
    cin >> n;
    vs = vector<set<int>>(n+1);
    ans = col = vector<int>(n+1);
    adj = vector<vector<int>>(n+1);
    for (int i = 1;i <= n;i++) cin >> col[i];
    for (int i = 0;i < n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,-1);
    for (int i = 1;i <= n;i++) cout << ans[i] << ' ';
    cout << '\n';

}

signed main() {
    wady
    files();
    int t = 1;
    //    cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}