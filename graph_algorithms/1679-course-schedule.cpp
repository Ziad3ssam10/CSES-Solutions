#include <bits/stdc++.h>
using namespace std;
std::vector<int> *adj, subjects;
int *in;
void dfs(int i){
    in[i] = 1e9;
    subjects.push_back(i);
    for(int ch : adj[i])
        if(!--in[ch])
            dfs(ch);
}
int main() {
    int n, m;
    std::cin >> n >> m;
    adj = new std::vector<int>[n];
    in = new int[n]{};
    while(m--){
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        ++in[v];
    }
    for(int i=0; i<n; ++i)
        if(!in[i])
            dfs(i);
    if(subjects.size() != n) std::cout << "IMPOSSIBLE";
    else
        for(int x : subjects)
            std::cout << x+1 << ' ' ;
}