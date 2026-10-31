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
    lps.assign(sz, 0);
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

vector<int> p[2];

void Manacher(string &s) {
    int n = s.size();
    p[0].resize(n + 1); // even
    p[1].resize(n); // odd
    for (int z = 0; z < 2; z++) {
        for (int i = 0, l = 0, r = 0; i < n; i++) {
            int t = r - i + !z;
            if (i < r) p[z][i] = min(t, p[z][l + t]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L >= 1 and R + 1 < n and s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    }
}

bool query(int l, int r) {
    int mid = (l + r + 1) / 2, len = r - l + 1;
    return 2 * p[len % 2][mid] + len % 2 >= len;
}

void solve(int tc) {
    string s;
    cin >> s;
    Manacher(s);
    int n = s.size();
    int even = *max_element(p[0].begin(), p[0].end());
    int odd = *max_element(p[1].begin(), p[1].end());
    if (even == 0 and odd == 0)cout << s[0] << endl;
    else if (even > odd) {
        for (int i = 0; i < n; i++) {
            if (p[0][i] == even) {
                cout << s.substr(i - even, 2 * even);
                break;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (p[1][i] == odd) {
                cout << s.substr(i - odd, 2 * odd + 1);
                break;
            }
        }
    }
}

signed main() {
    wady
   // files();
    int tc = 1;
    int tt = 1;
    // cin >> tt;
    while (tt--)solve(tc++);
}

