#include <bits/stdc++.h>
using namespace std;
#define int long long
#define wady ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

struct Tarjan {
    int n, timer = 0;
    vector<int> tin, low;
    vector<pair<int,int>> st;
    vector<vector<int>> comps;
    vector<vector<int>> adj;
    Tarjan(int n): n(n), tin(n+1, -1), low(n+1, -1), adj(n+1) {}
    void addEdge(int u, int v){ adj[u].push_back(v), adj[v].push_back(u); }
    void dfs(int v, int p=-1) {
        tin[v] = low[v] = ++timer;
        for(int to: adj[v]) {
            if(to == p) continue;
            if(tin[to] == -1) {
                st.push_back({v,to});
                dfs(to,v);
                low[v] = min(low[v], low[to]);
                if(low[to] >= tin[v]) {
                    vector<int> comp;
                    while(true) {
                        auto e = st.back(); st.pop_back();
                        comp.push_back(e.first);
                        comp.push_back(e.second);
                        if(e.first==v && e.second==to) break;
                    }
                    sort(comp.begin(), comp.end());
                    comp.erase(unique(comp.begin(), comp.end()), comp.end());
                    comps.push_back(comp);
                }
            } else if(tin[to] < tin[v]) {
                st.push_back({v,to});
                low[v] = min(low[v], tin[to]);
            }
        }
    }
    void run() {
        for(int i=1;i<=n;i++) if(tin[i]==-1) dfs(i);
    }
};

struct LCA {
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    LCA(int n): n(n), LOG(__lg(n)+1), depth(n+1), up(LOG, vector<int>(n+1)), adj(n+1) {}
    void addEdge(int u,int v){ adj[u].push_back(v), adj[v].push_back(u); }
    void dfs(int v,int p){
        up[0][v] = p==-1? v:p;
        for(int i=1;i<LOG;i++) up[i][v]=up[i-1][up[i-1][v]];
        for(int to:adj[v]) if(to!=p){
            depth[to]=depth[v]+1;
            dfs(to,v);
        }
    }
    void build(int root=1){ dfs(root,-1); }
    int get(int a,int b){
        if(depth[a]<depth[b]) swap(a,b);
        int diff=depth[a]-depth[b];
        for(int i=0;i<LOG;i++) if(diff>>i&1) a=up[i][a];
        if(a==b) return a;
        for(int i=LOG-1;i>=0;i--) if(up[i][a]!=up[i][b]) a=up[i][a], b=up[i][b];
        return up[0][a];
    }
    int dist(int a,int b){ return depth[a]+depth[b]-2*depth[get(a,b)]; }
};

int32_t main(){
    wady
    int n,m,q; cin>>n>>m>>q;
    Tarjan tj(n);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        tj.addEdge(u,v);
    }
    tj.run();

    // build block-cut tree
    int tot = n; // 1..n = original vertices
    vector<vector<int>> tree(n+tj.comps.size()+5);
    for(int i=0;i<(int)tj.comps.size();i++){
        int id = ++tot; // new node for BCC
        for(int v: tj.comps[i]){
            tree[v].push_back(id);
            tree[id].push_back(v);
        }
    }

    LCA lca(tot);
    for(int i=1;i<=tot;i++) for(int j:tree[i]) if(i<j) lca.addEdge(i,j);
    lca.build(1);

    while(q--){
        int u,v,w; cin>>u>>v>>w;
        int l = lca.get(u,v);
        // check if w lies on path u-v in block-cut tree
        bool ok = (lca.dist(u,v) == lca.dist(u,w)+lca.dist(w,v));
        cout<<(!ok? "YES\n":"NO\n");
    }
}
