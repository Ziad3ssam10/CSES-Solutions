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
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    int tot = (n * (n + 1)) / 2;
    if (tot & 1)cout << 0;
    else {
        tot /= 2;
        vector<int> dp(tot + 5);
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            vector<int> ndp(tot + 5);
            for (int j = 0; j <= tot; j++) {
                ndp[j] = add(ndp[j], dp[j]);
                if (j - i >= 0)ndp[j] = add(ndp[j], dp[j - i]);
            }
            dp.swap(ndp);
        }
        cout << dp[tot] << endl;
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
