#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    vector<long long> sub(n,1), ans(n);
    function<void(int, int, int)> dfs=[&](int i, int p, int d){
        ans[0] += d;
        for(int x : g[i]) if(x != p) {
            dfs(x, i, d+1);
            sub[i] += sub[x];
        }
    }; dfs(0, -1, 0);
    function<void(int, int)> dfs2=[&](int i, int p){
        for(int x : g[i]) if(x != p) {
            ans[x] = ans[i] - 2 * sub[x] + n;
            dfs2(x, i);
        }
    }; dfs2(0, -1);
    for(long long x : ans) cout << x << endl;
}
