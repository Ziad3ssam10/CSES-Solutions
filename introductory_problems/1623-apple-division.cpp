//██████╗ ██╗ ██████╗     ███████╗
//██╔══██╗██║██╔════╝     ╚══███╔╝
//██████╔╝██║██║  ███╗      ███╔╝
//██╔══██╗██║██║   ██║     ███╔╝
//██████╔╝██║╚██████╔╝    ███████╗
//╚═════╝ ╚═╝ ╚═════╝     ╚══════╝
// Pleeeease stay , I need U I want U Oh god
//    dont take this beautiful things
//           that ive got
#include<bits/stdc++.h>
using namespace std;
#define double long double
#define ll long long
#define MX INT_MAX
#define MN INT_MIN
#define wady ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define testcases int t = 1;cin >> t;while(t--)
const long long mod = 1e9 + 7, N = 2e5 + 10;
const double pi = 3.14159265358979323846;
// GCD and LCM
ll gcd(ll a, ll b) { return (a == 0) ? b : gcd(b % a, a); }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }
// Co primes
vector<int>coprime[1000+10];
void pre_calc_coprime(){
    for (int i = 1; i <= 1000; ++i)
        for (int j = i ; j <= 1000; ++j)
            if (gcd(i, j) == 1) {
                coprime[i].push_back(j);
                coprime[j].push_back(i);
            }
}
// sieve
bool primes[N];
void sieve() {
// Time Complexity : O(Nlog(log(N))).
int N = 1000;
    memset(primes, true, sizeof primes);
    primes[0] = primes[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (primes[i]) {
            for (int j = i * i; j < N; j += i) {
                primes[j] = false;
            }
        }
    }
}
// SPF
vector<int>spf(N);
void SPF(){
    int NN = 1000;
    spf[1] = 1;
    // making spf to every num is itself
    for (int i=2; i<NN; i++)
        spf[i] = i;
    for (int i=4; i<NN; i+=2)
        spf[i] = 2;

    for (int i=3; i*i<NN; i++){
        if (spf[i] == i){
            for (int j=i*i; j<NN; j+=i)
                if (spf[j]==j)
                    spf[j] = i;
        }
    }
}
// prime factor
vector<int> factrz(int x){
    vector<int> ret;
    while (x != 1){
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}
//fast power
ll fast_power(ll x, ll n) {
   if (x == 1 or n == 0)return 1; int res = 1;
    while (n > 0) { if (n % 2 == 1) res *= x; x *= x, n /= 2; }return res;
}
// lot of pre-calc
int fact[N], inv[N];
void alotofcalx() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = (fact[i - 1] * i) % mod, inv[i] = fast_power(fact[i], mod - 2);
}
// prop
ll c(ll n, ll r) {
    return ((fact[n] * inv[r]) % mod * inv[n - r]) % mod;
}

ll p(ll n, ll r) {
    return ((fact[n] * inv[n - r])) % mod;
}
int starsAndBars(int stars, int bars){
    return c(stars + bars, bars);
}
// GRAPH
vector<int> adj[1000000+10];
bool vis[1000000+10],recstack[1000000+10], cycle = 0;
int ans = MN;
void dfs(int node, int parent) {
    vis[node] = true;
    for (int child : adj[node]) {
        if (!vis[child])
            dfs(child, parent);
        // cycle detection undirected graph
      // else if (vis[child] and child != parent)cycle = true;
    }
}
void bfs(int start) {
    queue<int> q;
    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int child : adj[node]) {
            if (!vis[child]) {
                q.push(child);
                vis[child] = true;
            }
        }
    }
}
int n;
//cin >> n;
vector<int> a;
ll rec(int idx, ll sum1, ll sum2)
{
    if (idx == n)
        return abs(sum1 - sum2);
    ll choose = rec(idx + 1, sum1 + a[idx], sum2);
    ll notChoose = rec(idx + 1, sum1, sum2 + a[idx]);

    return min(choose, notChoose);
}
void solve() {
    //  int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        int x;cin >> x;
         a.push_back(x);
    //cin >> a[i];
}
int ans = rec(0,0,0);
    cout << ans << endl;

}

int main(){
    wady
    //testcases
    solve();
}