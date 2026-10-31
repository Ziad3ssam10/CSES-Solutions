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
    ll k;
    cin >> k;
    deque<int> ans;
    for (int i = 1; i <= n; i++)ans.emplace_back(i);
    ll m = 0;
    while (((m + 1) * m) / 2 < k)m++;
    reverse(ans.begin(), ans.begin() + m);
    ll rem = k - (m * (m - 1) / 2);
    if (rem > 0) {
        int idx = 0;
        for (int i = 0; i < n; i++) {
            if (ans[i] == m + 1) {
                idx = i;
                break;
            }
        }
        int val = ans[idx];
        ans.erase(ans.begin() + idx);
        ans.insert(ans.begin() + (m - rem), val);
    }
    for (auto &i: ans)cout << i << " ";
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
