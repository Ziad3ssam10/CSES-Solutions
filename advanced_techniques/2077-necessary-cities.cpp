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


struct Tarjan {
    int n, compID, timer;
    bool is_directed;
    stack<int> stk;
    set<int> artPoints;
    vector<bool> inStack;
    vector<int> scc, low, tin, id;
    set<pair<int, int> > bridges;
    vector<vector<int> > adj, comps;

    // Constructor: 1-based indexing by default.
    Tarjan(int _n, bool _is_directed = true) {
        n = _n;
        is_directed = _is_directed;
        adj.assign(n + 1, vector<int>());
        comps.assign(n + 1, vector<int>());
        inStack.assign(n + 1, false);
        scc.assign(n + 1, 0);
        low.assign(n + 1, 0);
        tin.assign(n + 1, 0);
        id.assign(n + 1, 0);
        compID = timer = 0;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (!is_directed) adj[v].push_back(u);
    }

    pair<int, int> get_edge(int u, int v) {
        return {min(u, v), max(u, v)};
    }

    void dfs(int node, int par = -1) {
        int children = 0;
        inStack[node] = true;
        tin[node] = low[node] = ++timer;
        stk.push(node);

        for (auto &child: adj[node]) {
            if (!is_directed && child == par) continue;

            if (!tin[child]) {
                children++;
                dfs(child, node);
                low[node] = min(low[node], low[child]);
                if (!is_directed) {
                    if (low[child] > tin[node]) {
                        bridges.insert(get_edge(node, child));
                    }
                    if (low[child] >= tin[node] && par != -1) {
                        artPoints.insert(node);
                    }
                }
            } else if (inStack[child] || !is_directed) {
                low[node] = min(low[node], tin[child]);
            }
        }

        if (!is_directed && par == -1 && children > 1) {
            artPoints.insert(node);
        }

        if (low[node] == tin[node]) {
            compID++;
            while (true) {
                int cur = stk.top();
                stk.pop();
                inStack[cur] = false;
                scc[cur] = compID;
                comps[compID].push_back(cur);
                if (cur == node) break;
            }
        }
    }

    void build() {
        for (int i = 1; i <= n; ++i) {
            if (!tin[i]) dfs(i);
        }
    }

    void _build_bridge_components(int u) {
        id[u] = timer;
        for (auto &v: adj[u]) {
            if (bridges.count(get_edge(u, v)) || id[v]) continue;
            _build_bridge_components(v);
        }
    }

    vector<vector<int> > get_bridge_tree() {
        assert(!is_directed);
        build();
        timer = 0;
        fill(id.begin(), id.end(), 0);

        for (int i = 1; i <= n; ++i) {
            if (!id[i]) {
                ++timer;
                _build_bridge_components(i);
            }
        }

        vector<vector<int> > tree(timer + 1);
        for (auto &e: bridges) {
            int u = id[e.first];
            int v = id[e.second];
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        return tree;
    }

    vector<vector<int> > get_condensed_graph() {
        assert(is_directed);
        build();
        vector<vector<int> > dag(compID + 1);
        set<pair<int, int> > seen_edges;

        for (int i = 1; i <= n; ++i) {
            for (auto &j: adj[i]) {
                if (scc[i] != scc[j]) {
                    if (seen_edges.insert({scc[i], scc[j]}).second) {
                        dag[scc[i]].push_back(scc[j]);
                    }
                }
            }
        }
        return dag;
    }
};

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    Tarjan tr(n + 2, 0);
    while (m--) {
        int u, v;
        cin >> u >> v;
        tr.add_edge(u, v);
    }
    tr.build();
    cout << tr.artPoints.size() << endl;
    for (auto &i: tr.artPoints) {
        cout << i << " ";
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
