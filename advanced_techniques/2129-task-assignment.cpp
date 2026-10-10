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

const int N = 205;
const ll INF = (ll) 4e18;


struct Hungarian {
    int n;
    int cost[N][N];
    int u[N], v[N], p[N], way[N];

    Hungarian(int sz) {
        n = sz;
        for (int i = 0; i <= n; i++) u[i] = v[i] = p[i] = way[i] = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cost[i][j] = 0;
    }

    void setCost(int i, int j, int c) {
        cost[i][j] = c;
    }

    int solve() {
        // Returns min cost (we will negate for max)
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv(n + 1, INF);
            vector<bool> used(n + 1, false);

            do {
                used[j0] = true;
                int i0 = p[j0], delta = INF, j1 = -1;

                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }

                for (int j = 0; j <= n; j++) {
                    if (used[j]) u[p[j]] += delta, v[j] -= delta;
                    else minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        return -v[0];
    }
};

void solve(int tc) {
    int n;
    cin >> n;

    Hungarian mat(n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ll c;
            cin >> c;
            mat.setCost(i - 1, j - 1, c);
        }
    }
    ll res = mat.solve();
    cout << res << endl;
    vector<int> ans(n + 1);
    for (int j = 1; j <= n; j++) if (mat.p[j])ans[mat.p[j]] = j;
    for (int i = 1; i <= n; i++) {
        cout << i << " " << ans[i] << endl;
    }
}

signed main() {
    wady
    files();
    int t = 1;
    //  cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
