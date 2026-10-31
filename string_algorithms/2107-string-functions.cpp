#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ll long long
#define ld  long double
#define endl '\n'
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define wady ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void files() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
}


vector<int> build_lps(string p) {
    int sz = p.size();
    vector<int> lps;
    lps.assign(sz , 0);
    int j = 0;
    lps[0] = 0;
    for (int i = 1; i < sz; i++) {
        while (j >= 0 and p[i] != p[j]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        j++;
        lps[i] = j;
    }
    return lps;
}

vector<int> build_z(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r)z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n and s[z[i]] == s[z[i] + i])z[i]++;
        if (i + z[i] > r)l = i, r = i + z[i];
    }
    return z;
}

void solve(int tc) {
    string s;
    cin >> s;
    vector<int> z = build_z(s);
    vector<int> pi = build_lps(s);
    for (auto &i: z)cout << i << " ";
    cout << endl;
    for (auto &i: pi)cout << i << " ";
}

signed main() {
    wady
   // files();
    int tc = 1;
    int tt = 1;
   // cin >> tt;
    while (tt--)solve(tc++);
}

