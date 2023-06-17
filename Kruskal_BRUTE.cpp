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

struct Compare_sort {
	bool operator() (const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
		return get<2>(a) > get<2>(b);
	}
};

bool find(vector<vector<pair<int, int>>> adj, int node, int b, bool vis[]) {
	if (vis[node]) return false;
	vis[node] = true;

	for (auto v: adj[node]) {
		if (v.first == b) return true;
		if (find(adj, v.first, b, vis)) return true;
	}

	return false;
}

int dfs(int node, vector<vector<pair<int, int>>> adj, bool vis[]) {
	if (vis[node]) return 0;
	vis[node] = true;
	int t_weight = 0;

	for (auto v: adj[node]) {
		if (!vis[v.first]) t_weight += v.second;
		int w = dfs(v.first, adj, vis);
		t_weight += w;
	}

	return t_weight;
}


void kruskal(priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, Compare_sort> edge_list, int N) {
	vector<vector<pair<int, int>>> adj(N+1);
	bool vis[N+1] = {false};

	while(!edge_list.empty()) {
		auto edge = edge_list.top(); edge_list.pop();
		int a = get<0>(edge);
		int b = get<1>(edge);
		if (!find(adj, a, b, vis)) {
			adj[a].push_back({b, get<2>(edge)});
			adj[b].push_back({a, get<2>(edge)});
		}
		fill(vis, vis+N+1, false);
	}

	int minimum_spanning_tree = dfs(1, adj, vis);
	db1(minimum_spanning_tree);

}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 6;
	vector<tuple<int, int, int>> edge_list{{1,2,3}, {1,5,5}, {2,5,6}, {2,3,5}, {3,4,9}, {3,6,3}, {4,6,7}, {5,6,2}};

	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, Compare_sort> sorted_edges;

	for (auto edge: edge_list) {
		sorted_edges.push(edge);
	}

	kruskal(sorted_edges, N);

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