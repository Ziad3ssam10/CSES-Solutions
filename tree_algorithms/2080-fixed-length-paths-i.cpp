#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using orderedset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//#define int long long
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

const int N = 2e5 + 5;

int n, k;
vector<int> adj[N];
bool done[N];
int sz[N];
ll ans = 0;

int freq[N];

int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v: adj[u]) {
        if (v == p || done[v]) continue;
        sz[u] += dfs_sz(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int p, int total) {
    for (int v: adj[u]) {
        if (v == p || done[v]) continue;
        if (sz[v] * 2 > total)
            return get_centroid(v, u, total);
    }
    return u;
}

void get_dist(int u, int p, int d, vector<int> &dist) {
    if (d > k) return;
    dist.push_back(d);
    for (int v: adj[u]) {
        if (v == p || done[v]) continue;
        get_dist(v, u, d + 1, dist);
    }
}

void solve_centroid(int c) {
    freq[0] = 1;
    int maxDepth = 0;

    for (int v: adj[c]) {
        if (done[v]) continue;

        vector<int> dist;
        get_dist(v, c, 1, dist);

        for (int d: dist)
            if (d <= k)
                ans += freq[k - d];

        for (int d: dist) {
            if (d <= k) {
                freq[d]++;
                maxDepth = max(maxDepth, d);
            }
        }
    }

    for (int i = 0; i <= maxDepth; i++)
        freq[i] = 0;
}

void decompose(int entry) {
    int total = dfs_sz(entry, -1);
    int c = get_centroid(entry, -1, total);

    solve_centroid(c);
    done[c] = true;

    for (int v: adj[c])
        if (!done[v])
            decompose(v);
}

void solve(int tc) {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(1);

    cout << ans << "\n";
}


signed main() {
    wady
 //   files();
    int t = 1;
    //   cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
