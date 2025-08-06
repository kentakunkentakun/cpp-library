struct segtree
{
    int n;
    vector<int> d;
    segtree(int mx)
    {
        n = 1;
        while (n < mx)
            n <<= 1;
        d = vector<int>(n << 1);
    }
    int getmax(int a, int b, int i = 1, int l = 0, int r = -1)
    {
        if (r == -1)
            r = n;
        if (a <= l && r <= b)
            return d[i];
        int res = 0;
        int c = (l + r) >> 1;
        if (a < c)
            res = max(res, getmax(a, b, i << 1, l, c));
        if (c < b)
            res = max(res, getmax(a, b, i << 1 | 1, c, r));
        return res;
    }
    void add(int i, int x)
    {
        i += n;
        while (i)
        {
            d[i] = max(d[i], x);
            i >>= 1;
        }
    }
};

//////////////////////////////////////////////

// Monoid, 1点更新(書き換え)区間取得
// 要素数, 2項演算, 単位元 (, 初期データ)
// todo:1点取得も関数化する？
template <typename T>
struct SegmentTree
{
    typedef function<T(T, T)> F;
    int n; // 要素数
    F f;   // 2項演算
    T e;   // 単位元
    vector<T> dat;
    SegmentTree(int n_, F f, T e) : f(f), e(e)
    {
        init(n_);
        build();
    }
    SegmentTree(int n_, F f, T e, vector<T> &v) : f(f), e(e)
    {
        init(n_);
        build(n_, v);
    }
    void init(int n_)
    {
        n = 1;
        while (n < n_)
            n <<= 1;
        dat.clear();
        dat.resize(n << 1, e);
    }
    void build(int n_, const vector<T> &v)
    { 
        for (int i = 0; i < n_; ++i)
            dat[n + i] = v[i];
        build();
    }
    void build()
    {
        for (int i = n - 1; i >= 1; --i)
        {
            dat[i] = f(dat[i << 1], dat[i << 1 | 1]);
        }
    }
    void update(int k, const T &x)
    {
        dat[k += n] = x;
        while (k >>= 1)
        {
            dat[k] = f(dat[k << 1], dat[k << 1 | 1]);
        }
    }
    T query(int a, int b)
    {
        T l = e, r = e;
        for (a += n, b += n; a < b; a >>= 1, b >>= 1)
        {
            if (a & 1)
                l = f(l, dat[a++]);
            if (b & 1)
                r = f(dat[--b], r);
        }
        return f(l, r);
    }
};

// 区間の総和を求める遅延セグ木
// https : // tsutaj.hatenablog.com/entry/2017/03/30/224339
// struct LazySegmentTree
// {
// private:
//     int n;
//     vector<ll> node, lazy;

// public:
//     LazySegmentTree(vector<ll> v)
//     {
//         int sz = (int)v.size();
//         n = 1;
//         while (n < sz)
//             n *= 2;
//         node.resize(2 * n - 1);
//         lazy.resize(2 * n - 1, 0);

//         for (int i = 0; i < sz; i++)
//             node[i + n - 1] = v[i];
//         for (int i = n - 2; i >= 0; i--)
//             node[i] = node[i * 2 + 1] + node[i * 2 + 2];
//     }
//     // k 番目のノードについて遅延評価を行う
//     void eval(int k, int l, int r)
//     {
//         // 遅延配列が空でない場合、自ノード及び子ノードへの
//         // 値の伝播が起こる
//         if (lazy[k] == 0)
//             return;
//         node[k] += lazy[k];

//         // 最下段かどうかのチェックをしよう
//         // 子ノードは親ノードの 1/2 の範囲であるため、
//         // 伝播させるときは半分にする
//         if (r - l > 1)
//         {
//             lazy[2 * k + 1] += lazy[k] / 2;
//             lazy[2 * k + 2] += lazy[k] / 2;
//         }

//         // 伝播が終わったので、自ノードの遅延配列を空にする
//         lazy[k] = 0;
//     }

//     void add(int a, int b, ll x, int k = 0, int l = 0, int r = -1)
//     {
//         if (r < 0)
//             r = n;

//         // k 番目のノードに対して遅延評価を行う
//         eval(k, l, r);

//         // 範囲外なら何もしない
//         if (b <= l || r <= a)
//             return;

//         // 完全に被覆しているならば、遅延配列に値を入れた後に評価
//         if (a <= l && r <= b)
//         {
//             lazy[k] += (r - l) * x;
//             eval(k, l, r);
//         }

//         // そうでないならば、子ノードの値を再帰的に計算して、
//         // 計算済みの値をもらってくる
//         else
//         {
//             add(a, b, x, 2 * k + 1, l, (l + r) / 2);
//             add(a, b, x, 2 * k + 2, (l + r) / 2, r);
//             node[k] = node[2 * k + 1] + node[2 * k + 2];
//         }
//     }

//     ll getsum(int a, int b, int k = 0, int l = 0, int r = -1)
//     {
//         if (r < 0)
//             r = n;
//         if (b <= l || r <= a)
//             return 0;

