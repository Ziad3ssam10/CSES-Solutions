#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int N = 200005;

int n, k1, k2;
vector<int> adj[N];

int sz[N];
bool done[N];

int cnt[N], suf[N];
int md, mmd;

void calc_sz(int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v == p || done[v]) continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int p, int total) {
    for (auto v : adj[u]) {
        if (v == p || done[v]) continue;
        if (sz[v] > total / 2)
            return get_centroid(v, u, total);
    }
    return u;
}

long long dfs_count(int u, int p, int depth) {
    if (depth > k2) return 0;

    md = max(md, depth);
    mmd = max(mmd, depth);

    cnt[depth]++;

    long long res = 0;

    int L = max(0LL, k1 - depth);
    int R = k2 - depth;

    if (R >= 0)
        res += suf[L] - (R + 1 < N ? suf[R + 1] : 0);

    for (auto v : adj[u]) {
        if (v == p || done[v]) continue;
        res += dfs_count(v, u, depth + 1);
    }

    return res;
}

long long solve(int entry) {
    calc_sz(entry, -1);
    int cen = get_centroid(entry, -1, sz[entry]);
    done[cen] = true;

    long long ans = 0;

    md = mmd = 0;

    for (auto v : adj[cen]) {
        if (done[v]) continue;

        ans += dfs_count(v, cen, 1);

        for (int i = md; i >= 0; i--)
            suf[i] = cnt[i] + suf[i + 1];

        md = 0;
    }

    ans += suf[k1] - suf[k2 + 1];

    for (int i = 0; i <= mmd; i++) {
        cnt[i] = 0;
        suf[i] = 0;
    }
    mmd = 0;

    for (auto v : adj[cen]) {
        if (!done[v])
            ans += solve(v);
    }

    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k1 >> k2;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << solve(1) << endl;
}
