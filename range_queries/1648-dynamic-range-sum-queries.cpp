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

#define int ll

struct SegmentTree {
    int n;

    struct Node {
        int val = 0;
    };

    Node skip;
    vector<Node> tree;

    SegmentTree(int n, vector<int> &v) {
        this->n = n;
        tree.resize(n << 2);
        build(1, 0, n - 1, v);
    }

    Node single(int x) {
        Node r;
        r.val = x;
        return r;
    }

    Node merge(Node a, Node b) {
        Node ret;
        ret.val = a.val + b.val;
        return ret;
    }

    void build(int u, int st, int en, vector<int> &a) {
        if (st == en) return void(tree[u] = single(a[st]));
        int mid = st + en >> 1;
        build(u << 1, st, mid, a);
        build((u << 1) | 1, mid + 1, en, a);
        tree[u] = merge(tree[u << 1], tree[(u << 1) | 1]);
    }

    void update(int u, int st, int en, int idx, int val) {
        if (idx > en || idx < st) return;
        if (st == en) return void(tree[u] = single(val));
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

void solve(int tc) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    SegmentTree tr(n, a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, u;
            cin >> k >> u;
            tr.update(k, u);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r).val << endl;
        }
    }
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
