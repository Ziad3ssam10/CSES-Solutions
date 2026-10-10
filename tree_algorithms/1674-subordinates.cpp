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
int sz[N];

void dfs(int node,int par) {
    sz[node] = 1;
    for (auto child: adj[node]) {
        if (child == par)continue;
        dfs(child, node);
        sz[node] += sz[child];
    }
}


void solve(int tc) {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[i].emplace_back(p);
        adj[p].emplace_back(i);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)cout << sz[i] - 1 << " ";
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
