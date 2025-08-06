typedef vector<ll> vec;
typedef vector<vec> mat;

// A*Bの計算
mat mul(mat &A, mat &B)
{
  mat c(A.size(), vec(B[0].size()));
  for (int i = 0; i < A.size(); i++)
  {
    for (int k = 0; k < B.size(); k++)
    {
      for (int j = 0; j < B[0].size(); j++)
      {
        c[i][j] = (c[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }
}

// A^nの計算
mat pow(mat A, ll n)
{
  mat B(A.size(), vec(A.size()));
  for (int i = 0; i < A.size(); i++)
  {
    B[i][i] = 1;
  }
  while (n > 0)
  {
    if (n & 1)
      B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}
