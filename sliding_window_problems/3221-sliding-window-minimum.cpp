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

struct MonotonicMinDeque {
    deque<int> dq;
    vector<long long> *arr;

    MonotonicMinDeque(vector<long long> &a) {
        arr = &a;
    }

    void push(int i) {
        while (!dq.empty() && (*arr)[dq.back()] >= (*arr)[i])
            dq.pop_back();
        dq.push_back(i);
    }

    void pop(int i) {
        if (!dq.empty() && dq.front() == i)
            dq.pop_front();
    }

    long long get() {
        return (*arr)[dq.front()];
    }

    bool empty() {
        return dq.empty();
    }
};

void solve(int tc) {
    int n, k;
    cin >> n >> k;
    int x, aa, b, c;
    cin >> x >> aa >> b >> c;
    auto a = gen(x, aa, b, c, n);
    int ans = 0;
    MonotonicMinDeque dq(a);
    for (int i = 0; i < k; i++)dq.push(i);
    int sum = dq.get();
    ans = sum;
    int l = 0, r = k - 1;
    while (r + 1 < n) {
        dq.pop(l++);
        dq.push(++r);
        ans ^= dq.get();
    }
    cout << ans << endl;
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
