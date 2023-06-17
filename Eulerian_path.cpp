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

const int N = 7;

int in_nodes[N] = {0};
int out_nodes[N] = {0};
stack<int> eulerian_path;

bool existence() {
	// For Directed graphs
	int starting = 0, ending = 0;
	for (int i = 0; i < N; ++i) {
		if (out_nodes[i] - in_nodes[i] > 1 || in_nodes[i] - out_nodes[i] > 1) return false;
		else if (out_nodes[i] - in_nodes[i] == 1) starting++;
		else if (in_nodes[i] - out_nodes[i] == 1) ending++;
	}
	return starting == ending && (starting == 1 || starting == 0);
}

int find_starting_node() {
	int rv = 0;
	for (int i = 0; i < N; ++i) {
		if (out_nodes[i] - in_nodes[i] == 1) return i;
		// Make sure the starting node has outgoing edges
		if (out_nodes[i]) rv = i;
	}

	return rv;
}

void hierholzer(int start_node, const VVI& adj) {

	while (out_nodes[start_node] > 0) {
		hierholzer(adj[start_node][--out_nodes[start_node]], adj);
	}

	eulerian_path.push(start_node);
}

int main() {
	// EULERIAN PATHS AND CIRCUITS
    ios_base::sync_with_stdio(0), cin.tie(0);

    VVI edge_list = {{1,2}, {2,5}, {2,3}, {3,5}, {4,1}, {5,4}};
    // Setup
    for(auto& edge: edge_list) {
		++in_nodes[edge[1]];
		++out_nodes[edge[0]];
	}
	
	if (!existence()) {
		cout<<"Cannot find an Eulerian path!\n";
		return 1;
	}

	int starting_node = find_starting_node();

	VVI adj(N);
	for (auto& v: edge_list) {
		adj[v[0]].push_back(v[1]);
	}

	hierholzer(starting_node, adj);

	while (!eulerian_path.empty()) {
		cout<<eulerian_path.top()<<"\n";
		eulerian_path.pop();
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