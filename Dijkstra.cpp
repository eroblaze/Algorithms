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

struct Min_Compare{
	bool operator() (PII& a, PII& b) {
		return a.first > b.first;
	}
};

void dijkstra(int start_node, int n, VPII& adj) {
	int dist[n+1];
	fill(dist, dist+n+1, INT_MAX);
	dist[start_node] = 0;
	bool processed[n+1];
	fill(processed, processed+n+1, false);

	// priority_queue<PII, vector<PII>, Min_Compare> q;
	priority_queue<PII> q;
	q.push({0, start_node});

	while (!q.empty()) {
		int l = q.top().second; q.pop();
		if (processed[l]) continue;
		// db1(l);
		processed[l] = true;

		for (auto v: adj[l]) {
			int to = v.first;
			int weight = v.second;

			if (dist[l] + weight < dist[to]) {
				dist[to] = dist[l] + weight;
				q.push({-dist[to], to});
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout<<"The distance of "<<i<<" from "<<start_node<<" is: "<<dist[i]<<"\n";
	}

}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N = 5;
    VPII edges(N+1);
    edges[1].push_back({2, 5});
    edges[1].push_back({4, 9});
    edges[1].push_back({5, 1});
    edges[2].push_back({1, 5});
    edges[2].push_back({3, 2});
    edges[3].push_back({2, 2});
    edges[3].push_back({4, 6});
    edges[4].push_back({3, 6});
    edges[4].push_back({1, 9});
    edges[4].push_back({5, 2});
    edges[5].push_back({4, 2});
    edges[5].push_back({1, 1});


    dijkstra(1, N, edges);
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