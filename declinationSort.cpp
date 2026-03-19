struct point
{
  ll x, y;
};

long long cross(const point &a, const point &b)
{
  return (long long)a.x * b.y - (long long)a.y * b.x;
}

bool cmp(const point &a, const point &b)
{
  ll ah = (a.y < 0 or (a.y == 0 and a.x < 0));
  ll bh = (b.y < 0 or (b.y == 0 and b.x < 0));
  if (ah != bh)
    return ah < bh;
  return cross(a, b) > 0;
}

void argument_sort(vector<point> &points)
{
  sort(points.begin(), points.end(), cmp);
}
