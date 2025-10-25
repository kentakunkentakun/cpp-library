template <class T>
vector<int> z_algorithm(const std::vector<T> &s)
{
  vector<int> Z(s.size());
  Z[0] = s.size();
  int i = 1, j = 0;
  while (i < s.size())
  {
    while (i + j < s.size() && S[j] == S[i + j])
      j++;
    Z[i] = j;

    if (j == 0)
    {
      i++;
      continue;
    }
    int k = 1;
    while (k < j && k + Z[k] < j)
    {
      Z[i + k] = Z[k];
      k++;
    }
    i += k;
    j -= k;
  }
  return Z;
}

vector<int> z_algorithm(const string &s)
{
  int n = int(s.size());
  vector<int> s2(n);
  for (int i = 0; i < n; i++)
  {
    s2[i] = s[i];
  }
  return z_algorithm(s2);
}
