#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);

VI sorted_arr;
int faulty_node = -1;

bool dfs(int node, VVI adj, int state[]) {
    state[node] = 1; // processing

    for (int v: adj[node]) {
        if (state[v] == 1) {
            // There is a cycle
            faulty_node = v;
            return false;
        } else if (!state[v]) {
            if (!dfs(v, adj, state)) return false;
        }
    }

    state[node] = 2; // processed;
    sorted_arr.push_back(node);
    return true;
}

void topological_sort(VVI adj) {
    // This is topological sort using DFS
    // There is another one using BFS called "Kahn's algorithm"
    int N = adj.size();
    int state[N] = {0};

    for (int i = 1; i < N; ++i) {
        if (!state[i]) {
            if (!dfs(i, adj, state)) {
                cout<<"CYCLE DETECTED AT NODE -> "<<faulty_node<<"\n";
                break;
            }
        }
    }
    // display_contents(sorted_arr);
    reverse(sorted_arr.begin(), sorted_arr.end());
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 7;
    VVI adj(N);
    adj[1].push_back(2);
    adj[1].push_back(4);
    adj[2].push_back(3);
    adj[3].push_back(6);
    adj[4].push_back(5);
    adj[5].push_back(2);
    adj[5].push_back(3);

    topological_sort(adj);

    display_contents(sorted_arr);
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