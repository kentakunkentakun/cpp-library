template <typename T = long long>
struct CC
{
  bool initialized;
  vector<T> xs;
  CC() : initialized(false) {}
  void add(T x) { xs.push_back(x); }
  void init()
  {
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    initialized = true;
  }
  int operator()(T x)
  {
    if (!initialized)
      init();
    return upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
  }
  T operator[](ll i)
  {
    if (!initialized)
      init();
    return xs[i];
  }
  int size()
  {
    if (!initialized)
      init();
    return xs.size();
  }
};

// 自作structでやりたい場合は以下のように < と == を定義する
// struct P
// {
//   long long x, y;
//   bool operator<(const P &o) const
//   {
//     if (x != o.x)
//       return x < o.x;
//     return y < o.y;
//   }
//   bool operator==(const P &o) const
//   {
//     return x == o.x && y == o.y;
//   }
// };

// CC<P> cc;
