//LCA
template <typename T = ll>
struct LowestCommonAncestor {
  struct Edge {
    ll to;
    T cost;
    Edge(ll to, T cost) : to(to), cost(cost) {}
  };
  ll n;
  ll l;
  vector<vector<Edge>> es;
  vector<vector<ll>> par;
  vector<ll> dep;
  vector<T> dists;
  LowestCommonAncestor(ll n) : n(n), es(n), dep(n), dists(n + 1) {
    l = 0;
    while ((1 << l) < n) l++;
    par.assign(n + 1, vector<ll>(l, n));
  }
  void add_edge(ll v, ll u, T c = 0) {
    es[v].emplace_back(u, c);
    es[u].emplace_back(v, c);
  }
  void dfs(ll v = 0, ll d = 0, T c = 0, ll p = -1) {
    if (p != -1) par[v][0] = p;
    dep[v] = d;
    dists[v] = c;
    for (auto e : es[v]) {
      if (e.to == p) continue;
      dfs(e.to, d + 1, c + e.cost, v);
    }
  }
  void build() {
    dfs();
    for (ll i = 0; i < l - 1; i++) {
      for (ll v = 0; v < n; v++) {
        par[v][i + 1] = par[par[v][i]][i];
      }
    }
  }
  ll lca(ll v, ll u) {
    if (dep[v] < dep[u]) swap(v, u);
    ll gap = dep[v] - dep[u];
    for (ll i = l - 1; i >= 0; i--) {
      if ((1 << i) & gap) v = par[v][i];
    }
    if (v == u) return v;
    for (ll i = l - 1; i >= 0; i--) {
      ll pv = par[v][i];
      ll pu = par[u][i];
      if (pv != pu) v = pv, u = pu;
    }
    return par[v][0];
  }
  ll length(ll v, ll u) {
    ll a = lca(v, u);
    return dep[v] + dep[u] - dep[a] * 2;
  }
  T dist(ll v, ll u) {
    ll a = lca(v, u);
    return dists[v] + dists[u] - dists[a] * 2;
  }
};
