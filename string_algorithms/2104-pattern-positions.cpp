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



struct SuffixAutomaton {
    int last = 0, cntState = 1;

    struct state {
        int len = 0, link = -1, cnt = 0, first_pos = 0;
        map<char, int> next;
    };

    vector<state> st;
    int n;

    SuffixAutomaton(int _n) {
        n = _n;
        st.resize(n * 2);
    }

    void addChar(char c) {
        int p = last;
        int cur = cntState++;
        st[cur].len = st[last].len + 1;
        st[cur].cnt = 1;
        st[cur].first_pos = st[cur].len - 1;
        while (p != -1 && st[p].next.count(c) == 0) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[q].len == st[p].len + 1) {
                st[cur].link = q;
            } else {
                int clone = cntState++;
                st[clone].link = st[q].link;
                st[clone].len = st[p].len + 1;
                st[q].link = st[cur].link = clone;
                st[clone].next = st[q].next;
                st[clone].cnt = 0;
                st[clone].first_pos = st[q].first_pos;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
            }
        }
        last = cur;
    }
};

void solve(int tc) {
    string s;
    cin >> s;
    int n;
    cin >> n;
    SuffixAutomaton st(s.size() +1);
    for (auto c: s)st.addChar(c);
    for (int i = 0; i < n; i++) {
        string p;
        cin >> p;
        int cur = 0;
        bool found = 1;
        for (auto c: p) {
            if (st.st[cur].next.count(c)) {
                cur = st.st[cur].next[c];
            } else {
                found = 0;
                break;
            }
        }
        if (found) {
            cout << st.st[cur].first_pos - p.size() + 2 << endl;
        } else cout << "-1\n";
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
