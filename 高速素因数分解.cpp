///// 最小素因数（SPF）テーブル & 高速素因数分解 /////

// ビルド後：min_factor[x] = x の最小素因数（x>=2）/ is_prime[x] は素数判定O(1)
vector<ll> primes;
vector<ll> is_prime;
vector<ll> min_factor;

// N までの SPF を構築（O(N log log N)）
void build_min_factor(ll N)
{
  is_prime.assign(N + 1, true);
  min_factor.assign(N + 1, 0);
  if (N >= 0)
    is_prime[0] = false;
  if (N >= 1)
    is_prime[1] = false;
if (N >= 1)
    min_factor[1] = 1;

  for (ll i = 2; i <= N; ++i)
  {
    if (is_prime[i])
    {
      min_factor[i] = i; // 素数の最小素因数は自分
      primes.push_back(i);
      // i*i から刻む（オーバーフロー対策で 1LL）
      for (ll j = 1LL * i * i; j <= N; j += i)
      {
        is_prime[(ll)j] = false;
        if (min_factor[(ll)j] == 0)
          min_factor[(ll)j] = i;
      }
    }
  }
}

// SPF を使った素因数分解： O(log n)
// out[p] に指数が加算される（既存 map にも追記できる）
void prime_factor_spf(ll x, map<ll, ll> &out)
{
  while (x > 1)
  {
    ll p = min_factor[(ll)x];
    if (p == 0)
  { // x がテーブル上限を超える/未構築などの保険
      // フォールバック（素朴）：必要なら削除可
      for (ll d = 2; d * d <= x; ++d)
      {
        while (x % d == 0)
        {
          out[d]++;
          x /= d;
        }
      }
      if (x > 1)
        out[x]++;
      return;
    }
    ll cnt = 0;
    while (x % p == 0)
    {
      x /= p;
      cnt++;
    }
    out[p] += cnt;
  }
}

// ベクタで返す版（{素因数, 指数} の昇順）
vector<pair<ll, ll>> prime_factor_spf_vec(ll x)
{
  vector<pair<ll, ll>> ret;
  while (x > 1)
  {
    ll p = min_factor[(ll)x];
    if (p == 0)
    {
      for (ll d = 2; d * d <= x; ++d)
      {
        if (x % d == 0)
        {
          ll c = 0;
          while (x % d == 0)
          {
            x /= d;
            c++;
          }
          ret.push_back({d, c});
        }
      }
      if (x > 1)
        ret.push_back({x, 1});
      break;
    }
    ll c = 0;
    while (x % p == 0)
    {
      x /= p;
      c++;
    }
    ret.push_back({p, c});
  }
  sort(ret.begin(), ret.end());
  return ret;
}

// 参考：SPFを使った約数列挙（素因数分解→全展開）
vector<ll> divisors_from_spf(ll x)
{
  auto pf = prime_factor_spf_vec(x);
  vector<ll> ds = {1};
  for (auto [p, e] : pf)
  {
    size_t m = ds.size();
    ll cur = 1;
    for (ll k = 1; k <= e; ++k)
    {
      cur *= p;
      for (size_t i = 0; i < m; ++i)
        ds.push_back(ds[i] * cur);
    }
  }
  sort(ds.begin(), ds.end());
  return ds;
}
