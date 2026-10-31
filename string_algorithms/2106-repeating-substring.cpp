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

void countsort(vector<int> &p, vector<int> &c) {
    int n = p.size();
    vector<int> cnt(n, 0);
    for (auto x: c)cnt[x]++;
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto x: p) {
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

vector<int> suffixarray(vector<int> v) {
    vector<int> s = v;
    s.push_back(-2e9);
    int n = s.size();
    vector<int> p(n), c(n);
    {
        vector<pair<int, int> > a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) c[p[i]] = c[p[i - 1]];
            else c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        countsort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> prv = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (prv == cur) c_new[p[i]] = c_new[p[i - 1]];
            else c_new[p[i]] = c_new[p[i - 1]] + 1;
        }
        c = c_new;
        k++;
    }
    return p;
}

vector<int> lcp(vector<int> s, vector<int> &p) {
    int n = p.size();
    vector<int> rank(n);
    for (int i = 0; i < n; i++)rank[p[i]] = i;
    int k = 0;
    vector<int> lcp(n - 1);
    for (int i = 0; i < n - 1; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n - 1 and j + k < n - 1 and s[i + k] == s[j + k])k++;
        lcp[rank[i]] = k;
        if (k)k--;
    }
    return lcp;
}

void solve(int tc) {
    string s;
    cin >> s;
    vector<int> v;
    for (auto &i: s)v.emplace_back(i - 'a');
    auto sa = suffixarray(v);
    auto lc = lcp(v, sa);
    int len = 0, idx = 0;
    for (int i = 1; i < lc.size(); i++) {
        if (lc[i] > len) {
            len = lc[i];
            idx = sa[i];
        }
    }
    if (len) {
        cout << s.substr(idx, len) << endl;
    } else cout << "-1\n";
}

signed main() {
    wady
 //   files();
    int t = 1;
    // cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}