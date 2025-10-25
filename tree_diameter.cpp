// 木の直径（辺数）と直径の両端点を返す
// 戻り値: {diameter_len, u, v}
// g は 0-index、無向木（連結・N>=1）を仮定
tuple<int, int, int> tree_diameter(const vector<vector<int>> &g)
{
  int n = (int)g.size();
  auto bfs_far = [&](int s) -> pair<int, int>
  {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    int far = s;
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      if (dist[u] > dist[far])
        far = u;
      for (int v : g[u])
        if (dist[v] == -1)
        {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
    }
    return {far, dist[far]};
  };

  // n==1 の特別扱い
  if (n == 1)
    return {0, 0, 0};

  // 任意頂点(0)から一番遠い a、a から一番遠い b
  auto [a, _da] = bfs_far(0);
  auto [b, diam] = bfs_far(a);
  return {diam, a, b};
}
