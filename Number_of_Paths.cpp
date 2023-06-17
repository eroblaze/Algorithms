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

#define N_size 7
VI top_sort;
int state[N_size];

void topological_sort(int node, int adj_mat[][N_size]) {
    // graph should be a directed acyclic graph so no need to check for cycles
    state[node] = 1; // processing

    // To find the neighbors of 'node' in the adjacency matrix
    for (int i = 1; i < N_size; ++i) {
        if (node == i || state[i]) continue;
        if (adj_mat[node][i] == 1) {
            // There is an edge
            topological_sort(i, adj_mat);
        }
    }

    state[node] = 2; // processed
    top_sort.push_back(node);
}

int new_paths(int source, int x, int adj_matrix[][N_size]) {
    // First get a topological sort of the graph
    fill(state, state+N_size, 0);

    for (int i = 1; i < N_size; ++i) {
        if (!state[i]) topological_sort(i, adj_matrix);
    }
    reverse(top_sort.begin(), top_sort.end());

    // Pick each node accordingly from the top_sort and find the number of paths from the node to source
    // The idea is that before we get to any node, the number of paths from all nodes leading to that particular node from the source will already have been calculated
    // path(x) = path(a) + path(b)... where 'a' and 'b' are nodes that leads to 'x'
    
    int number_of_paths[N_size];
    fill(number_of_paths, number_of_paths+N_size, 0);

    number_of_paths[source] = 1; // IMPORTANT

    for (auto v: top_sort) {
        if (v == source) continue;

        // Finding all nodes that leads to 'v' in the adjacency matrix
        for (int i = 1; i < N_size; ++i) {
            if (i != v && adj_matrix[i][v] == 1) {
                number_of_paths[v]+=number_of_paths[i];
            }
        }

        if (v == x) break;
    }

    return number_of_paths[x];
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int adj_mat[N_size][N_size] = {
        {},
        {0, 1, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1},
    };

    int number_of_paths2 = new_paths(1, 6, adj_mat);
    db1(number_of_paths2);

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