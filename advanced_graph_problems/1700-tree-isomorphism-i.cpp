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

constexpr int mod = 1e9 + 7;
int add(long long a, long long b) {
    return (a % mod + b % mod + 2 * mod) % mod;
}

int mul(long long a, long long b) {
    return ((a % mod) * (b % mod)) % mod;
}

int fp(long long a, long long p) {
    int ret = 1;
    while (p) {
        if (p & 1) ret = mul(ret, a);
        a = mul(a, a), p >>= 1;
    }
    return ret;
}

constexpr int P = 998244353, Q = 1e9 + 1, R = 99999989; // any primes
// f(x) = hash * Q + R
struct TreeIsomorphism {
    int n;
    vector<vector<int> > adj;

    TreeIsomorphism(int n, vector<vector<int> > &adj) : n(n), adj(adj) {
    }

    // each tree has at most 2 centers
    vector<int> get_centers() {
        return {1};
        vector<int> deg(n + 5, 0);
        for (int i = 1; i <= n; ++i) deg[i] = adj[i].size();

        queue<int> leafs;
        for (int i = 1; i <= n; ++i) if (deg[i] <= 1) leafs.push(i);
        int rem = n;
        while (rem > 2) {
            int sz = leafs.size();
            rem -= sz;
            for (int i = 0; i < sz; ++i) {
                int u = leafs.front();
                leafs.pop();
                for (auto &v: adj[u])
                    if (--deg[v] == 1) leafs.push(v);
            }
        }
        vector<int> cent;
        while (!leafs.empty()) {
            cent.push_back(leafs.front());
            leafs.pop();
        }
        return cent;
    }

    int get_hash(int u, int p) {
        int ans = 0;
        for (auto &v: adj[u])
            if (v != p)
                ans = add(ans, fp(P, get_hash(v, u)));
        // P^tree_hash1 + P^tree_hash2 => multiset hashing
        return add(mul(ans, Q), R); // to differ the levels from each other
    }

    bool isomorphism(TreeIsomorphism &tr) {
        auto v1 = get_centers();
        auto v2 = tr.get_centers();
        for (auto &u1: v1) {
            for (auto &u2: v2) {
                if (get_hash(u1, -1) == tr.get_hash(u2, -1))
                    return true;
            }
        }
        return false;
    }
};

void solve(int tc) {
    int n;
    cin >> n;
    vector<vector<int> > adj(n + 1), adj2(n + 1);
    int m = n - 1;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj2[u].emplace_back(v);
        adj2[v].emplace_back(u);
    }
    TreeIsomorphism tr1(n, adj), tr2(n, adj2);
    cout << ((tr1.isomorphism(tr2)) ? "YES" : "NO") << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
