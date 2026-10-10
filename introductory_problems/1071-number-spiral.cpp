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
    int y, x;
    cin >> y >> x;
    y > x
        ? y % 2 == 1
              ? cout << (y - 1) * (y - 1) + x
              : cout << y * y - x + 1
        : x % 2 == 1
              ? cout << x * x - y + 1
              : cout << (x - 1) * (x - 1) + y;
    cout << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
