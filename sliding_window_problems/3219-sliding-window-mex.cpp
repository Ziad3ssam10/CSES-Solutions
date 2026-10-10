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

vector<int> gen(int x,int a,int b,int c,int n) {
    vector<int> ret = {x};
    for (int i = 1; i < n; i++) {
        int temp = ret.back();
        ret.emplace_back((a * temp + b) % c);
    }
    return ret;
}

struct SparseTable {
    vector<int> lg;
    vector<vector<int> > table;

    SparseTable(vector<int> &a) {
        int n = a.size();
        table = vector<vector<int> >(n + 5, vector<int>(20));
        lg.resize(n + 5);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i < n; i++)
            table[i][0] = a[i];
        for (int j = 1; j <= lg[n]; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }

    int query(int l, int r) {
        int sz = lg[r - l + 1];
        return merge(table[l][sz], table[r - (1 << sz) + 1][sz]);
    }

    int merge(int a, int b) {
        return (a | b);
    }
};

void solve(int tc) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    multiset<int> ms;
    map<int,int> mp;
    for (int i = 0; i <= k; i++)ms.insert(i);
    auto add = [&](int x) {
        if (x <= k) {
            if (mp[x] == 0)ms.extract(x);
            mp[x]++;
        }
    };
    auto rem = [&](int x) {
        if (x <= k) {
            mp[x]--;
            if (mp[x] == 0)ms.insert(x);
        }
    };
    for (int i = 0; i < k; i++)add(a[i]);
    cout << *ms.begin() << " ";
    int l = 0, r = k - 1;
    while (r + 1 < n) {
        rem(a[l++]);
        add(a[++r]);
        cout << *ms.begin() << " ";
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
