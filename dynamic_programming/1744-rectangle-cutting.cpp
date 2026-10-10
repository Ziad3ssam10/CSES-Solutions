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

const int N = 1000 + 20;
int dp[N][N], a[N], b[N];
int n, m;

int rec(int i, int j) {
    if (i == n or j == m)return 0;
    int &ret = dp[i][j];
    if (~ret)return ret;
    ret = rec(i + 1, j);
    ret = max(ret, rec(i, j + 1));
    if (a[i] == b[j])ret = max(ret, rec(i + 1, j + 1) + 1);
    return ret;
}

vector<int> ans;

void build(int i, int j) {
    if (i == n or j == m)return;
    int tar = rec(i, j);
    if (tar == rec(i + 1, j))return build(i + 1, j), void();
    if (tar == rec(i, j + 1))return build(i, j + 1), void();
    if (a[i] == b[j] and tar == rec(i + 1, j + 1) + 1) {
        ans.emplace_back(a[i]);
        return build(i + 1, j + 1), void();
    }
}

void solve(int tc) {
    int a, b;
    cin >> a >> b;
    vector<vector<int> > dp(a + 2, vector<int>(b + 2, 1e9));
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }

            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            }
            for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
        }
    }
    cout << dp[a][b] << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
