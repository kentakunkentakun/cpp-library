// 木の直径（辺数）、直径の両端点、木の中心を返す
// 戻り値: {diameter_len, u, v, centers}
// centers は 0-index、要素数は 1 または 2
tuple<ll , ll , ll , vector<ll >> tree_diameter_and_centers(const vector<vector<ll >> &g)
{
  ll  n = (ll )g.size();

  auto bfs_far = [&](ll  s) -> pair<ll , ll >
  {
    vector<ll > dist(n, -1);
    queue<ll > q;
    dist[s] = 0;
    q.push(s);

    ll  far = s;
    while (!q.empty())
    {
      ll  u = q.front();
      q.pop();

      if (dist[u] > dist[far])
        far = u;

      for (ll  v : g[u])
      {
        if (dist[v] == -1)
        {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }

    return {far, dist[far]};
  };

  auto bfs_parent = [&](ll  s) -> pair<vector<ll >, vector<ll >>
  {
    vector<ll > dist(n, -1), par(n, -1);
    queue<ll > q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty())
    {
      ll  u = q.front();
      q.pop();

      for (ll  v : g[u])
      {
        if (dist[v] == -1)
        {
          dist[v] = dist[u] + 1;
          par[v] = u;
          q.push(v);
        }
      }
    }

    return {dist, par};
  };

  if (n == 1)
  {
    return {0, 0, 0, vector<ll >{0}};
  }

  auto [a, _da] = bfs_far(0);
  auto [dist, par] = bfs_parent(a);

  ll  b = a;
  rep(i, n)
  {
    if (dist[i] > dist[b])
      b = i;
  }

  ll  diam = dist[b];

  // a -> b の直径パスを復元
  vector<ll > path;
  ll  cur = b;
  while (cur != -1)
  {
    path.push_back(cur);
    if (cur == a)
      break;
    cur = par[cur];
  }
  reverse(all(path));

  vector<ll > centers;
  ll  len = (ll )path.size(); // 頂点数 = diam + 1

  if (diam % 2 == 0)
  {
    centers.push_back(path[diam / 2]);
  }
  else
  {
    centers.push_back(path[diam / 2]);
    centers.push_back(path[diam / 2 + 1]);
  }

  return {diam, a, b, centers};
}
