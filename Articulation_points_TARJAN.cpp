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

vector<bool> articulation_points;
VI disc;
VI low;

int tarjan(int node, const VVI& adj, int parent=-1) {
	static int time = 0;
	disc[node] = low[node] = time++;

	int children_count = 0;

	for (auto v: adj[node]) {
		// 3 conditions
		// 1) UNVISITED
		if (disc[v] == -1) {
			++children_count;

			tarjan(v, adj, node);
			low[node] = min(low[node], low[v]);

			// 2ND Condition - If at least one descendant has a low value that is greater than or equal to disc[node]
			// i.e that descendant is dependant on 'node' before it can be reached
			if (low[v] >= disc[node]) {
				// 'node' is an articulation point
				articulation_points[node] = true;
			}
		} else if (v != parent) {
			// 2) VISITED - This is a back-edge to an ancestor node
			// 3) We assume that the parent has been removed so we don't want to traverse the parent node through the child
			low[node] = min(low[node], disc[v]);
		}
	}
	return children_count;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 6;
    VVI adj(N);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);
    adj[4].push_back(5);
    adj[5].push_back(4);
    adj[5].push_back(2);
    adj[2].push_back(5);

    articulation_points = vector<bool>(N, false);
    disc = VI(N, -1);
    low = VI(N);
	
	// In case the graph is DISCONNECTED
	for (int i = 1; i < N; ++i) {
		if (disc[i] == -1) {
			// 1ST Condition - if the root has at least 2 sub-graphs
			articulation_points[i] = tarjan(i, adj, -1) >= 2; // returns the root's number of children sub-graphs
		}
	}

	// Print out the bridges if any
	bool found = false;
	for (int i = 1; i < N; ++i) {
		if (articulation_points[i]) {
			found = true; // For printing out message
			cout<<i<<"\n";
		}
	}
	if (!found) cout<<"There are no articulation_points in the provided graph\n";

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