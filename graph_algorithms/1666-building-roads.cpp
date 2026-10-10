//██████╗ ██╗ ██████╗     ███████╗
//██╔══██╗██║██╔════╝     ╚══███╔╝
//██████╔╝██║██║  ███╗      ███╔╝
//██╔══██╗██║██║   ██║     ███╔╝
//██████╔╝██║╚██████╔╝    ███████╗
//╚═════╝ ╚═╝ ╚═════╝     ╚══════╝
// حبيبي ليه تغيب و تسيبني لحالي

#include <bits/stdc++.h>
using namespace std;

#define double long double
#define int long long
#define ll long long
#define MX INT_MAX
#define MN INT_MIN
#define wady ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define testcases int t = 1;cin >> t;while(t--)
const long long mod = 1e9 + 7, N = 1000000+50;
const double pi = 3.14159265358979323846;
string YN[2] = { "NO\n","YES\n" };

bool check(int a, int b, int exp) {
    while (exp) {
        if (!(exp % 10 == a or exp % 10 == b))return 0;
        exp /= 10;
    }
    return true;
}

ll fast_power(ll x, ll n) {
    if (x == 1 or n == 0)return 1;
    ll res = 1;
    while (n > 0) {
        if (n % 2 == 1)
            res = (res * x) % mod;
        x = (x * x) % mod;
        n /= 2;
    }
    return res;
}

int fact[N], inv[N];
void alotofcalx() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = fast_power(fact[i], mod - 2);
    }
}


ll c(ll n, ll r) {
    return ((fact[n] * inv[r]) % mod * inv[n - r]) % mod;
}
int last = -1;
bitset<N>vis;
map<int,vector<int>>adj;
void bfs(int start){
    queue<int>a;
    a.push(start);
    vis[start] = 1;
    while(!a.empty()){
        int node = a.front();
        a.pop();
        for(auto i : adj[node]){
            if(!vis[i]){
            vis[i] = 1;
            a.push(i);
        }}
        last = node;
    }
}


void solve() {
int n,m;cin >> n >> m;
for(int i = 0;i<m;i++){
    int u,v;cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
bfs(1);
vector<pair<int, int>> ans;
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            if(last != -1)
                ans.push_back({last, i});
            bfs(i);
        }
    }
    cout << ans.size() << endl;
    for(auto p : ans)cout << p.first << " " << p.second << endl;
}

signed main() {
    wady
   // alotofcalx();
    // testcases
    solve();
}
