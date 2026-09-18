/*
 * IntervalSet
 *
 * 整数の半開区間 [l, r) の集合を管理する。
 * 重複または隣接する区間は自動的にマージする。
 *
 * 例:
 *   [1,3) + [3,5) -> [1,5)
 *   [1,3) + [4,6) -> [1,3), [4,6)
 *
 * 常に、保持されている区間同士は
 * 「重複せず、隣接もしない」状態になる。
 *
 * insert(l, r)
 *   [l,r) を追加する。
 *   重複・隣接区間は自動でマージする。
 *
 * insert(x)
 *   整数 x を表す区間 [x,x+1) を追加する。
 *
 * contains(x)
 *   x がいずれかの区間に含まれるか。
 *
 * intersects(l, r)
 *   [l,r) が、いずれかの区間と交差するか。
 *   端点が接するだけなら交差とはみなさない。
 *
 * next_free(x)
 *   x 以上で、どの区間にも含まれない最小の整数を返す。
 *
 * size()
 *   現在保持している区間数。
 */
struct IntervalSet
{
  set<pair<ll, ll>> st;

  // 半開区間 [l, r) を追加
  void insert(ll l, ll r)
  {
    if (l >= r)
      return;

    auto it = st.lower_bound({l, -INF});

    // 左隣と重複・隣接している可能性
    if (it != st.begin())
    {
      auto pre = prev(it);

      // [a,b) と [l,r) が重複または隣接
      // b >= l ならマージ可能
      if (pre->second >= l)
        it = pre;
    }

    // 重複・隣接する区間をすべて吸収
    while (it != st.end() && it->first <= r)
    {
      l = min(l, it->first);
      r = max(r, it->second);

      it = st.erase(it);
    }

    st.insert({l, r});
  }

  // 整数 x を追加
  // x は半開区間 [x, x+1) として表現
  void insert(ll x)
  {
    insert(x, x + 1);
  }

  // x がいずれかの区間に含まれるか
  bool contains(ll x) const
  {
    auto it = st.upper_bound({x, INF});

    if (it == st.begin())
      return false;

    --it;

    return it->first <= x && x < it->second;
  }

  // 半開区間 [l,r) が、いずれかの区間と交差するか
  bool intersects(ll l, ll r) const
  {
    if (l >= r)
      return false;

    auto it = st.lower_bound({l, -INF});

    // l 以上から始まる最初の区間
    // [a,b) と [l,r) が交差する条件は a < r
    if (it != st.end() && it->first < r)
      return true;

    // l より左から始まる区間が l を越えていれば交差
    if (it != st.begin())
    {
      auto pre = prev(it);

      if (pre->second > l)
        return true;
    }

    return false;
  }

  // x 以上で最初の未使用整数を返す
  ll next_free(ll x) const
  {
    auto it = st.upper_bound({x, INF});

    if (it != st.begin())
    {
      auto pre = prev(it);

      if (pre->first <= x && x < pre->second)
        return pre->second;
    }

    return x;
  }

  // 管理中の区間数
  ll size() const
  {
    return st.size();
  }

  bool empty() const
  {
    return st.empty();
  }
};
