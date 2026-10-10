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

// 1-based
// Tested
struct Eulerian {
    int n;
    bool directed;
    int edge_cnt = 0;
    vector<vector<pair<int, int> > > g; // (to, edgeID)
    vector<int> in, out; // degree counters
    vector<int> used; // mark edges used in DFS
    vector<int> ptr; // iterator per node
    vector<int> path; // final result

    Eulerian(int _n, bool _directed = false) {
        n = _n;
        directed = _directed;
        g.assign(n + 1, {});
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
    }

    void addEdge(int u, int v) {
        ++edge_cnt;
        g[u].push_back({v, edge_cnt});
        out[u]++, in[v]++;
        if (!directed) {
            g[v].push_back({u, edge_cnt});
            out[v]++, in[u]++;
        }
    }

    void dfs(int u) {
        while (ptr[u] < (int) g[u].size()) {
            auto [v, id] = g[u][ptr[u]++];
            if (used[id]) continue;
            used[id] = 1;
            dfs(v);
        }
        path.push_back(u);
    }

    bool solve() {
        path.clear();
        ptr.assign(n + 1, 0);
        used.assign(edge_cnt + 1, 0);

        int start = 0, end = 0, root = 0;

        if (!directed) {
            // undirected: at most 2 odd-degree vertices
            for (int i = 1; i <= n; i++) {
                if (out[i] & 1) {
                    if (!start) start = i;
                    else if (!end) end = i;
                    else return false;
                }
            }
            if (!start) {
                // all even
                for (int i = 1; i <= n; i++)
                    if (out[i]) {
                        start = i;
                        break;
                    }
            }
            if (!start) return true; // empty graph
            root = start;
        } else {
            // directed: in/out degree constraints
            int cnt_start = 0, cnt_end = 0;
            for (int i = 1; i <= n; i++) {
                if (out[i] - in[i] == 1) {
                    cnt_start++;
                    start = i;
                } else if (in[i] - out[i] == 1) cnt_end++;
                else if (abs(in[i] - out[i]) > 1) return false;
            }
            if ((cnt_start != 1 || cnt_end != 1) && cnt_start != 0) return false;
            if (!start) {
                for (int i = 1; i <= n; i++)
                    if (out[i]) {
                        start = i;
                        break;
                    }
            }
            if (!start) return true; // empty graph
            root = start;
        }

        dfs(root);

        // connectivity check
        if ((int) path.size() != edge_cnt + 1) return false;

        reverse(path.begin(), path.end());
        return true;
    }

    bool isCircuit() {
        if (!solve()) return false; // if no Eulerian path, can't be circuit
        if (!directed) {
            for (int i = 1; i <= n; i++)
                if (out[i] & 1) return false;
            return true;
        }
        for (int i = 1; i <= n; i++)
            if (in[i] != out[i]) return false;
        return true;
    }

    vector<int> getPath() { return path; }
};

int n, m;
vector<vector<int> > adj;
vector<int> parent;
vector<bool> visited;
int cycle_start = -1, cycle_end = -1;

bool dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;

    for (int v: adj[u]) {
        if (v == p) continue;
        if (visited[v]) {
            cycle_start = v;
            cycle_end = u;
            return true;
        }
        if (!visited[v]) {
            if (dfs(v, u)) return true;
        }
    }
    return false;
}

void solve(int tc) {
    cin >> n >> m;
    adj.assign(n + 1, vector<int>());
    parent.assign(n + 1, 0);
    visited.assign(n + 1, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (dfs(i, 0)) {
                vector<int> path;
                for (int v = cycle_end; v != cycle_start; v = parent[v]) {
                    path.push_back(v);
                }
                path.push_back(cycle_start);
                reverse(path.begin(), path.end());
                path.push_back(cycle_start);

                cout << path.size() << "\n";
                for (int x: path) {
                    cout << x << " ";
                }
                cout << "\n";
                return;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
