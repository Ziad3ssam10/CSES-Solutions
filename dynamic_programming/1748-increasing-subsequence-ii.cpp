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

struct SegmentTree {
    int n;

    struct Node {
        int val = 0;
    };

    Node skip;
    vector<Node> tree;

    SegmentTree(int n) {
        this->n = n;
        tree.resize(n << 2);
    }

    Node single(int x) {
        Node r;
        r.val = x;
        return r;
    }

    Node merge(Node a, Node b) {
        Node ret;
        ret.val = (a.val + b.val) % mod;
        return ret;
    }

    void update(int u, int st, int en, int idx, int val) {
        if (idx > en || idx < st) return;
        if (st == en) {
            tree[u].val = (tree[u].val + val) % mod;
            return;
        }
        int mid = st + en >> 1;
        update(u << 1, st, mid, idx, val);
        update((u << 1) | 1, mid + 1, en, idx, val);
        tree[u] = merge(tree[u << 1], tree[(u << 1) | 1]);
    }

    Node query(int u, int st, int en, int l, int r) {
        if (st >= l && en <= r) return tree[u];
        if (st > r || en < l) return skip;
        int mid = st + en >> 1;
        return merge(query(u << 1, st, mid, l, r), query((u << 1) | 1, mid + 1, en, l, r));
    }

    void update(int idx, int val) {
        --idx;
        update(1, 0, n - 1, idx, val);
    }

    Node query(int l, int r) {
        --l, --r;
        return query(1, 0, n - 1, l, r);
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
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    }

    int get_val(int idx) const {
        return vals[idx];
    }

    int size() const {
        return vals.size();
    }
};

void solve(int tc) {
    int n;
    cin >> n;
    vector<int> a(n);
    Compressor comp;
    for (auto &i: a) cin >> i, comp.add(i);
    comp.build();
    SegmentTree tr(comp.size() + 2);
    for (int i = 0; i < n; i++) {
        int id = comp.get_id(a[i]);
        int temp = (id == 0) ? 0 : tr.query(1, id).val;
        int total_ways = (temp + 1) % mod;
        tr.update(id + 1, total_ways);
    }
    cout << tr.query(1, comp.size()).val << endl;
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
