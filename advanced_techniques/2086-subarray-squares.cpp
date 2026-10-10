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

const int N = 3000  + 20, K = 3000 + 20;
int dp[K][N];
int a[N];
int ans = 0;
int frq[N];

int pre[N];

int n, k;

int query(int l, int r) {
    int temp = pre[r] - pre[l - 1];
    return temp * temp;
}

void rec(int i, int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    int best = optl;
    int mini = 1e18;
    for (int j = optl; j <= min(mid - 1, optr); j++) {
        int cost = query(j + 1, mid);
        int val = dp[i - 1][j] + cost;
        if (val < mini) {
            mini = val;
            best = j;
        }
    }
    dp[i][mid] = mini;
    rec(i, l, mid - 1, optl, best);
    rec(i, mid + 1, r, best, optr);
}

void solve(int tc) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];
    for (int j = 0; j <= n; j++) dp[0][j] = 1e18;
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++) rec(i, 1, n, 0, n - 1);
    cout << dp[k][n] << endl;
}


signed main() {
    wady
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
