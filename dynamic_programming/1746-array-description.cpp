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

const int mod = 1e9 + 7;

int add(ll a, int b) {
    return (a + b) % mod;
}

int mul(int a,ll b) {
    return (a * b) % mod;
}

int fp(int b, int p) {
    if (!p)return 1;
    int ret = fp(b, p / 2);
    ret = mul(ret, ret);
    if (p & 1)ret = mul(ret, b);
    return ret;
}

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    vector<vector<int> > dp(n + 2, vector<int>(m + 2));
    if (a[0] == 0) {
        for (int i = 1; i <= m; i++)dp[0][i] = 1;
    } else dp[0][a[0]] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] != 0 and j != a[i])continue;
            dp[i][j] = dp[i - 1][j];
            if (j - 1 >= 1)dp[i][j] = add(dp[i][j], dp[i - 1][j - 1]);
            if (j + 1 <= m)dp[i][j] = add(dp[i][j], dp[i - 1][j + 1]);
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; j++) {
        ans = add(ans, dp[n - 1][j]);
    }
    cout << ans << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