//         // 関数が呼び出されたら評価！
//         eval(k, l, r);
//         if (a <= l && r <= b)
//             return node[k];
//         ll vl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
//         ll vr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
//         return vl + vr;
//     }
// };

// 遅延評価セグ木 合計取得
struct LazySegmentTree
{
private:
    int n;           // 葉の数（2 の冪）
    vector<ll> node; // 各区間の現在の総和
    vector<ll> lazy; // 要素あたりの未反映加算量 Δ

    /* 子へ押し下げる */
    void push(int k, int l, int r)
    {
        if (lazy[k] == 0 || r - l == 1)
            return; // 葉 or 仕事なし
        int m = (l + r) >> 1;
        apply(k << 1, lazy[k], m - l);     // 左子
        apply(k << 1 | 1, lazy[k], r - m); // 右子
        lazy[k] = 0;
    }

    /* ノード k (区間長 len) へ Δ を適用 */
    inline void apply(int k, ll delta, int len)
    {
        node[k] += delta * len; // 総和を更新
        lazy[k] += delta;       // 子・孫への先送り分
    }

public:
    /*--- コンストラクタ ---*/
    LazySegmentTree(const vector<ll> &v)
    {
        int sz = (int)v.size();
        n = 1;
        while (n < sz)
            n <<= 1;
        node.assign(2 * n, 0);
        lazy.assign(2 * n, 0);

        for (int i = 0; i < sz; ++i)
            node[i + n] = v[i];
        for (int i = n - 1; i > 0; --i)
            node[i] = node[i << 1] + node[i << 1 | 1];
    }

    /*--- 区間 [a,b) に +x ---*/
    void add(int a, int b, ll x, int k = 1, int l = 0, int r = -1)
    {
        if (r == -1)
            r = n;
        if (b <= l || r <= a)
            return; // 完全に外
        if (a <= l && r <= b)
        { // 完全に内
            apply(k, x, r - l);
            return;
        }
        push(k, l, r); // 部分的なら子へ
        int m = (l + r) >> 1;
        add(a, b, x, k << 1, l, m);
        add(a, b, x, k << 1 | 1, m, r);
        node[k] = node[k << 1] + node[k << 1 | 1];
    }

    /*--- 区間 [a,b) の総和 ---*/
    ll getsum(int a, int b, int k = 1, int l = 0, int r = -1)
    {
        if (r == -1)
            r = n;
        if (b <= l || r <= a)
            return 0; // 完全に外
        if (a <= l && r <= b)
            return node[k]; // 完全に内
        push(k, l, r);      // 子に潜る前に伝播
        int m = (l + r) >> 1;
        return getsum(a, b, k << 1, l, m) +
               getsum(a, b, k << 1 | 1, m, r);
    }
};

// 遅延評価セグ木 max取得
struct LazySegmentTree
{
private:
    int n;           // 葉の数（2 の冪）
    vector<ll> node; // 各区間の現在の総和
    vector<ll> lazy; // 要素あたりの未反映加算量 Δ

    /* 子へ押し下げる */
    void push(int k)
    {
        if (lazy[k] == 0 || k >= n)
            return;                 // 葉 or 仕事なし
        apply(k << 1, lazy[k]);     // 左子
        apply(k << 1 | 1, lazy[k]); // 右子
        lazy[k] = 0;
    }

    /* ノード k (区間長 len) へ Δ を適用 */
    inline void apply(int k, ll delta)
    {
        node[k] = delta; // 総和を更新
        lazy[k] = delta; // 子・孫への先送り分
    }

public:
    /*--- コンストラクタ ---*/
    LazySegmentTree(const vector<ll> &v)
    {
        int sz = (int)v.size();
        n = 1;
        while (n < sz)
            n <<= 1;
        node.assign(2 * n, 0);
        lazy.assign(2 * n, 0);

        for (int i = 0; i < sz; ++i)
            node[i + n] = v[i];
        for (int i = n - 1; i > 0; --i)
            node[i] = node[i << 1] + node[i << 1 | 1];
    }

    /*--- 区間 [a,b) をxに ---*/
    void assign(int a, int b, ll x, int k = 1, int l = 0, int r = -1)
    {
        if (r == -1)
            r = n;
        if (b <= l || r <= a)
            return; // 完全に外
        if (a <= l && r <= b)
        { // 完全に内
            apply(k, x);
            return;
        }
        push(k); // 部分的なら子へ
        int m = (l + r) >> 1;
        assign(a, b, x, k << 1, l, m);
        assign(a, b, x, k << 1 | 1, m, r);
        node[k] = max(node[k << 1], node[k << 1 | 1]);
    }

    /*--- 区間 [a,b) の最大値 ---*/
    ll getmax(int a, int b, int k = 1, int l = 0, int r = -1)
    {
        if (r == -1)
            r = n;
        if (b <= l || r <= a)
            return 0; // 完全に外
        if (a <= l && r <= b)
            return node[k]; // 完全に内
        push(k);            // 子に潜る前に伝播
        int m = (l + r) >> 1;
        return max(getmax(a, b, k << 1, l, m),
                   getmax(a, b, k << 1 | 1, m, r));
    }
};
