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

void top_sort_algo(string node, map<string, vector<string>> adj, stack<string>& top_sort, map<string, bool>& vis) {
    vis[node] = true;

    for (auto v: adj[node]) {
        if (!vis[v]) top_sort_algo(v, adj, top_sort, vis);
    }

    top_sort.push(node);
}

map<string, vector<string>> transpose(map<string, vector<string>> adj) {
    map<string, vector<string>> ans;
    for (auto[k, v]: adj) {
        for (auto j: v) {
            ans[j].push_back(k);
        }
    }
    return ans;
}

unordered_set<string> dfs(string node, map<string, vector<string>> adj, map<string, bool>& vis) {
    vis[node] = true;

    unordered_set<string> m_c;

    for (auto v: adj[node]) {
        if (!vis[v]) {
            unordered_set<string> c = dfs(v, adj, vis);
            // m_c.insert(m_c.begin(), c.begin(), c.end());
            m_c.merge(c);
        }
    }
    m_c.insert(m_c.begin(), node);
    return m_c;
}

string normalize(string str) {
    if (str[0] == '-') return str.substr(1);
    return str;
}

void another_dfs(string node,  map<string, vector<string>>& adj, map<string, bool>& vis, map<string, bool>& variables) {
    vis[node] = true;

    if (!variables.contains(normalize(node))) {
        if (node[0] == '-') {
            variables[node.substr(1)] = false; 
        } else {
            variables[node] = true;
        }
    }

    for (auto v: adj[node]) {
        if (!vis[v]) another_dfs(v, adj, vis, variables);
    }
}


bool kosaraju(map<string, vector<string>> adj, map<string, bool> vis) {
    int N = adj.size();
    stack<string> top_sort;
    stack<string> new_top_sort; // In case there is a solution, this will hold the reversed topological sort

    for (auto [k, v]: adj) {
        if (!vis[k]) top_sort_algo(k, adj, top_sort, vis);
    }

    map<string, vector<string>> transposed_adj = transpose(adj);

    map<string, bool> new_vis;

    for (auto [k,v]: vis) new_vis[k] = false;

    bool is_there_a_solution = true;

    while (!top_sort.empty()) {
        if (!is_there_a_solution) break;

        string node = top_sort.top(); top_sort.pop(); 
        new_top_sort.push(node);
        
        if (new_vis[node]) continue;

        unordered_set<string> scc = dfs(node, transposed_adj, new_vis);
        // check if x1 and -x2 are in the same component
        for (auto it = scc.begin(); it != scc.end(); ++it) {
            string node = *it;
            string to_check;

            if (node[0] == '-') {
                to_check = node.substr(1);
            } else {
                to_check = '-' + node;
            }

            if (scc.contains(to_check)) {
                display_contents(scc);
                is_there_a_solution = false;
                break;
            };
        }
    }

    if (is_there_a_solution) {
        for (auto [k,v]: vis) new_vis[k] = false;
        map<string, bool> variables;

        while (!new_top_sort.empty()) {
            string node = new_top_sort.top(); new_top_sort.pop();

            if (new_vis[node]) continue;
            another_dfs(node, transposed_adj, vis, variables);
        }

        // variables values have been found!
        cout<<"*****SOLUTION*****\n";
        for(auto [k, v]: variables) {
            cout<<k<<" -> "<<(v?"True":"False")<<"\n";
        }
    }

    return is_there_a_solution;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    // First thing is to create the graph through:
    // (a1 v b1) == ¬ a1 -> b1 && ¬ b1 -> a1 
    // a1, b1, c1, d1 = 1, 2, 3, 4 && ¬ a1, ¬ b1, ¬ c1, ¬ d1 = -1, -2, -3, -4
    int N, W, T; cin>>N>>W>>T;

    map<string, vector<string>> adj;
    map<string, bool> vis;

    for (int i = 0; i < N; ++i) {
		string a1, b1; cin>>a1>>b1;
        vis[a1] = false;
        vis[b1] = false;

		if (a1[0] == '-') {
			adj[a1.substr(1)].push_back(b1);
		} else {
			adj['-' + a1].push_back(b1);
		}
		if (b1[0] == '-') {
			adj[b1.substr(1)].push_back(a1);
		} else {
			adj['-' + b1].push_back(a1);
		}
	}

    bool is_there_a_solution = kosaraju(adj, vis);
    db1(is_there_a_solution);

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