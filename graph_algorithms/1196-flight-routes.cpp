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

#define int ll

void solve(int tc) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int> > > adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    vector<vector<int> > path(n + 1);
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<> > pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [cost , u] = pq.top();
        pq.pop();
        if (path[u].size() >= k) continue;
        path[u].push_back(cost);
        for (auto [ch , c]: adj[u])
            pq.push({cost + c, ch});
    }
    for (int i = 0; i < k; i++) cout << path[n][i] << ' ';
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
