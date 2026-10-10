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
    int n, x;
    cin >> n >> x;
    int half = n / 2;
    int other = n - half;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    vector<int> sums;
    sums.reserve(1ll << half);
    for (int msk = 0; msk < (1ll << half); msk++) {
        int temp = 0;
        for (int i = 0; i < half; i++) {
            if (msk & (1ll << i)) {
                temp += a[i];
            }
        }
        if (temp > x)continue;
        sums.emplace_back(temp);
    }
    sort(sums.begin(), sums.end());
    int ans = 0;
    for (int msk = 0; msk < (1ll << other); msk++) {
        int temp = 0;
        for (int i = 0; i < other; i++) {
            if (msk & (1ll << i)) {
                temp += a[half + i];
            }
        }
        if (temp <= x) {
            auto low = lower_bound(sums.begin(), sums.end(), x - temp);
            auto high = upper_bound(sums.begin(), sums.end(), x - temp);
            ans += (high - low);
        }
    }
    cout << ans << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
