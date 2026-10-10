#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
#define double long double
#define int long long
#define ll int
#define MX LLONG_MAX
#define MN LLONG_MIN
#define endl '\n'
#define ordered_set tree<ll, null_type, greater<ll>, rb_tree_tag, tree_order_statistics_node_update>

#define wady ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);

const int N = 1e7 + 10;

string a, b;
int dp[20][11][2][2];

int rec(int idx, int last, bool eqa, bool eqb) {
    if (idx == b.size()) return 1;
    int &ret = dp[idx][last][eqa][eqb];
    if (~ret) return ret;
    ret = 0;
    int up = (eqb ? b[idx] - '0' : 9);
    int down = (eqa ? a[idx] - '0' : 0);
    for (int d = down; d <= up; d++) {
        if(last == 10 and d == 0)
            ret += rec(idx + 1, last, eqa and (d == down), eqb and (d == up));
        else if (d != last)
            ret += rec(idx + 1, d, eqa and (d == down), eqb and (d == up));
    }
    return ret;
}

void solve() {
    cin >> a >> b;
    while (a.size() < b.size()) a = '0' + a;
    memset(dp, -1, sizeof dp);
    cout << rec(0, 10, 1, 1) << endl;
}

signed main() {
    wady
    // alotofcalx();
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int tt = 1;
    //cin >> tt;
    while (tt--) solve();
}
