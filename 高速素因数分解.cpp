#include <iostream>
#include <vector>
#define ll long long
using namespace std;

// エラトステネスの篩
struct Eratosthenes
{
  // テーブル
  vector<bool> isprime;

  // 整数 i を割り切る最小の素数
  vector<ll> minfactor;

  // メビウス関数値
  vector<int> mobius;

  // コンストラクタで篩を回す
  Eratosthenes(ll N) : isprime(N + 1, true),
                       minfactor(N + 1, -1),
                       mobius(N + 1, 1)
  {
    // 1 は予めふるい落としておく
    isprime[1] = false;
    minfactor[1] = 1;

    // 篩
    for (ll p = 2; p <= N; ++p)
    {
      // すでに合成数であるものはスキップする
      if (!isprime[p])
        continue;

      // p についての情報更新
      minfactor[p] = p;
      mobius[p] = -1;

      // p 以外の p の倍数から素数ラベルを剥奪
      for (ll q = p * 2; q <= N; q += p)
      {
        // q は合成数なのでふるい落とす
        isprime[q] = false;

        // q は p で割り切れる旨を更新
        if (minfactor[q] == -1)
          minfactor[q] = p;
        if ((q / p) % p == 0)
          mobius[q] = 0;
        else
          mobius[q] = -mobius[q];
      }
    }
  }

  // 高速素因数分解
  // pair (素因子, 指数) の vector を返す
  vector<pair<ll, ll>> factorize(ll n)
  {
    vector<pair<ll, ll>> res;
    while (n > 1)
    {
      ll p = minfactor[n];
      ll exp = 0;

      // n で割り切れる限り割る
      while (minfactor[n] == p)
      {
        n /= p;
        ++exp;
      }
      res.emplace_back(p, exp);
    }
    return res;
  }

  // 高速約数列挙
  vector<ll> divisors(ll n)
  {
    vector<ll> res({1});

    // n を素因数分解 (メンバ関数使用)
    auto pf = factorize(n);

    // 約数列挙
    for (auto p : pf)
    {
      ll s = (ll)res.size();
      for (ll i = 0; i < s; ++i)
      {
        ll v = 1;
        for (ll j = 0; j < p.second; ++j)
        {
          v *= p.first;
          res.push_back(res[i] * v);
        }
      }
    }
    return res;
  }
};

int main()
{
  // エラトステネスの篩
  Eratosthenes er(50);

  // 結果表示
  for (ll n = 2; n <= 50; ++n)
  {
    auto pf = er.factorize(n);
    cout << n << ": ";
    for (ll i = 0; i < pf.size(); ++i)
    {
      if (i > 0)
        cout << " * ";
      cout << pf[i].first << "^" << pf[i].second;
    }
    cout << endl;
  }
}
