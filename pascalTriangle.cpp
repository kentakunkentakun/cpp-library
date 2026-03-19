vvll s(5001, vll(5001));
s[1][1] = 1;
rep(i, 5001)
{
  s[i][0] = 1;
  s[i][i] = 1;
}
for (int i = 2; i <= 5000; i++)
{
  for (int j = 1; j < i; j++)
  {
    s[i][j] = (s[i - 1][j - 1] + s[i - 1][j]);
  }
}
