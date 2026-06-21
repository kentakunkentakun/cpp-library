// subset zeta:
// f[S] = Σ 元の f[T]  where T ⊆ S
template <class T>
vector<T> subset_zeta(int n, vector<T> f)
{
  for (int i = 0; i < n; i++)
  {
    for (int S = 0; S < (1 << n); S++)
    {
      if ((S >> i) & 1)
      {
        f[S] += f[S ^ (1 << i)];
      }
    }
  }
  return f;
}

// subset mobius:
// subset_zeta の逆変換
template <class T>
vector<T> subset_mobius(int n, vector<T> f)
{
  for (int i = 0; i < n; i++)
  {
    for (int S = 0; S < (1 << n); S++)
    {
      if ((S >> i) & 1)
      {
        f[S] -= f[S ^ (1 << i)];
      }
    }
  }
  return f;
}

// superset zeta:
// f[S] = Σ 元の f[T]  where S ⊆ T
template <class T>
vector<T> superset_zeta(int n, vector<T> f)
{
  for (int i = 0; i < n; i++)
  {
    for (int S = 0; S < (1 << n); S++)
    {
      if (((S >> i) & 1) == 0)
      {
        f[S] += f[S | (1 << i)];
      }
    }
  }
  return f;
}

// superset mobius:
// superset_zeta の逆変換
template <class T>
vector<T> superset_mobius(int n, vector<T> f)
{
  for (int i = 0; i < n; i++)
  {
    for (int S = 0; S < (1 << n); S++)
    {
      if (((S >> i) & 1) == 0)
      {
        f[S] -= f[S | (1 << i)];
      }
    }
  }
  return f;
}
