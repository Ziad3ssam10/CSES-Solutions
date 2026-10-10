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

struct Line {
    ll k, m;
    mutable ll p;

    bool operator<(const Line &o) const {
        return k < o.k;
    }

    bool operator<(const ll &x) const {
        return p < x;
    }
};

struct LineContainer : multiset<Line, less<> > {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const ll inf = numeric_limits<ll>::max();
    ll div(ll a, ll b) {
        // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = inf;
            return false;
        }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    void add(ll k, ll m) {
        k *= -1;
        m *= -1;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }

    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return -(l.k * x + l.m);
    }
};

const int N = 3000 + 20;
int dp[N][N];
int a[N];
int n, k;
int pre[N], sum[N];

int query(int j, int i) {
    if (j >= i) return 0;
    int mid = (j + i) >> 1;

    int left_cost = (sum[mid] - sum[j]) - j * (pre[mid] - pre[j]);
    int right_cost = i * (pre[i - 1] - pre[mid]) - (sum[i - 1] - sum[mid]);

    return left_cost + right_cost;
}

const int INF = 1e18;

void rec(int i, int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    int best = optl;
    int mini = INF;
    for (int j = optl; j <= min(mid - 1, optr); j++) {
        if (dp[i - 1][j] == INF)continue;
        int cost = query(j, mid);
        int val = dp[i - 1][j] + cost;
        if (val < mini) {
            mini = val;
            best = j;
        }
    }
    dp[i][mid] = mini;
    rec(i, l, mid - 1, optl, best);
    rec(i, mid + 1, r, best, optr);
}

void solve(int tc) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
        sum[i] = sum[i - 1] + i * a[i];
    }
    for (int j = 1; j <= n; j++) dp[1][j] = j * pre[j - 1] - sum[j - 1];
    for (int i = 2; i <= k; i++) rec(i, 1, n, 1, n - 1);
    int ans = INF;
    for (int i = k; i <= n; i++) {
        int suffix_cost = (sum[n] - sum[i]) - i * (pre[n] - pre[i]);
        ans = min(ans, dp[k][i] + suffix_cost);
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
