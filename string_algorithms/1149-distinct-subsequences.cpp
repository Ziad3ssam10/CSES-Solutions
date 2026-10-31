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

int add(int a, int b) {
    return (1ll * a + b) % mod;
}

const int N = 5e5 + 20;
int n;
string s;
vector<vector<int> > id(26);
int dp[N];

int rec(int idx) {
    if (idx >= n) return 1;
    int &ret = dp[idx];
    if (~ret) return ret;
    ret = rec(idx + 1);
    for (int i = 0; i < 26; i++) {
        auto nxt = upper_bound(id[i].begin(), id[i].end(), idx);
        if (nxt != id[i].end() and *nxt < n) {
            ret = add(ret, rec(*nxt));
        }
    }
    return ret;
}

#define int ll

void solve(int tc) {
    cin >> s;
    n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    vector<int> last_occ(26, -1);
    for (int i = 1; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) % mod;
        int c = s[i - 1] - 'a';
        if (last_occ[c] != -1) dp[i] = (dp[i] - dp[last_occ[c] - 1] + mod) % mod;
        last_occ[c] = i;
    }
    int ans = (dp[n] - 1 + mod) % mod;
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
