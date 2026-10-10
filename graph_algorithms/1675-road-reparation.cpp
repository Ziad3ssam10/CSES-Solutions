#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define ll long long
#define ld long double
#define endl '\n'
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define wady ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}

int temp = 0;
struct DSU {
    vector<int> par, sz;


    DSU(int n) {
        par.resize(n);
        sz.assign(n, 1);
        for (int i = 0; i < n; i++) {
            par[i] = i;
        }
    }

    int find(int x) {
        if (par[x] != x) par[x] = find(par[x]);
        return par[x];
    }

    bool union_set(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        temp++;
        return true;
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

struct edge {
    int u, v;
    ll w;

    bool operator<(const edge &other) const {
        return w < other.w;
    }
};

void solve(int tc) {
    int n,m;cin >> n >> m;
    vector<edge>a(m);
    for(auto &[u,v,x] :a)cin >> u >> v >> x;
    sort(a.begin(),a.end());
    int ans = 0;
    DSU dsu(n + 5);
    for(auto &[u,v,w] : a){
        if(dsu.same(u,v))continue;
        dsu.union_set(u,v);
        ans += w;
    }
    if(temp != n -1)cout << "IMPOSSIBLE\n";
    else cout << ans << endl;
}


signed main() {
    wady
   // files();
    int tc = 1;
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve(tc++);
    }
}
