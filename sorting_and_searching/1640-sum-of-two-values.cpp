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
    int n, k;
    cin >> n >> k;
    map<int, vector<int> > mp;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    for (int i = 0; i < n; i++) {
        mp[a[i]].emplace_back(i);
    }
    for (int i = 0; i < n; i++) {
        int rem = k - a[i];
       // if (a[i] == 2)cout << i + 1 << endl;
        if (rem == a[i]) {
            if (mp[a[i]].size() >= 2)return cout << mp[a[i]][0] + 1 << " " << mp[a[i]][1] + 1 << endl, void();
        } else {
            if (mp.count(rem))return cout << i + 1 << " " << mp[rem][0] + 1 << endl, void();
        }
    }
    cout << "IMPOSSIBLE\n";
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
