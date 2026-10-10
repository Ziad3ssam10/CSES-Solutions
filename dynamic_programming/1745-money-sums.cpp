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


void solve(int tc) {
    int n;
    cin >> n;
    const int N = 1e6 + 2;
    bitset<N> dp;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        dp |= dp << x;
    }
    vector<int> ans;
    for (int i = 1; i < N; i++) {
        if (dp[i])ans.emplace_back(i);
    }
    cout << ans.size() << endl;
    for (auto &i: ans)cout << i << " ";
    cout << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
