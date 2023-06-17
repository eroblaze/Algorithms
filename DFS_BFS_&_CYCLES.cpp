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

bool has_something(int, VVI&, bool*);

void display_graph(VVI& g) {
	for (int i = 0; i < g.size(); ++i) {
		cout<<i<<" -> ";
		for (int j = 0; j < g[i].size(); ++j) {
			cout<<g[i][j]<<", ";
		}
		cout<<"\n";
	}
}

void dfs(VVI& g, int node, bool visited[]) {
	if (visited[node]) return;
	visited[node] = true;

	// db1(node);
 	cout<<node<<" -> ";


	for (auto n: g[node]) {
		dfs(g, n, visited);
	}
}

void bfs(VVI& g, int node, bool visited[], int distance_arr[]) {
	queue<int> nodes;
	nodes.push(node);

	while (!nodes.empty()) {
		int N = nodes.front();
		visited[N] = true;
		nodes.pop(); // very important step

		db2(N, distance_arr[N]);

		for (int n: g[N]) {
			if (visited[n]) continue;
			nodes.push(n);
			distance_arr[n] = distance_arr[N]+1;
		}
	}
}

 bool dfs_cycle(int node, VVI& adj, bool visited[], int parent) {
 	visited[node] = true;

 	for (auto v: adj[node]) {
 		if (visited[v]) {
 			if (v == parent) continue;
 			// db2(v,parent);
 			return true;
 		} 
		bool something = dfs_cycle(v, adj, visited, node);
		// db2(node, something);
		if (something) return true;
 	}

 	return false;
};

 bool has_cycle(int n, VVI& adj, bool visited[]) {
 	for (int i = 1; i < n; ++i) {
 		if (!visited[i]) {
 			cout<<"New component\n";
 			// if (dfs_cycle(i, adj, visited, -1)) return true;
 			dfs(adj, i, visited);
          	cout<<"\n";
 		}
 	}
 	return false;
}

 bool checkForCycle(int node, int parent, vector < int > & vis, VVI adj) {
      vis[node] = 1;
      for (auto it: adj[node]) {
        if (!vis[it]) {
          if (checkForCycle(it, node, vis, adj))
            return true;
        } else if (it != parent)
          return true;
      }

      return false;
    }

bool isCycle(int V, VVI adj) {
  vector < int > vis(V + 1, 0);
  for (int i = 0; i < V; i++) {
    if (!vis[i]) {
      if (checkForCycle(i, -1, vis, adj)) return true;
    }
  }

  return false;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int N = 6;

    VVI adj(N);

    adj[1].push_back(3);
    // adj[1].push_back(4);
    adj[3].push_back(1);
    adj[3].push_back(4);
    // adj[4].push_back(1);
    adj[4].push_back(3);
    adj[2].push_back(5);
    adj[5].push_back(2);

    // display_graph(adj);

    bool visited[N] = {false};

    // cout<<(has_cycle(N, adj, visited)?"TRUE":"FALSE")<<"\n";
    cout<<(has_something(N, adj, visited)?"TRUE":"FALSE")<<"\n";
    
    visited[N] = {false};

    cout<<(isCycle(N, adj)?"TRUE":"FALSE");

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

void new_dfs(int node, VVI& adj, bool visited[], int& N, int& M, int parent) {
	++N;
	visited[node] = true;
	// cout<<node<<" -> ";

	for (auto v: adj[node]) {
		if (!visited[v]) {
			++M;
			new_dfs(v, adj, visited, N,M,node);
		} else if (v != parent) ++M;
	}
}

bool has_something(int n, VVI& adj, bool visited[]) {
	int number_of_nodes = 0, number_of_edges = 0;
	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			new_dfs(i, adj, visited, number_of_nodes, number_of_edges, -1);

			db2(number_of_nodes, number_of_edges);
			if (number_of_edges >= number_of_nodes) return true;

			number_of_edges = 0;
			number_of_nodes = 0;
		}
	}
	return false;
}