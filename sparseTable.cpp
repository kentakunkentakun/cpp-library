template <class T, T (*op)(T, T)>
struct SparseTable
{
  int n;
  vector<vector<T>> dat;
  vector<int> lg;

  SparseTable() {}

  SparseTable(const vector<T> &v)
  {
    build(v);
  }

  void build(const vector<T> &v)
  {
    n = (int)v.size();

    lg.assign(n + 1, 0);
    for (int i = 2; i <= n; i++)
    {
      lg[i] = lg[i >> 1] + 1;
    }

    int K = lg[n] + 1;
    dat.assign(K, vector<T>(n));
    dat[0] = v;

    for (int k = 1; k < K; k++)
    {
      int len = 1 << k;
      int half = len >> 1;

      for (int i = 0; i + len <= n; i++)
      {
        dat[k][i] = op(dat[k - 1][i], dat[k - 1][i + half]);
      }
    }
  }

  // [l, r) のクエリ
  T query(int l, int r) const
  {
    assert(0 <= l && l < r && r <= n);

    int k = lg[r - l];

    return op(dat[k][l], dat[k][r - (1 << k)]);
  }
};







// min
int op_min(int a, int b)
{
  return min(a, b);
}
SparseTable<int, op_min> st(v);

int x = st.query(l, r); // [l, r) の min


// max
int op_max(int a, int b)
{
  return max(a, b);
}
SparseTable<int, op_max> st(v);

int x = st.query(l, r); // [l, r) の max


// gcd

long long op_gcd(long long a, long long b)
{
  return std::gcd(a, b);
}
SparseTable<long long, op_gcd> st(v);

long long x = st.query(l, r); // [l, r) の gcd
