#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
#define int long long
#define ll long long
#define ld  long double
#define endl '\n'
#define wady ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define orderedset tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}


void solve(int tc) {
    int n, m, q;
    cin >> n >> m >> q;
    const int INF = 1e15;
    vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        d[u][v] = min(d[u][v], c);
        d[v][u] = min(d[v][u], c);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] < INF and d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = min(d[a][b], d[b][a]);
        if (ans == INF) cout << "-1\n";
        else cout << ans << endl;
    }
}

signed main() {
    wady
    files();
    int tc = 1;
    int tt = 1;
    //  cin >> tt;
    while (tt--)solve(tc);
}
