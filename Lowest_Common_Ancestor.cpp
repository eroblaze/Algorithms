#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VPII = vector<PII>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);


void dfs(int node, const VVI& adj, VVI& dfs_arr, VI& depth_arr, int depth = 0) {
    dfs_arr.push_back({node, depth});
    depth_arr[node] = depth;

    for (auto v: adj[node]) {
        dfs(v, adj, dfs_arr, depth_arr, depth+1);
        dfs_arr.push_back({node, depth});
    }
}

int lowest_common_ancestor(int a, int b, const VVI& dfs_arr) {
    // Euler Tour Technique
    int N = dfs_arr.size();
    int min_depth = INT_MAX;
    int lca = 0;

    for (int i = 0; i < N; ++i) {
        if (dfs_arr[i][0] == a || dfs_arr[i][0] == b) {

            int node = dfs_arr[i][0];
            min_depth = dfs_arr[i][1];
            lca = node;
            int a_or_b = (node == a) ? b: a;

            while (node != a_or_b) {
                node = dfs_arr[++i][0];
                if (dfs_arr[i][1] < min_depth) {
                    min_depth = dfs_arr[i][1];
                    lca = node;
                }
            }
            break;
        }
    }
    return lca;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 9;

    VVI adj(N);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[2].push_back(5);
    adj[2].push_back(6);
    adj[4].push_back(7);
    adj[6].push_back(8);

    VVI dfs_arr;
    VI depth_arr(N);

    dfs(1, adj, dfs_arr, depth_arr);

    int node = lowest_common_ancestor(5, 8, dfs_arr);
    db1(node);

    // To get the distance between two nodes, get their lowest common ancestor and run this formula :
    // depth(a) + depth(b) - 2*depth(c) where c is their lca

    int m_dist = (depth_arr[5] + depth_arr[8]) - (2*depth_arr[node]);
    db1(m_dist);

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