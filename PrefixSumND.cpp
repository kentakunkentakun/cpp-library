template <class T>
struct PrefixSumND
{
  int dim;
  vector<ll> n;
  vector<ll> len; // sz から変更
  vector<ll> stride;
  vector<T> s;
  bool built = false;

  PrefixSumND(const vector<ll> &dims)
      : dim((int)dims.size()), n(dims), len(dim), stride(dim)
  {
    ll total = 1;

    for (int i = dim - 1; i >= 0; i--)
    {
      assert(n[i] >= 0);
      len[i] = n[i] + 1;
      stride[i] = total;
      total *= len[i];
    }

    s.assign((size_t)total, T{});
  }

  ll id(const vector<ll> &p) const
  {
    assert((int)p.size() == dim);

    ll res = 0;
    for (int i = 0; i < dim; i++)
    {
      assert(0 <= p[i] && p[i] <= n[i]);
      res += p[i] * stride[i];
    }
    return res;
  }

  void add(const vector<ll> &pos, T val)
  {
    assert(!built);
    assert((int)pos.size() == dim);

    vector<ll> p(dim);
    for (int i = 0; i < dim; i++)
    {
      assert(0 <= pos[i] && pos[i] < n[i]);
      p[i] = pos[i] + 1;
    }

    s[id(p)] += val;
  }

  void build()
  {
    assert(!built);

    ll total = (ll)s.size();

    for (int axis = 0; axis < dim; axis++)
    {
      ll step = stride[axis];
      ll axis_len = len[axis];
      ll period = step * axis_len;

      for (ll base = 0; base < total; base += period)
      {
        for (ll off = 0; off < step; off++)
        {
          for (ll k = 1; k < axis_len; k++)
          {
            ll cur = base + off + k * step;
            s[cur] += s[cur - step];
          }
        }
      }
    }

    built = true;
  }

  T prefix(const vector<ll> &upper) const
  {
    assert(built);
    assert((int)upper.size() == dim);
    return s[id(upper)];
  }

  T sum(const vector<ll> &l, const vector<ll> &r) const
  {
    assert(built);
    assert((int)l.size() == dim);
    assert((int)r.size() == dim);

    for (int i = 0; i < dim; i++)
    {
      assert(0 <= l[i] && l[i] <= r[i] && r[i] <= n[i]);
    }

    T res = T{};
    vector<ll> p(dim);

    for (ll mask = 0; mask < (1LL << dim); mask++)
    {
      int bits = 0;

      for (int i = 0; i < dim; i++)
      {
        if ((mask >> i) & 1)
        {
          p[i] = l[i];
          bits++;
        }
        else
        {
          p[i] = r[i];
        }
      }

      if (bits & 1)
        res -= s[id(p)];
      else
        res += s[id(p)];
    }

    return res;
  }
};

// sample
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N0, N1, N2, N3, N4, N5;
  cin >> N0 >> N1 >> N2 >> N3 >> N4 >> N5;

  PrefixSumND<ll> ps({N0, N1, N2, N3, N4, N5});

  // A[a][b][c][d][e][f] += x
  ps.add({a, b, c, d, e, f}, x);

  // 全部入れたあと build
  ps.build();

  // 全部の添字が現在位置より strict に小さい ものの和は：
  ll ans = ps.prefix({i0, i1, i2, i3, i4, i5});
}
