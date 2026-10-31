#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using orderedset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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

struct DSU {
    int n;
    vector<int> par, sz;
    int comps, maxi = 1;

    DSU(int _n) {
        n = _n + 1;
        par.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(par.begin(), par.end(), 0);
        comps = n - 1;
        maxi = 1;
    }

    int find(int node) {
        if (node == par[node])return node;
        return par[node] = find(par[node]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)return;
        par[u] = v;
        sz[v] += sz[u];
        maxi = max(maxi, sz[v]);
        comps--;
    }
};

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        dsu.merge(u, v);
        cout << dsu.comps << " " << dsu.maxi << endl;
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
