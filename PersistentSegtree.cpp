template <class S, S (*op)(S, S), S (*e)()>
struct PersistentSegTree
{
  struct Node
  {
    S val;
    int left, right;
    Node(S val = e(), int left = -1, int right = -1)
        : val(val), left(left), right(right) {}
  };

  int n;
  vector<Node> nodes;

  PersistentSegTree() {}
  PersistentSegTree(const vector<S> &v)
  {
    int sz = (int)v.size();
    n = 1;
    while (n < sz)
      n <<= 1;
    nodes.reserve(4 * n);
    build(v, 0, n);
  }

  int new_node(const Node &node)
  {
    nodes.push_back(node);
    return (int)nodes.size() - 1;
  }

  int build(const vector<S> &v, int l, int r)
  {
    if (r - l == 1)
    {
      if (l < (int)v.size())
        return new_node(Node(v[l]));
      else
        return new_node(Node(e()));
    }
    int m = (l + r) / 2;
    int lc = build(v, l, m);
    int rc = build(v, m, r);
    return new_node(Node(op(nodes[lc].val, nodes[rc].val), lc, rc));
  }

  int set(int root, int p, S x)
  {
    return set_rec(root, p, x, 0, n);
  }

  int set_rec(int k, int p, S x, int l, int r)
  {
    if (r - l == 1)
    {
      return new_node(Node(x));
    }

    int m = (l + r) / 2;
    int lc = nodes[k].left;
    int rc = nodes[k].right;

    if (p < m)
    {
      lc = set_rec(lc, p, x, l, m);
    }
    else
    {
      rc = set_rec(rc, p, x, m, r);
    }

    return new_node(Node(op(nodes[lc].val, nodes[rc].val), lc, rc));
  }

  S prod(int root, int ql, int qr)
  {
    return prod_rec(root, ql, qr, 0, n);
  }

  S prod_rec(int k, int ql, int qr, int l, int r)
  {
    if (qr <= l || r <= ql)
      return e();
    if (ql <= l && r <= qr)
      return nodes[k].val;

      
    int m = (l + r) / 2;
    S vl = prod_rec(nodes[k].left, ql, qr, l, m);
    S vr = prod_rec(nodes[k].right, ql, qr, m, r);
    return op(vl, vr);
  }

  S get(int root, int p)
  {
    return prod(root, p, p + 1);
  }
};
