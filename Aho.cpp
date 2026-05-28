#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (n); ++i)
using mint = modint998244353;
#define ll long long

struct Aho
{
  using MP = unordered_map<char, ll>;
  vector<MP> to;
  vector<ll> cnt, mask, fail;
  Aho() : to(1), cnt(1), mask(1) {}
  ll add(const string &s, ll i)
  {
    ll v = 0;
    for (char c : s)
    {
      if (!to[v].count(c))
      {
        to[v][c] = to.size();
        to.push_back(MP());
        cnt.push_back(0);
        mask.push_back(0);
      }
      v = to[v][c];
    }
    cnt[v]++;
    mask[v] |= 1 << i;
    return v;
  }
  void init()
  {
    fail = vector<ll>(to.size(), -1);
    queue<ll> q;
    q.push(0);
    while (!q.empty())
    {
      ll v = q.front();
      q.pop();
      for (auto [c, u] : to[v])
      {
        fail[u] = (*this)(fail[v], c);
        cnt[u] += cnt[fail[u]];
        mask[u] |= mask[fail[u]];
        q.push(u);
      }
    }
  }
  ll operator()(ll v, char c) const
  {
    while (v != -1)
    {
      auto it = to[v].find(c);
      if (it != to[v].end())
        return it->second;
      v = fail[v];
    }
    return 0;
  }
  ll size() const
  {
    return to.size();
  }
  ll operator[](ll v) const { return mask[v]; }
};

int main()
{
  int n, l;
  cin >> n >> l;
  vector<string> S(n);
  rep(i, n) cin >> S[i];

  Aho aho;
  rep(i, n) aho.add(S[i], i);
  aho.init();
  int m = aho.to.size();
}
