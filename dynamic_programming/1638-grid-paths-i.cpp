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


void solve(int tc) {
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto &i: a)cin >> i;
    vector<vector<int> > dp(n + 2, vector<int>(n + 2, 0));
    dp[0][0] = (a[0][0] == '.');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '*')continue;
            if (i - 1 >= 0)dp[i][j] = add(dp[i][j], dp[i - 1][j]);
            if (j - 1 >= 0)dp[i][j] = add(dp[i][j], dp[i][j - 1]);
        }
    }
    cout << dp[n - 1][n - 1] << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
