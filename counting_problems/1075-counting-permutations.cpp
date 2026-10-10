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

const int N = 1e3 + 5, mod = 1e9 + 7;
int dp[N][N][2];
int n;

int add(int a,int b) { return (a + b) % mod; }
int mul(int a,int b) { return (a * b) % mod; }

void solve(int tc) {
    cin >> n;
    dp[1][0][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (j) {
                dp[i][j - 1][0] = add(dp[i][j - 1][0], add(mul(j, dp[i - 1][j][0]), mul(j - 1, dp[i - 1][j][1])));
            }
            dp[i][j][0] = add(dp[i][j][0], add(mul(i - j - 2, dp[i - 1][j][0]), mul(i - j - 1, dp[i - 1][j][1])));
            dp[i][j][1] = add(dp[i][j][1], dp[i - 1][j][1]);
            dp[i][j + 1][1] = add(dp[i - 1][j][0] * 2, dp[i - 1][j][1]);
        }
    }
    cout << dp[n][0][0];
}


signed main() {
    wady
 //   files();
    int t = 1;
    //   cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
