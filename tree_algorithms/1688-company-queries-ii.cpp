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

const int N = 2e5 + 20, LG = 24;
vector<int> adj[N];
int up[N][LG];
int depth[N];
int n;
int st[2 * N][LG], lg[2 * N];
int timer = 0;
vector<int> flat;
vector<int> depflat;
int in[N];

void build(int node,int par,int d) {
    depth[node] = d;
    up[node][0] = par;
    in[node] = flat.size();
    flat.emplace_back(node);
    depflat.emplace_back(d);
    for (auto child: adj[node]) {
        if (child == par)continue;
        build(child, node, d + 1);
        flat.emplace_back(node);
        depflat.emplace_back(d);
    }
}

void buildst() {
    int m = flat.size();
    lg[1] = 0;
    for (int i = 2; i <= m; i++)lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < m; i++)st[i][0] = i;
    for (int j = 1; (1 << j) <= m; j++) {
        for (int i = 0; i + (1 << j) <= m; i++) {
            int x = st[i][j - 1];
            int y = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (depflat[x] < depflat[y]) ? x : y;
        }
    }
}

int lcao1(int u,int v) {
    int l = in[u];
    int r = in[v];
    if (l > r)swap(l, r);
    int j = lg[r - l + 1];
    int x = st[l][j];
    int y = st[r - (1 << j) + 1][j];
    return (depflat[x] < depflat[y]) ? flat[x] : flat[y];
}

void solve(int tc) {
    int q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].emplace_back(i);
        adj[i].emplace_back(p);
    }
    build(1, 1, 0);
    buildst();
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lcao1(u, v) << endl;
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
