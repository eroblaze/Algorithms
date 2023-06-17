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


void display_matrix(const VVI& dist) {
	int n = dist.size();

	for (int i = 1; i < n; ++i) {
		cout<<i<<" -> ";
		for (int j = 1; j < n; ++j) {
			cout<<"("<<j<<" == "<<(dist[i][j] == INT_MAX?"INF":to_string(dist[i][j]))<<"),";
		}
		cout<<endl;
	}
}

VVI floyd_warshall(const VVI& adj_matrix, int n) {
	VVI dist(n);

	for (int i = 1; i < n; ++i) {
		dist[i].resize(n);
		for (int j = 1; j < n; ++j) {
			// if (i == j) dist[i][j] = 0;
			dist[i][j] = adj_matrix[i][j];
		}
	}

	// display_matrix(dist);

	for (int k = 1; k < n; ++k) {
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < n; ++j) {
				// Doing it this way, overflow may occur
				// dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i]
				[k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	display_matrix(dist);

	return dist;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    VVI adj_matrix = {{}, {0,0,5,INT_MAX,9,1}, {0,5,0,2,INT_MAX,INT_MAX},
    {0, INT_MAX,2,0,7,INT_MAX}, {0,9,INT_MAX,7,0,2}, {0,1,INT_MAX, INT_MAX,2,0}};

    floyd_warshall(adj_matrix, adj_matrix.size());

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