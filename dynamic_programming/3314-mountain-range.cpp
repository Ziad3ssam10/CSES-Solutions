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

vector<int> nextGreater(vector<int> &a) {
    int n = a.size();
    vector<int> nxt(n, n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[i] > a[st.top()]) {
            nxt[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return nxt;
}

vector<int> prevGreater(vector<int> &a) {
    int n = a.size();
    vector<int> pre(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            st.pop();
        }
        while (!st.empty() && a[st.top()] == a[i]) {
            st.pop();
        }
        if (!st.empty()) pre[i] = st.top();
        st.push(i);
    }
    return pre;
}

void solve(int tc) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;

    auto prv = prevGreater(a);
    auto nxt = nextGreater(a);

    vector<vector<int>> adj(n + 5);
    vector<int> in(n + 2, 0);

    for (int i = 0; i < n; i++) {
        if (prv[i] != -1 && nxt[i] != n) {
            int par = (a[prv[i]] < a[nxt[i]]) ? prv[i] : nxt[i];
            adj[par].emplace_back(i);
            in[i]++;
        } else if (prv[i] != -1) {
            int par = prv[i];
            adj[par].emplace_back(i);
            in[i]++;
        } else if (nxt[i] != n) {
            int par = nxt[i];
            adj[par].emplace_back(i);
            in[i]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!in[i]) q.emplace(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        topo.emplace_back(node);
        for (auto &child : adj[node]) {
            in[child]--;
            if (!in[child]) {
                q.emplace(child);
            }
        }
    }

    vector<int> dp(n, 1);
    reverse(topo.begin(), topo.end());
    for (auto node : topo) {
        int maxi = 0;
        for (auto &child : adj[node]) {
            maxi = max(maxi, dp[child]);
        }
        dp[node] = maxi + 1;
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}

signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
    return 0;
}