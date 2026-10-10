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


int lengthOfLIS(vector<int> &nums) {
    vector<int> temp;
    for (int num: nums) {
        auto it = lower_bound(temp.begin(), temp.end(), num);
        if (it == temp.end()) {
            temp.push_back(num);
        } else {
            *it = num;
        }
    }
    return temp.size();
}

void solve(int tc) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i: a)cin >> i;
    cout << lengthOfLIS(a) << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    int tc = 1;
    while (t--)
        solve(tc++);
}
