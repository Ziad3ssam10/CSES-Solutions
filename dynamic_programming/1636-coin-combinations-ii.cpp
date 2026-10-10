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
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &i: c) cin >> i;
    vector<int> dp(x + 2, 0);
    dp[0] = 1;
    for (int j: c) {
        for (int i = j; i <= x; i++) {
            dp[i] = add(dp[i], dp[i - j]);
        }
    }
    cout << dp[x] << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
