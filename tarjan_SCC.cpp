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

#define N 7
VVI adj(N+1);
int disc[N],low[N];
stack<int> nodes;
bool in_stack[N];
bool vis[N];

void tarjan_SCC(int node) {
	static int time = 1; // Can also be a global variable
	disc[node] = low[node] = time++;

	in_stack[node] = true;
	vis[node] = true;
	nodes.push(node);

	for (auto v: adj[node]) {
		if (!vis[v]) {
			tarjan_SCC(v);
			low[node] = min(low[node], low[v]);
		} else if (in_stack[v]) {
			// We only care about visited nodes that are in the stack i.e ancestor nodes
			// This is a Back-edge
			// If v is not in the stack, it is a cross-edge
			low[node] = min(low[node], disc[v]);
		}
	}

	if (disc[node] == low[node]) {
		// This is the head of a SCC
		while (nodes.top() != node) {
			cout<<nodes.top()<<" -> ";
			nodes.pop();
		}
		cout<<nodes.top()<<"\n";
		nodes.pop();
	}

	in_stack[node] = false;
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

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

	// Create disc, low and stack arrays
	fill(disc, disc+N, 0);
	fill(low, low+N, 0);
	fill(in_stack, in_stack+N, false);
	fill(vis, vis+N, false);

	for (int i = 1; i < N; ++i) {
		if (!vis[i]) {
			tarjan_SCC(i);
		}
	}

    return 0;
}

template <typename T>
void display_contents(const T& ds) {
    for (auto& el: ds) {
        cout<<el<<", ";
    }
    cout<<"\n";
}