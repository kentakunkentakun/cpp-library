struct WeightedUnionFind
{
  // p[x] < 0 なら x は根で、-p[x] は集合サイズ
  // そうでなければ p[x] は親
  vector<int> p;
  vector<ll> diff;
  WeightedUnionFind(int n) : p(n, -1), diff(n) {}
  int root(int a)
  {
    if (p[a] < 0)
      return a;
    int par = p[a];
    p[a] = root(par);
    diff[a] += diff[par];
    return p[a];
  }

  bool merge(int a, int b, ll w)
  {
    root(a);
    root(b);
    w = w + diff[a] - diff[b];
    a = root(a);
    b = root(b);
    if (a == b)
      return w == 0;
    if (-p[a] < -p[b])
      swap(a, b), w = -w;
    p[a] += p[b];
    p[b] = a;
    diff[b] = w;
    return true;
  }
};
