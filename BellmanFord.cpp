struct BellmanFordMax
{
  BellmanFordMax() {}
  BellmanFordMax(ll n) { init(n); }
  vector<vector<pair<ll, ll>>> E;
  ll N;
  void init(ll n)
  {
    N = n;
    E.resize(0);
    E.clear();
    E.resize(n);
  }
  void add(ll a, ll b, ll c) { E[a].push_back({b, c}); }
  vector<ll> solve(ll s)
  {
    vector<ll> res(N, -INF);
    res[s] = 0;

    rep(i, N - 1)
    {
      rep(cu, N) if (-INF < res[cu]) for (auto p : E[cu])
      {
        chmax(res[p.first], res[cu] + p.second);
      }
    }

    vector<bool> pos(N);
    rep(i, N)
    {
      rep(cu, N) if (-INF < res[cu]) for (auto p : E[cu])
      {
        if (chmax(res[p.first], res[cu] + p.second))
        {
          pos[p.first] = true;
        }
        if (pos[cu])
          pos[p.first] = true;
      }
    }

    rep(cu, N) if (pos[cu]) res[cu] = INF;

    return res;
  }
};

struct BellmanFordMin
{
  BellmanFordMin() {}
  BellmanFordMin(ll n) { init(n); }
  vector<vector<pair<ll, ll>>> E;
  ll N;
  void init(ll n)
  {
    N = n;
    E.resize(0);
    E.clear();
    E.resize(n);
  }
  void add(ll a, ll b, ll c) { E[a].push_back({b, c}); }
  vector<ll> solve(ll s)
  {
    vector<ll> res(N, INF);
    res[s] = 0;

    rep(i, N - 1)
    {
      rep(cu, N) if (INF > res[cu]) for (auto p : E[cu])
      {
        chmin(res[p.first], res[cu] + p.second);
      }
    }

    vector<bool> pos(N);
    rep(i, N)
    {
      rep(cu, N) if (INF > res[cu]) for (auto p : E[cu])
      {
        if (chmin(res[p.first], res[cu] + p.second))
        {
          pos[p.first] = true;
        }
        if (pos[cu])
          pos[p.first] = true;
      }
    }

    rep(cu, N) if (pos[cu]) res[cu] = -INF;

    return res;
  }
};
