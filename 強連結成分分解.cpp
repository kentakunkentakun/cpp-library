template <typename T = int>
struct SCC
{
  using Edge = T;
  using SGraph = vector<vector<Edge>>;

  // input
  SGraph G, rG;

  // result
  vector<vector<T>> scc; // 各成分に含まれる頂点
  vector<int> cmp;       // 各頂点が属する成分番号（-1初期化）
  SGraph dag;            // SCCを縮約したDAG

  // constructor
  SCC(T n) : G(n), rG(n) {}

  // add edge
  void addedge(T u, T v)
  {
    G[u].push_back(v);
    rG[v].push_back(u);
  }

  // decomposition
  vector<char> seen;
  vector<T> vs, rvs;

  void dfs(T v)
  {
    seen[v] = true;
    for (auto e : G[v])
      if (!seen[e])
        dfs(e);
    vs.push_back(v);
  }

  void rdfs(T v, int k)
  {
    seen[v] = true;
    cmp[v] = k;
    for (auto e : rG[v])
      if (!seen[e])
        rdfs(e, k);
    rvs.push_back(v);
  }

  // reconstruct DAG
  set<pair<int, int>> newEdges;
  void reconstruct()
  {
    int N = (int)G.size();
    int dV = (int)scc.size();
    dag.assign(dV, vector<Edge>());
    newEdges.clear();
    for (int i = 0; i < N; ++i)
    {
      int u = cmp[i];
      for (auto e : G[i])
      {
        int v = cmp[e];
        if (u == v)
          continue;
        if (!newEdges.count({u, v}))
        {
          dag[u].push_back(v);
          newEdges.insert({u, v});
        }
      }
    }
  }

  // main
  void solve()
  {
    int N = (int)G.size();
    seen.assign(N, 0);
    vs.clear();
    for (int v = 0; v < N; ++v)
      if (!seen[v])
        dfs(v);

    int k = 0;
    scc.clear();
    cmp.assign(N, -1);
    seen.assign(N, 0);
    for (int i = N - 1; i >= 0; --i)
    {
      if (!seen[vs[i]])
      {
        rvs.clear();
        rdfs(vs[i], k++);
        scc.push_back(rvs);
      }
    }
    reconstruct();
  }
};
