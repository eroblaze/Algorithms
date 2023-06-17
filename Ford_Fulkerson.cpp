#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VPII = vector<PII>;
using VVI = vector<VI>;
using VVPII = vector<vector<PII>>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);

const int N = 7;

pair<deque<int>, int> find_augmented_path_BFS_EDMONDS_KARP(const VVI& residual_graph, int source, int sink, bool vis[], pair<deque<int>, int>& path, int minimum_capacity=INT_MAX) {
	int parent[N];
	fill(parent, parent+N, -1);
	bool found = false;

	queue<int> bfs;
	bfs.push(source);

	while (!bfs.empty()) {
		int node = bfs.front(); bfs.pop();
		vis[node] = true;

		if (node == sink) {
			found = true;
			break;
		}

		for (int i = 1; i < N; ++i) {
			if (!vis[i] && residual_graph[node][i] > 0) {
				bfs.push(i);
				parent[i] = node;
			}
		}
	}

	pair<deque<int>, int> rv = {deque<int>(), INT_MAX};
	if (found) {
		while (sink != source) {
			rv.first.push_front(sink);
			rv.second = min(rv.second, residual_graph[parent[sink]][sink]);
			sink = parent[sink];
		}
		rv.first.push_front(sink);
	}

	return rv;
}

pair<deque<int>, int> find_augmented_path(const VVI& residual_graph, int source, int sink, bool vis[], pair<deque<int>, int>& path, int minimum_capacity=INT_MAX) {
	// This is the major engine in the Ford-Fulkerson method
	get<0>(path).push_back(source);
	get<1>(path) = min(get<1>(path), minimum_capacity);

	if (source == sink) {
		return path;
	}

	vis[source] = true;

	for (int i = 1; i < N; ++i) {
		int to = i, cap = residual_graph[source][i];
		if (!vis[to] && cap > 0) {
			pair<deque<int>, int> rv = find_augmented_path(residual_graph, to, sink, vis, path, cap);
			if (get<0>(rv).size() > 0) {
				return rv;
			}
		}
	}

	get<0>(path).pop_back();
	return pair<deque<int>, int>();
}

int Ford_Fulkerson(const VVI& flow_network, int source, int sink) {
	// Returns the maximum flow that can be passed from the source to the sink in the flow network
	int maximum_flow = 0;
	int n = flow_network.size();

	VVI residual_graph = flow_network;

	bool vis[n] = {false};
	pair<deque<int>, int> tmp_path = {deque<int>(), INT_MAX};
	pair<deque<int>, int> augmented_path = find_augmented_path_BFS_EDMONDS_KARP(residual_graph, source, sink, vis, tmp_path);

	while (get<0>(augmented_path).size() > 0) {
		// Find the maximum flow of the augmenting path or the Minimum capacity of an edge in the path
		// already calculated this in the 'find_augmented_path' function
		int flow = get<1>(augmented_path);
		db1(flow);
		maximum_flow += flow;

		// augment the flow of edges in the augmented path
		int par = get<0>(augmented_path).front(); get<0>(augmented_path).pop_front();

		while (!get<0>(augmented_path).empty()) {
			int to = get<0>(augmented_path).front(); get<0>(augmented_path).pop_front();
			residual_graph[par][to] -= flow;
			residual_graph[to][par] += flow;
			par = to;
		}

		// cleanup
		fill(vis, vis+n, false);
		tmp_path = {deque<int>(), INT_MAX};
		augmented_path = find_augmented_path_BFS_EDMONDS_KARP(residual_graph, source, sink, vis, tmp_path);
	}

	return maximum_flow;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    VVI flow_network(N, VI(N));
    flow_network[1][2] = 5;
    flow_network[1][4] = 4;
    flow_network[2][3] = 6;
    flow_network[3][5] = 8;
    flow_network[3][6] = 5;
    flow_network[4][2] = 3;
    flow_network[4][5] = 1;
    flow_network[5][6] = 2;

    const int source = 1, sink = 6;

    int maximum_flow_val = Ford_Fulkerson(flow_network, source, sink);
    db1(maximum_flow_val);

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