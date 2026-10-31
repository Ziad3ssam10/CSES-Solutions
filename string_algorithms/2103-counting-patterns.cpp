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

// N * sqrt(sum of lens) ---- vaild to 5e5 it will be  ~ 3e8
// if it all uniuqe it will be  ( n ^ 2)
struct Aho {
    int n;
    const int Alpha = 26;
    vector<vector<int> > nxt, out;
    vector<int> link, outlink;
    // nxt[][] at each node it tells u where to fail if i add that char
    // link[] at each node the lPS
    // outlink[] at each node the lps i can match and hads a pattern
    // out [][] at each node the indcies for the patterns i match it
    int node() {
        link.emplace_back(0);
        outlink.emplace_back(0);
        nxt.emplace_back(Alpha, 0);
        out.emplace_back(0);
        return n++;
    }

    Aho() : n(0) {
        node();
    };

    int idx(char c) {
        return c - 'a';
    }

    void add_pat(string &pat,int i) {
        int u = 0;
        for (auto c: pat) {
            if (nxt[u][idx(c)] == 0) nxt[u][idx(c)] = node();
            u = nxt[u][idx(c)];
        }
        out[u].emplace_back(i);
    }

    void build() {
        queue<int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < Alpha; ++c) {
                int v = nxt[u][c];
                if (!v) nxt[u][c] = nxt[link[u]][c];
                else {
                    link[v] = u ? nxt[link[u]][c] : 0;
                    outlink[v] = out[link[v]].empty() ? outlink[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int go(int u, char c) {
        while (u and !nxt[u][idx(c)]) u = link[u];
        u = nxt[u][idx(c)];
        return u;
    }
};

void solve(int tc) {
    string s;
    cin >> s;
    int n;
    cin >> n;
    map<string,int> mp;
    Aho a7a;
    vector<string> pat(n);
    for (auto &i: pat)cin >> i;
    for (int i = 0; i < n; i++) {
        string t = pat[i];
        if (mp.count(t))continue;
        a7a.add_pat(t, i);
        mp[t] = i;
    }
    a7a.build();
    vector<int> ans(n);
    int u = 0;
    for (auto &c: s) {
        u = a7a.go(u, c);
        for (int v = u; v; v = a7a.outlink[v]) {
            for (auto &i: a7a.out[v])ans[i]++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[mp[pat[i]]] << endl;
    }
}

signed main() {
    wady
 //   files();
    int t = 1;
    //   cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
