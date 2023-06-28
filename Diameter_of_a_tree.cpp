#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VLL = vector<ll>;
using VVI = vector<VI>;
using VVLL = vector<VLL>;
using VPII = vector<PII>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);


pair<int, int> dfs(int node, const VVI& adj, bool vis[]) {
    vis[node] = 1;

    pair<int, int> farthest = {0,node};

    for (auto& v: adj[node]) {
        if (!vis[v]) {
            pair<int, int> res = dfs(v, adj, vis);
            res.first++;
            if (res.first > farthest.first) {
                farthest = res;
            }
        }
    }
    return farthest;
}

void solve() {
    // INPUT: 
    /*
        2
        6
        1 2
        1 3
        2 4
        2 5
        3 6
        5
        1 2
        1 3
        3 4
        3 5
    */
    // OUTPUT: 
    /*
        4
        3
    */
    int N; cin>>N;
    VVI adj(N);
    for (int i = 0; i < N-1; ++i) {
        int a, b;
        cin>>a>>b;
        --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // The idea is to run 2 dfs() -> first one finds the longest node 'a' from an arbitrary root
    // Then second one finds the longest node 'c' from node 'a'
    // The distance between a and c is the diameter of the tree

    bool vis[N] = {0};
    pair<int, int> a = dfs(3, adj, vis);

    memset(vis, 0, sizeof(vis));

    pair<int, int> ans = dfs(a.second, adj, vis);
    cout<<ans.first<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
      solve();
    }

    return 0;
}

template <typename T>
void create_vector(T& V, int N) {
    V.resize(N);
    for (int i = 0; i < N; ++i)    
        cin>>V[i];
}

template <typename T>
void display_contents(const T& ds) {
    for (auto& el: ds) {
        cout<<el<<", ";
    }
    cout<<"\n";
}