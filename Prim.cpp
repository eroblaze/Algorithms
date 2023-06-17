#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;

using PII = pair<int, int>;
using PQI = priority_queue<int>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);

int Prim(vector<vector<pair<int, int>>> adj) {
    int N = adj.size();
    int source = 3;
    priority_queue<tuple<int, int, int>> nodes;
    nodes.push({0, source, source});

    bool vis[N] = {false};

    vector<pair<int, int>> spanning_tree;
    int minimum_spanning_tree = 0;

    while (!nodes.empty()) {
        int node, w, par;
        tie(w, node, par) = nodes.top(); nodes.pop();

        if (vis[node]) continue;

        // db2(node, abs(w));
        if (node != par)  spanning_tree.push_back({par,node});
        vis[node] = true;

        minimum_spanning_tree += abs(w);

        if (spanning_tree.size() == N-2) break; // It is '-2' because the example graph starts at 1 not 0

        for (pair<int, int> n: adj[node]) {
            if (!vis[n.first]) {
                nodes.push({-n.second, n.first, node});
            }
        }
    }

    // if spanning_tree.size() != N-2, a minimum spanning tree can't be formed from the graph
    display_contents(spanning_tree);
    return minimum_spanning_tree;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 6; vector<tuple<int, int, int>> edge_list{{1,2,3}, {1,5,5},
    {2,5,6}, {2,3,5}, {3,4,9}, {3,6,3}, {4,6,7}, {5,6,2}};

    vector<vector<pair<int, int>>> adj(N+1);
    adj[1].push_back({2,3});
    adj[2].push_back({1,3});
    adj[1].push_back({5,5});
    adj[5].push_back({1,5});
    adj[2].push_back({5,6});
    adj[5].push_back({2,6});
    adj[2].push_back({3,5});
    adj[3].push_back({2,5});
    adj[3].push_back({4,9});
    adj[4].push_back({3,9});
    adj[3].push_back({6,3});
    adj[6].push_back({3,3});
    adj[4].push_back({6,7});
    adj[6].push_back({4,7});
    adj[5].push_back({6,2});
    adj[6].push_back({5,2});
   
    db1(Prim(adj));

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
        cout<<el.first<<" -> "<<el.second<<"\n";
    }
    cout<<"\n";
}