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


void solve(int tc) {
    int n, q;
    cin >> n >> q;
    const int LG = 30;
    vector<vector<int> > parent(n + 5, vector<int>(32));
    for (int i = 1; i <= n; i++) {
        cin >> parent[i][0];
    }
    for (int i = 1; i <= LG; i++) {
        for (int u = 1; u <= n; u++) {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }
    }
    while (q--) {
        int u, x;
        cin >> u >> x;
        for (int i = 0; i <= LG; i++) {
            if (x & (1ll << i)) {
                u = parent[u][i];
            }
        }
        cout << u << endl;
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
   // cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
