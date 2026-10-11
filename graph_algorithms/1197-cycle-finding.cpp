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
struct Edge {
    int a, b, cost;
};

int n, m;
vector<Edge> edges;
const long long INF = 1e18; 

int ptr = -1;
vector<int> par;

void bellman() {
    vector<long long> d(n + 1, 0);
    par.assign(n + 1, -1);
    ptr = -1;

    for (int i = 0; i < n; ++i) {
        ptr = -1;
        for (Edge e : edges) {
            if (d[e.a] + e.cost < d[e.b]) {
                d[e.b] = d[e.a] + e.cost;
                par[e.b] = e.a;
                ptr = e.b;
            }
        }
    }
}

void solve(int tc) {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(Edge{a, b, c});
    }
    bellman();
    if (ptr == -1) {
        cout << "NO\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        ptr = par[ptr];
    }
    vector<int> cycle;
    for (int v = ptr;; v = par[v]) {
        cycle.emplace_back(v);
        if (v == ptr && cycle.size() > 1) break;
    }
    cout << "YES\n";
    reverse(cycle.begin(), cycle.end());
    for (auto &i : cycle) {
        cout << i << " ";
    }
    cout << endl;
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
