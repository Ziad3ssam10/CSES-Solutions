#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using orderedset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
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

struct FenwickTree {
    vector<int> bit;
    int n;
    int LOGN;
    // 1 based
    FenwickTree(int sz) {
        n = sz + 1;
        LOGN = 0;
        while ((1 << LOGN) <= n) LOGN++;
        bit.assign(n, 0);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }

    int sum(int idx) {
        int ret = 0;
        for (; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    int sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }

    // Find the k-th order statistic (requires a 1-based tree)
    // Returns the 1-based index of the largest value less than or equal to v
    int bit_search(int v) {
        int sum = 0;
        int pos = 0;
        for (int i = LOGN; i >= 0; i--) {
            if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < v) {
                sum += bit[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
    }
};


struct Compressor {
    vector<int> vals;

    void add(int x) {
        vals.push_back(x);
    }

    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    int get_id(int x) const {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    }

    int get_val(int idx) const {
        return vals[idx - 1];
    }

    int size() const {
        return vals.size();
    }
};

void solve(int tc) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    Compressor comp;
    for (auto &i: a)comp.add(i);
    comp.build();
    FenwickTree tr(comp.size() + 5);
    int cur = 0;
    for (int i = 0; i < k; i++) {
        int cnt = tr.sum(comp.get_id(a[i]));
        cur += i - cnt;
        tr.add(comp.get_id(a[i]), 1);
    }
    cout << cur << " ";
    int l = 0, r = k - 1;
    while (r + 1 < n) {
        tr.add(comp.get_id(a[l]), -1);
        cur -= tr.sum(comp.get_id(a[l++]) - 1);
        int cnt = k - 1;
        cur += cnt - tr.sum(comp.get_id(a[++r]));
        tr.add(comp.get_id(a[r]), 1);
        cout << cur << " ";
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    //cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
