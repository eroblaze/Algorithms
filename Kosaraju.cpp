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

void dfs(int node, VVI adj, bool vis[], stack<int>& top_sort) {
	vis[node] = true;

	for (auto v: adj[node]) {
		if (!vis[v]) dfs(v, adj, vis, top_sort);
	}

	top_sort.push(node);
}

VI dfs2(int node, const VVI& transpose_adj, bool vis[]) {
	vis[node] = true;

	VI m_component;

	for (int v: transpose_adj[node]) {
		if (!vis[v]) {
			VI child_component = dfs2(v, transpose_adj, vis);
			m_component.insert(m_component.begin(), child_component.begin(), child_component.end());
		}
	}
	m_component.insert(m_component.begin(), node);
	return m_component;
}

VVI create_tranpose(const VVI& adj, int N) {
	VVI transpose(N+1);

	for (int i = 1; i <= N; ++i) {
		for (int j: adj[i]) {
			transpose[j].push_back(i);
		}
	}

	return transpose;
}

void kosaraju(VVI adj, int N) {
	stack<int> top_sort;
	bool vis[N+1] = {false};

	// FIRST step - Run topological sort
	for (int i = 1; i <= N; ++i) {
		if (!vis[i]) {
			dfs(i, adj, vis, top_sort);
		}
	}

	// SECOND step - Create the transpose of adj
	VVI transpose_adj = create_tranpose(adj, N);

	// THIRD step - Run dfs one last time on the transpose starting at every popped element from the stack and get the Strongly Connected Components (last the normal pattern)
	fill(vis, vis+N+1, false);

	while (!top_sort.empty()) {
		int node = top_sort.top(); top_sort.pop();

		if (vis[node]) continue;
		VI component = dfs2(node, transpose_adj, vis);
		cout<<"SCC -> ";
		display_contents(component);
	}
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

	int N = 7;
	VVI adj(N+1);
	adj[1].push_back(2);
	adj[2].push_back(1);
	adj[2].push_back(3);
	adj[3].push_back(6);
	adj[4].push_back(1);
	adj[4].push_back(5);
	adj[5].push_back(2);
	adj[5].push_back(6);
	adj[6].push_back(7);
	adj[7].push_back(3);

	kosaraju(adj, N);

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