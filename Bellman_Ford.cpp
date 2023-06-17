#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using VT = vector<tuple<int, int, int>>;
using PII = pair<int, int>;
using VPII = vector<vector<PII>>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);


void bellman_ford(int start_node, int n, VT& edges, int to_find, int begin_idx=0) {
	int initial_n = n; // Necessary for the outer loop so that it can run n-1 times regardless of if the graph's beginning index is 0 or 1 or whatever
	if (begin_idx > 0) n += begin_idx; // To adjust n if the graph's beginning index is not 0 i.e node 0 does not exist in th graph. This is necessary for the size of the dist and prev array inorder to prevent segmentation fault error

	// 3 steps
	int dist[n];
	int prev[n];

	for (int i = 0; i < n; ++i) {
		dist[i] = INT_MAX;
		prev[i] = -1;
	}

	dist[start_node] = 0;

	for (int i = 0; i < initial_n-1; ++i) {
		for (tuple<int, int, int>& edge: edges) {
			int from, to, weight;
			tie(from, to, weight) = edge;
			// dist[to] = min(dist[to], dist[from] + weight);
			if (dist[from] != INT_MAX && dist[from] + weight < dist[to]) {
				dist[to] = dist[from] + weight;
				prev[to] = from;
			}
		}
	}

	for (auto edge: edges) {
		int from, to, weight;
		tie(from, to, weight) = edge;
		if (dist[from] + weight < dist[to]) {
			cout<<"There is a cycle\n";
		}
	}

	for (int i = begin_idx; i < n; ++i) {
		cout<<"The distance of "<<i<<" from "<<start_node<<" is: "<<dist[i]<<"\n";
	}

	// for (int i = 0; i < n; ++i) {
	// 	cout<<prev[i]<<", ";
	// }
	// cout<<"\n";

	cout<<endl;
	cout<<to_find<<" -> ";
	int parent = prev[to_find];

	while (parent != start_node) {
		cout<<parent<<" -> ";
		parent = prev[parent];
	}
	cout<<start_node;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 4; // number of nodes in the graph
    // VT edges {{0,1,-1}, {0,2,4}, {1,2,3}, {1,3,2}, {1,4,2}, {3,2,5}, {3,1,1}, {4,3,-3}};
    VT edges {{1,2,2}, {1,3,6}, {2,4,3}, {3,4,5}};

    bellman_ford(1, N, edges, 4, 1); // starting node, number of nodes, edge list, node to find the distance from source, graph's beginning node idx

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