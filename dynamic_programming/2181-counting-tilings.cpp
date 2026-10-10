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

const int MOD = 1e9 + 7;

void solve(int tc) {
    int n, m;
    cin >> m >> n;
    int M = 1 << (m + 1);
    vector dp(n + 1, vector(m + 1, vector<int>(M << 1, 0LL)));
    dp[0][m][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int msk = 0; msk < M; msk++) dp[i][0][msk << 1] = dp[i - 1][m][msk];
        for (int j = 1; j <= m; j++) {
            for (int msk = 0; msk < M; msk++) {
                int rgt = (msk >> (j - 1)) & 1, dwn = (msk >> j) & 1;
                if (!rgt && !dwn) {
                    // case 1: try full (j & j + 1) or just full (j)
                    dp[i][j][msk ^ (1 << j)] = (dp[i][j][msk ^ (1 << j)] + dp[i][j - 1][msk]) % MOD;
                    //place right domino
                    dp[i][j][msk ^ (1 << (j - 1))] = (dp[i][j][msk ^ (1 << (j - 1))] + dp[i][j - 1][msk]) % MOD;
                    //place down domino
                } else if (rgt && !dwn) {
                    dp[i][j][msk ^ (1 << (j - 1))] = (dp[i][j][msk ^ (1 << (j - 1))] + dp[i][j - 1][msk]) % MOD;
                    //place down domino
                } else if (!rgt && dwn) {
                    dp[i][j][msk ^ (1 << j)] = (dp[i][j][msk ^ (1 << j)] + dp[i][j - 1][msk]) % MOD;
                    //place right domino
                }
            }
        }
    }
    cout << dp[n][m][0] << '\n';
}


signed main() {
    wady
    files();
    int t = 1;
    //cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
