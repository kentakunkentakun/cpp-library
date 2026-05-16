#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
};
