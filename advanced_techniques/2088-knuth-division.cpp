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

const int N = 5000 + 20;
int a[N];
int dp[N][N], opt[N][N];
int n;

void solve(int tc) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    auto cost = [&](int i, int j) {
        return a[j] - a[i - 1];
    };
    for (int i = 0; i <= n; i++) {
        opt[i][i] = i;
    }
    for (int i = n - 1; i > 0; i--) {
        for (int j = i + 1; j <= n; j++) {
            int mini = 1e18;
            int C = cost(i, j);
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                if (mini >= dp[i][k] + dp[k + 1][j] + C) {
                    opt[i][j] = k;
                    mini = dp[i][k] + dp[k + 1][j] + C;
                }
            }
            dp[i][j] = mini;
        }
    }
    cout << dp[1][n] << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
