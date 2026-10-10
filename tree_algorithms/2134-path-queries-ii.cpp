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

const int N = 2e5 + 20;
int par[N], depth[N], heavy[N], head[N], pos[N];
int cur_pos = 0;
vector<int> adj[N];
int n;

struct segmenttree {
    int n;
    vector<long long> tree;

    void init(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        tree.assign(2 * n, -1e18);
    }

    void update(int idx, long long val) {
        idx += n;
        tree[idx] = val;
        idx >>= 1;
        while (idx) {
            tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    int query(int l, int r) {
        l += n;
        r += n;
        long long res = -1e9;

        while (l <= r) {
            if (l & 1) res = max(res, tree[l++]);
            if (!(r & 1)) res = max(res, tree[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
}seg;


int dfs(int node) {
    int sz = 1;
    int max_chsz = 0;
    for (auto &child: adj[node]) {
        if (child == par[node])continue;
        par[child] = node;
        depth[child] = depth[node] + 1;
        int chsz = dfs(child);
        sz += chsz;
        if (chsz > max_chsz) {
            max_chsz = chsz;
            heavy[node] = child;
        }
    }
    return sz;
}

void decompse(int node,int h) {
    head[node] = h;
    pos[node] = cur_pos++;
    if (heavy[node] != -1) {
        decompse(heavy[node], h);
    }
    for (auto child: adj[node]) {
        if (child == par[node] or child == heavy[node])continue;
        decompse(child, child);
    }
}


void init() {
    fill(par, par + n + 5, 0);
    fill(depth, depth + n + 5, 0);
    fill(heavy, heavy + n + 5, -1);
    fill(head, head + n + 5, 0);
    fill(pos, pos + n + 5, 0);
    cur_pos = 0;
    dfs(0);
    decompse(0, 0);
}

int query(int a,int b) {
    int ret = 0;
    for (; head[a] != head[b]; b = par[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) {
            swap(a, b);
        }
        ret = max(ret, seg.query(pos[head[b]], pos[b]));
    }
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    ret = max(ret, seg.query(pos[a], pos[b]));
    return ret;
}

void solve(int tc) {
    cin >> n;
    int q;
    cin >> q;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    int m = n - 1;
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    init();
    seg.init(n);
    for (int i = 0; i < n; i++)seg.update(pos[i], a[i]);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            seg.update(pos[s], x);
        } else {
            int a, b;
            cin >> a >> b;
            a--,b--;
            cout << query(a, b) << " ";
        }
    }
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
