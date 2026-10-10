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

const int N = 1e6 + 20;
int dp[N];

int rec(int n) {
    if (n == 0)return 0;
    int &ret = dp[n];
    if (~ret)return ret;
    ret = 1e9;
    int temp = n;
    while (temp > 0) {
        int d = temp % 10;
        temp /= 10;
        ret = min(ret, rec(n - d) + 1);
    }
    return ret;
}

void solve(int tc) {
    int n;
    cin >> n;
    memset(dp, -1, sizeof dp);
    cout << rec(n) << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
