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

int mul(int a, int b) {
    return (1ll * a * b) % mod;
}

int fp(int b, int p) {
    if (!p)return 1;
    int ret = fp(b, p / 2);
    ret = mul(ret, ret);
    if (p & 1)ret = mul(ret, b);
    return ret;
}

int rec(int n) {
    if (n == 0)return 0;
    return n / 5 + rec(n / 5);
}

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    multiset<int> ms(a.begin(), a.end());
    while (m--) {
        int x;
        cin >> x;
        auto it = ms.upper_bound(x);
        if (it != ms.begin())it--;
        else {
            cout << "-1\n";
            continue;
        }
        cout << *it << endl;
        ms.extract(it);
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
