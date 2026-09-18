/*
 * Coordinate Compression
 *
 * 値を昇順に並べて重複を除き、
 * 元の値 <-> 圧縮後 index を対応付ける。
 *
 * 使用例:
 *   CC<ll> cc;
 *   cc.add(100);
 *   cc.add(50);
 *   cc.add(100);
 *
 *   cc.lb(50);   // 0
 *   cc.lb(100);  // 1
 *   cc[0];       // 50
 *   cc[1];       // 100
 *
 * メソッド:
 *   add(x)
 *     圧縮対象の値 x を追加する。
 *
 *   init()
 *     追加された値をソートし、重複を削除する。
 *     通常は明示的に呼ばなくてよい。
 *
 *   lb(x)
 *     x 以上の最小要素の index を返す。
 *     x が登録済みなら、x の圧縮後 index になる。
 *     O(log N)
 *
 *   operator()(x)
 *     x 以下の最大要素の index を返す。
 *     該当要素が存在しない場合は -1。
 *     O(log N)
 *
 *   operator[](i)
 *     圧縮後 index i に対応する元の値を返す。
 *     O(1)
 *
 *   contains(x)
 *     x が登録されているか判定する。
 *     O(log N)
 *
 *   size()
 *     圧縮後の要素数を返す。
 *     O(1)
 */
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
