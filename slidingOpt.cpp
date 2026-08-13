template <class T, bool (*comp)(T, T)>
struct SlidingOpt
{
  deque<pair<int, T>> dq;

  void push(int i, T x)
  {
    while (!dq.empty() && !comp(dq.back().second, x))
    {
      dq.pop_back();
    }
    dq.emplace_back(i, x);
  }

  void pop_less_than(int l)
  {
    while (!dq.empty() && dq.front().first < l)
    {
      dq.pop_front();
    }
  }

  T get() const
  {
    return dq.front().second;
  }

  int arg() const
  {
    return dq.front().first;
  }

  bool empty() const
  {
    return dq.empty();
  }
};

// スライド最小値
bool comp_min(ll a, ll b)
{
  return a < b;
}
SlidingOpt<double, comp_min> sm;

// スライド最大値
bool comp_max(ll a, ll b)
{
  return a > b;
}
SlidingOpt<double, comp_max> sm;
