template <typename T = ll>
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

  // lower_bound
  ll lb(T x)
  {
    if (!initialized)
      init();
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  }

  // x 以下の最大の要素のindex
  ll operator()(T x)
  {
    if (!initialized)
      init();
    return upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
  }

  // 圧縮後index i に対応する元の値を取得
  T operator[](ll i)
  {
    if (!initialized)
      init();
    return xs[i];
  }

  // x を登録済みかどうか
  bool contains(T x)
  {
    if (!initialized)
      init();
    int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    return i < (int)xs.size() && xs[i] == x;
  }

  ll size()
  {
    if (!initialized)
      init();
    return xs.size();
  }
};
