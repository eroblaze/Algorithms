// Worst time complexity -> Competitive Programming Book
struct DSU1 {
  vector<int> m_sets;
  vector<int> m_sizes;

  DSU1(int N) {
    m_sets.resize(N + 1);
    m_sizes.resize(N + 1);
    fill(m_sizes.begin(), m_sizes.end(), 1);
    iota(m_sets.begin(), m_sets.end(), 0);
  }
  // O(n)
  int find(int a) const {
    // Returns the representative of a set
    int par = m_sets[a];
    while (par != m_sets[par])
      par = m_sets[par];
    return par;
  }
  // O(n)
  bool same(int a, int b) const { return find(a) == find(b); }
  // O(n) UNION BY RANK OR SIZE
  void merge(int a, int b) {
    int rep_a = find(a);
    int rep_b = find(b);

    if (rep_a == rep_b)
      return;

    if (m_sizes[rep_a] < m_sizes[rep_b])
      swap(rep_a, rep_b);
    m_sets[rep_b] = rep_a;
    m_sizes[rep_a] += m_sizes[rep_b];
    m_sizes[rep_b] = 0;
  }
};

// Has better time complexity than ^ -> From 'Galen Colin'
struct DSU2 {
  int N{0};
  VI m_sets;
  VI m_sizes;
  VVI adj;
  int m_val{0};

  DSU2(int n) : N(n + 1) {
    m_sets.resize(N);
    iota(m_sets.begin(), m_sets.end(), 0);
    m_sizes = VI(N, 1);
    adj.resize(N);
  }
  // O(1)
  int find(int a) {
    assert(a < N);
    return m_sets[a];
  }
  // O(1)
  bool same(int a, int b) { return find(a) == find(b); }
  // (n log(n)) UNION BY RANK OR SIZE
  void merge(int a, int b, int weight) {
    if (same(a, b))
      return;
    int a_reps = m_sets[a];
    int b_reps = m_sets[b];

    // Make sure that a_reps variable contains the set or component with larger
    // members
    if (m_sizes[a_reps] < m_sizes[b_reps])
      swap(a_reps, b_reps);
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
    if (m_sets[node] == new_rep)
      return;
    m_sets[node] = new_rep;

    for (auto v : adj[node]) {
      m_dfs(v, new_rep);
    }
  }
};

// PATH COMPRESSION Best Complexity -> GeekForGeek
// The two techniques - PATH COMPRESSION with the union by RANK/SIZE,
// the time complexity will reach nearly constant time.
// It turns out, that the final amortized time complexity is O(α(n)),
// where α(n) is the inverse Ackermann function, which grows very steadily
// (it does not even exceed for n<10600  approximately).
struct DSU3 {
  vector<int> m_sets;
  vector<int> m_sizes;

  DSU3(int n) {
    m_sets.resize(n);
    iota(m_sets.begin(), m_sets.end(), 0);
    m_sizes = vector<int>(n, 1);
  }

  int find(int a) {
    // Returns the representative of a node using Path Compression
    if (m_sets[a] == a) {
      // if a is a representative
      return a;
    }
    // PATH COMPRESSION
    return m_sets[a] = find(m_sets[a]);

    // ALTERNATIVE APPROACH
    // if (m_sets[a] != a) {
    // 	m_sets[a] = find(m_sets[a]);
    // }

    // return m_sets[a];
  }

  bool same(int a, int b) { return find(a) == find(b); }
  // UNION BY RANK OR SIZE
  void merge(int a, int b) {
    int a_reps = find(a);
    int b_reps = find(b);

    if (a_reps == b_reps)
      return;

    if (m_sizes[a_reps] < m_sizes[b_reps])
      swap(a_reps, b_reps);
    m_sets[b_reps] = a_reps;
    m_sizes[a_reps] += m_sizes[b_reps];
    m_sizes[b_reps] = 0;
  }
};
