struct Mo
{
  ll n;
  vector<pair<ll, ll>> qs;
  Mo(ll n) : n(n) {}
  void add_query(ll l, ll r) { qs.push_back({l, r}); } // [l, r)

  vector<ll> build()
  {
    ll q = qs.size();
    ll bs = max(1LL, (ll)(n / max(1.0, sqrt((double)q))));
    vector<ll> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](ll a, ll b)
         {
            auto [l1, r1] = qs[a];
            auto [l2, r2] = qs[b];
            ll b1 = l1 / bs, b2 = l2 / bs;
            if (b1 != b2) return b1 < b2;
            return (b1 & 1) ? (r1 > r2) : (r1 < r2); });
    return ord;
  }
};

////////////////////////////////////////////////
template <class T = ll>
struct Mo
{
  ll n;
  vector<pair<ll, ll>> qs; // [l, r)

  Mo(ll n) : n(n) {}

  void add_query(ll l, ll r)
  {
    qs.emplace_back(l, r);
  }

  template <class AddLeft, class AddRight, class DelLeft, class DelRight, class Out>
  void run(AddLeft add_left, AddRight add_right,
           DelLeft del_left, DelRight del_right,
           Out out)
  {
    ll q = (ll)qs.size();
    ll bs = max(1LL, (ll)(n / max(1.0, sqrt((double)q))));

    vector<ll> ord(q);
    iota(ord.begin(), ord.end(), 0);

    sort(ord.begin(), ord.end(), [&](ll a, ll b)
         {
            auto [l1, r1] = qs[a];
            auto [l2, r2] = qs[b];
            ll b1 = l1 / bs, b2 = l2 / bs;
            if (b1 != b2) return b1 < b2;
            if (b1 & 1) return r1 > r2;
            return r1 < r2; });

    ll l = 0, r = 0; // [l, r)

    for (ll idx : ord)
    {
      auto [nl, nr] = qs[idx];

      while (l > nl)
        add_left(--l);
      while (r < nr)
        add_right(r++);
      while (l < nl)
        del_left(l++);
      while (r > nr)
        del_right(--r);

      out(idx);
    }
  }
};
