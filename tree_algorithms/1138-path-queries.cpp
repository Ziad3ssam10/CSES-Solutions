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

struct Node {
    int sum = 0;
};
int sz = 0;

struct seg {
    vector<Node> tree;
    Node neutral = {0};

    seg(int n) {
        sz = 1;
        while (sz < n)sz *= 2;
        tree.assign(sz * 2, neutral);
    }

    Node merge(Node l, Node r) {
        Node ret;
        ret.sum = l.sum + r.sum;
        return ret;
    }

    void build(vector<ll> &v, int node = 0, int lx = 0, int rx = sz - 1) {
        if (lx == rx) {
            if (lx < v.size()) {
                tree[node] = {v[lx]};
            }
            return;
        }
        int mid = (lx + rx) / 2;
        build(v, node * 2 + 1, lx, mid);
        build(v, node * 2 + 2, mid + 1, rx);
        tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
    }

    Node query(int l, int r, int node = 0, int lx = 0, int rx = sz - 1) {
        if (lx >= l and rx <= r) {
            return tree[node];
        }
        if (lx > r or rx < l) {
            return neutral;
        }
        int mid = (lx + rx) / 2;
        Node q1 = query(l, r, node * 2 + 1, lx, mid);
        Node q2 = query(l, r, node * 2 + 2, mid + 1, rx);
        return merge(q1, q2);
    }

    void update(int idx, int val, int node = 0, int lx = 0, int rx = sz - 1) {
        if (lx == rx) {
            tree[node] = {val};
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx <= mid)
            update(idx, val, node * 2 + 1, lx, mid);
        else
            update(idx, val, node * 2 + 2, mid + 1, rx);
        tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
    }
};


int timer = 1;
const int N = 2e5 + 10;
int in[N], out[N];
vector<int> adj[N + 1];
bool vis[N];
vector<ll> flat(2 * N);
vector<int> a(N);

void dfs(int node, int parent) {
    in[node] = timer;
    flat[timer++] = a[node];
    vis[node] = 1;
    //   cout << node << " " << timer <<endl;
    for (auto &child: adj[node]) {
        if (child == parent)continue;
        if (vis[child])continue;
        dfs(child, node);
    }
    out[node] = timer;
    flat[timer++] = -a[node];
}


void solve(int tc) {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)cin >> a[i];

    int m = n - 1;

    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0, -1);
    /*   for (int i = 0; i < n; i++) {
           cout << in[i] << " " << out[i] << endl;
           for(auto &j : adj[i])cout << j << endl;
       }*/
    seg tree(2 * n + 2);
    tree.build(flat);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            tree.update(in[s], x);
            tree.update(out[s], -x);
        } else {
            int x;
            cin >> x;
            x--;
            cout << tree.query(in[0], in[x]).sum << endl;
        }
    }
}

signed main() {
    wady
    files();
    int tc = 1;
    int tt = 1;
//    cin >> tt;
    while (tt--) {
        solve(tc++);
    }
}
