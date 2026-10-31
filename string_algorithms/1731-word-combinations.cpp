#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define endl '\n'
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define wady ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}


void solve(int tc) {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> lps(m, 0);
    int len = 0;
    for (int i = 1; i < m; i++) {
        while (len > 0 and t[i] != t[len])len = lps[len - 1];
        if (t[i] == t[len])len++;
        lps[i] = len;
    }
    int j = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 and s[i] != t[j])j = lps[j - 1];
        if (s[i] == t[j])j++;
        if (j == m)ans++, j = lps[j - 1];
    }

    cout << ans << endl;
}

signed main() {
    wady
 //   files();
    int tc = 1;
    int tt = 1;
    //  cin >> tt;
    while (tt--) {
        solve(tc++);
    }
}
