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

// Worse time complexity
struct Union_Find {
	vector<int> m_sets;
	vector<int> m_sizes;
	int m_val{0};

	Union_Find(int N) {
		m_sets.resize(N+1);
		m_sizes.resize(N+1);
		fill(m_sizes.begin(), m_sizes.end(), 1);
		iota(m_sets.begin(), m_sets.end(), 0);
	}
	// O(n)
	int find(int a) const {
		// Returns the representative of a set
		int par = m_sets[a];
		while (par != m_sets[par]) par = m_sets[par];
		return par;
	}
	// O(n)
	bool same(int a, int b) const {
		return find(a) == find(b);
	}
	// O(n)
	void merge(int a, int b, int weight) {
		int rep_a = find(a);
		int rep_b = find(b);

		if (m_sizes[rep_a] < m_sizes[rep_b]) swap(rep_a, rep_b);
		m_sets[rep_b] = rep_a;
		m_sizes[rep_a] += m_sizes[rep_b];
		m_sizes[rep_b] = 1;

		m_val += weight;
	}

};

// Has better time complexity - From 'Galen Colin'
struct DSU {
    int N{0};
    VI m_sets;
    VI m_sizes;
    VVI adj;
	int m_val{0};

    DSU(int n):N(n+1) {
        m_sets.resize(N);
        iota(m_sets.begin(), m_sets.end(), 0);
        m_sizes = VI(N, 1);
        adj.resize(N);
    }
    // O(1)
    int find (int a) {
        assert(a < N);
        return m_sets[a];
    }
    // O(1)
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    // (n log(n))
    void merge(int a, int b, int weight) {
        if (same(a, b)) return;
        int a_reps = m_sets[a];
        int b_reps = m_sets[b];

        // Make sure that a_reps variable contains the set or component with larger members
        if (m_sizes[a_reps] < m_sizes[b_reps]) swap(a_reps, b_reps);
        // I can also directly add
        adj[a].push_back(b);
        adj[b].push_back(a);

        // Change all nodes in b_reps set to point to a_rep
        m_dfs(b_reps, a_reps);
        m_sizes[a] += m_sizes[b];
        m_sizes[b] = 0;

		m_val += weight;
    }

private:
    void m_dfs(int node, int new_rep) {
        if (m_sets[node] == new_rep) return;
        m_sets[node] = new_rep;

        for (auto v: adj[node]) {
            m_dfs(v, new_rep);
        }
    }

};


void kruskal(priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, Compare_sort> edge_list, int N) {

	// Union_Find obj(N);
	DSU obj(N);
	
	while (!edge_list.empty()) {
		tuple<int, int, int> edge = edge_list.top(); edge_list.pop();
		int a,b,c;
		tie(a,b,c) = edge;

		if (!obj.same(a, b)) obj.merge(a,b,c);
	}

	int minimum_spanning_tree = obj.m_val;
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