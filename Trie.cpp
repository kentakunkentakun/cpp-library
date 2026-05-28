struct Trie
{
  struct Node
  {
    map<char, ll> to;
    ll cnt;
    Node() : cnt(0) {}
  };
  vector<Node> d;
  Trie() : d(1) {};

  void add(const string &s)
  {
    ll v = 0;
    for (char c : s)
    {
      if (!d[v].to.count(c))
      {
        d[v].to[c] = d.size();
        d.push_back(Node());
      }
      v = d[v].to[c];
    }
    d[v].cnt++;
  }

  ll ans;
  ll dfs(ll v)
  {
    ll res = d[v].cnt;
    for (auto [c, next] : d[v].to)
    {
      res += dfs(next);
    }
    if (v)
      ans += res * (res - 1) / 2;
    return res;
  }
  ll solve()
  {
    ans = 0;
    dfs(0);
    return ans;
  }
};
