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
#define wady                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

void files() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}

void radix(vector<pair<pair<int, int>, int>> &a, int n) {
    {
        vector<int> cnt(n);
        for (auto &[f, s]: a)cnt[f.second]++;
        vector<int> pos(n, 0);
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        vector<pair<pair<int, int>, int>> new_a(n);
        for (auto &[f, s]: a) {
            new_a[pos[f.second]] = {f, s};
            pos[f.second]++;
        }
        a = new_a;
    }
    {
        vector<int> cnt(n);
        for (auto &[f, s]: a)cnt[f.first]++;
        vector<int> pos(n, 0);
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        vector<pair<pair<int, int>, int>> new_a(n);
        for (auto &[f, s]: a) {
            new_a[pos[f.first]] = {f, s};
            pos[f.first]++;
        }
        a = new_a;
    }
}

void count(vector<int> &p, vector<int> &c, int n) {
    vector<int> cnt(n, 0);
    for (int x: c) cnt[x]++;
    vector<int> pos(n, 0);
    for (int i = 1; i < n; ++i) pos[i] = pos[i - 1] + cnt[i - 1];
    vector<int> new_p(n);
    for (int x: p) {
        int cls = c[x];
        new_p[pos[cls]] = x;
        pos[cls]++;
    }
    p = new_p;
}

void solve(int tc) {
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
    vector<pair<char, int>> init(n);
    for (int i = 0; i < n; i++) init[i] = {s[i], i};
    sort(init.begin(), init.end());

    vector<int> p(n), c(n);
    for (int i = 0; i < n; i++) p[i] = init[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (init[i].first == init[i - 1].first) c[p[i]] = c[p[i - 1]];
        else c[p[i]] = c[p[i - 1]] + 1;
    }

    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) {
            p[i] = (p[i] - (1 << k) + n) % n;
        }
        count(p, c, n);

        vector<int> new_c(n, 0);
        new_c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (now == prev) new_c[p[i]] = new_c[p[i - 1]];
            else new_c[p[i]] = new_c[p[i - 1]] + 1;
        }
        c = new_c;
        k++;
    }

    //for (auto &i: p) cout << i << " ";
    k = 0;
    vector<int> lcp(n);
    for (int i = 0; i < n - 1; i++) {
        int pi = c[i];
        int j = p[pi - 1];
        while (s[i + k] == s[j + k])k++;
        lcp[pi] = k;
        k = max(k - 1, 0ll);
    }
    // cout << endl;
    // for (int i = 1; i < n; i++)cout << lcp[i] << " ";
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans += (n - p[i] - 1) - lcp[i];
    }
    cout << ans << endl;
}

signed main() {
    wady
    files();
    int t = 1;
    //  cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}