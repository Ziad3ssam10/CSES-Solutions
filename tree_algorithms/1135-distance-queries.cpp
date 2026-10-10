//██████╗ ██╗ ██████╗     ███████╗
//██╔══██╗██║██╔════╝     ╚══███╔╝
//██████╔╝██║██║  ███╗      ███╔╝
//██╔══██╗██║██║   ██║     ███╔╝
//██████╔╝██║╚██████╔╝    ███████╗
//╚═════╝ ╚═╝ ╚═════╝     ╚══════╝


#include <bits/stdc++.h>
using namespace std;

#define double long double
#define int  long long
#define ll long long
#define MX INT_MAX
#define MN INT_MIN
#define endl '\n'
#define wady ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
const char sp = ' ';
const int   MOD = 1e9 + 7, N = 200000+10, Log = 23;
const double pi = 3.14159265358979323846;
string YN[] = {"YES\n","NO\n"};
int  dx[] = {-1,1,0,0,-1,1,-1,1};
int  dy[] = {0,0,1,-1,-1,1,1,-1};

vector<int> adj[N];
int ancestor[N][22], level[N] , ans[N] , parent[N];
void build(int node = 1, int par = 0) {
    level[node] = level[par] + 1;
    ancestor[node][0] = par;
    for(int i = 1;i<22;++i) ancestor[node][i] = ancestor[ancestor[node][i - 1]][i - 1];
    for(int child : adj[node]) {
        if(child != par) {
            parent[child] = node;
            build(child, node);
        }
    }
}
int LCA(int u, int v) {
    if(level[u] < level[v]) swap(u, v);
    for(int i = 21;i>=0;--i) {
        if(level[ancestor[u][i]] >= level[v]) u = ancestor[u][i];
        if(u == v) return u;
    }
    for(int i = 21;i>=0;--i) {
        if(ancestor[u][i] != ancestor[v][i]) {
            u = ancestor[u][i];
            v = ancestor[v][i];
        }
    }
    return ancestor[u][0];
}



void solve() {
    int n,q;cin >> n >> q;
    for(int i = 0;i<n-1;i++){
        int u,v;cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build();
    while(q--) {
        int a, b;
        cin >> a >> b;
        int lca = LCA(a, b);
        int ans = (level[lca]-level[a]) + (level[lca]-level[b]);
        cout << -ans << endl;
    }

}


signed main() {
    wady
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int tt = 1;
  //  cin >> tt;
    while(tt--) {
       solve();
    }
}