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

const int N = 2e5 + 20;
int n, sz[N], par[N];
bool done[N];
vector<int> adj[N];

int update_sz(int node, int parent) {
    sz[node] = 1;
    for (auto child: adj[node]) {
        if (child == parent or done[child]) continue;
        sz[node] += update_sz(child, node);
    }
    return sz[node];
}

int get_centroid(int node, int parent, int total) {
    for (auto child: adj[node]) {
        if (child == parent or done[child]) continue;
        if (sz[child] * 2 > total)
            return get_centroid(child, node, total);
    }
    return node;
}

int decompose(int node, int parent) {
    int total = update_sz(node, -1);
    int centroid = get_centroid(node, -1, total);
    done[centroid] = 1;
    par[centroid] = parent;
    for (auto child: adj[centroid]) {
        if (!done[child])
            decompose(child, centroid);
    }
    return centroid;
}

void solve(int tc) {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int root = decompose(0, -1);
    cout << root + 1 << endl;
}

signed main() {
    wady
 //   files();
    int t = 1;
    //    cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
