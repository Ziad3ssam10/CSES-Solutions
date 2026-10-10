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
    FenwickTree cnt_tr(comp.size() + 5);
    FenwickTree sum_tr(comp.size() + 5);

    auto add = [&](int x) {
        int id = comp.get_id(x);
        cnt_tr.add(id, 1);
        sum_tr.add(id, x);
    };

    auto rem = [&](int x) {
        int id = comp.get_id(x);
        cnt_tr.add(id, -1);
        sum_tr.add(id, -x);
    };

    for (int i = 0; i < k; i++) {
        add(a[i]);
    }
    int median_rank = (k + 1) / 2;
    for (int i = 0; i <= n - k; i++) {
        int median_id = cnt_tr.bit_search(median_rank);
        int median_val = comp.get_val(median_id);
        int left_cnt = cnt_tr.sum(median_id);
        int left_sum = sum_tr.sum(median_id);
        int right_cnt = k - left_cnt;
        int right_sum = sum_tr.sum(1, comp.size()) - left_sum;
        int cost = (left_cnt * median_val - left_sum) + (right_sum - right_cnt * median_val);
        cout << cost << (i == n - k ? "" : " ");
        if (i + k < n) {
            rem(a[i]);
            add(a[i + k]);
        }
    }
    cout << endl;
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
