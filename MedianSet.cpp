#include <bits/stdc++.h>
using namespace std;
#define ll long long
/*
 * MedianSet
 *
 * multiset を2つ使って、動的に中央値を管理するデータ構造。
 *
 * L : 小さい側の半分
 * R : 大きい側の半分
 *
 * 常に以下を満たすように管理する。
 *   1. L の全要素 <= R の全要素
 *   2. |L| == |R| または |L| == |R| + 1
 *
 * そのため、
 *   - 奇数個なら L の最大値が中央値
 *   - 偶数個なら L の最大値と R の最小値が中央2要素
 *
 * 計算量:
 *   add(x)          : O(log N)
 *   erase_one(x)    : O(log N)
 *   median_lower()  : O(1)
 *   median_upper()  : O(1)
 *   median()        : O(1)
 *   size()          : O(1)
 *
 * 重複要素にも対応。
 */
struct MedianSet
{
  multiset<ll> L, R; // L:小さい半分 R:大きい半分
  void rebalance()
  {
    // サイズ: |L| == |R| または |L| == |R+1|
    while (L.size() < R.size())
    {
      auto it = R.begin();
      L.insert(*it);
      R.erase(it);
    }
    while (L.size() > R.size() + 1)
    {
      auto it = prev(L.end());
      R.insert(*it);
      L.erase(it);
    }
  }
  void add(ll x)
  {
    if (L.empty() || x <= *prev(L.end()))
    {
      L.insert(x);
    }
    else
    {
      R.insert(x);
    }
    rebalance();
  }

  void erase_one(ll x)
  {

    auto itL = L.find(x);
    if (itL != L.end())
    {
      L.erase(itL);
    }
    else
    {
      auto itR = R.find(x);
      if (itR != R.end())
        R.erase(itR);
    }
    rebalance();
  }

  ll median_lower()
  {
    assert(!L.empty());
    return *prev(L.end());
  }
  ll median_upper()
  {
    assert(!L.empty());
    if (L.size() > R.size())
      return *prev(L.end());
    return *R.begin();
  }
  int size() const
  {
    return (int)L.size() + (int)R.size();
  }
  long double median()
  {
    assert(size() > 0);

    if (size() % 2 == 1)
    {
      return median_lower();
    }
    else
    {
      return ((long double)median_lower() + (long double)median_upper()) / 2.0;
    }
  }
};
