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
const int N = 5000 + 20;
int dp[N][N];
int n, a[N];

int pre[N];

int sum(int l, int r) {
    if (r < l)return 0;
    return pre[r] - ((l - 1 >= 0) ? pre[l - 1] : 0);
}

int rec(int i, int j) {
    if (j == i)return a[i];
    int &ret = dp[i][j];
    if (~ret)return ret;
    ret = a[i] - rec(i + 1, j) + sum(i + 1, j);
    ret = max(ret, a[j] - rec(i, j - 1) + sum(i, j - 1));
    return ret;
}

void solve(int tc) {
    cin >> n;
    for (int i = 0; i < n; i++)cin >> a[i];
    pre[0] = a[0];
    for (int i = 1; i < n; i++)pre[i] += pre[i - 1] + a[i];
    for (int i = 0; i < n; i++) {
        dp[i][i] = a[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            int option1 = a[i] - dp[i + 1][j] + sum(i + 1, j);
            int option2 = a[j] - dp[i][j - 1] + sum(i, j - 1);
            dp[i][j] = max(option1, option2);
        }
    }

    cout << dp[0][n - 1] << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
