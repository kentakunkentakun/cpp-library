struct NextFree
{
  unordered_map<long long, long long> p;

  //x以上でuseされていない最も小さい値を求める
  long long find(long long x)
  {
    auto it = p.find(x);
    if (it == p.end())
      return x;
    return it->second = find(it->second);
  }

  // xをuseする
  void use(long long x)
  {
    p[x] = find(x + 1);
  }
};
