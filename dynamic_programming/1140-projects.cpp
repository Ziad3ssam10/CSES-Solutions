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

void solve(int tc) {
    int n;
    cin >> n;
    vector<int> temp;
    vector<array<int, 3> > v(n);
    vector<int> nxt(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
        nxt[i] = n + 1;
        temp.emplace_back(v[i][0]);
    }
    sort(temp.begin(), temp.end());
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) nxt[i] = upper_bound(temp.begin(), temp.end(), v[i][1]) - temp.begin();
    vector<int> dp(n + 2);
    for (int i = 0; i < n; i++) {
        dp[i + 1] = max(dp[i + 1], dp[i]);
        dp[nxt[i]] = max(v[i][2] + dp[i], dp[nxt[i]]);
    }
    cout << dp[n] << endl;
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
    return 0;
}
