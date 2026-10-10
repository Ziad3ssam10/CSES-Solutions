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


#define  int ll

void solve(int tc) {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    vector<pair<int, ll> > dp(1 << n);
    dp[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); ++mask) {
        pair<int, ll> best = {n + 1, 0};
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                auto prev = dp[mask ^ (1 << i)];
                if (prev.second + a[i] <= x) {
                    prev.second += a[i];
                } else {
                    prev.first++;
                    prev.second = a[i];
                }
                best = min(best, prev);
            }
        }
        dp[mask] = best;
    }
    cout << dp[(1 << n) - 1].first << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
