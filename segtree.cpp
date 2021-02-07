struct segtree {
  int n;
  vector<int> d;
  segtree(int mx) {
    n = 1;
    while (n < mx) n <<= 1;
    d = vector<int>(n<<1);
  }
  int getmax(int a, int b, int i=1, int l=0, int r=-1) {
    if (r == -1) r = n;
    if (a <= l && r <= b) return d[i];
    int res = 0;
    int c = (l+r)>>1;
    if (a < c) res = max(res, getmax(a, b, i<<1, l, c));
    if (c < b) res = max(res, getmax(a, b, i<<1|1, c, r));
    return res;
  }
  void add(int i, int x) {
    i += n;
    while (i) {
      d[i] = max(d[i], x);
      i >>= 1;
    }
  }
};

//////////////////////////////////////////////

//Monoid, 1点更新(書き換え)区間取得
//要素数, 2項演算, 単位元 (, 初期データ)
//todo:1点取得も関数化する？
template<typename T>
struct SegmentTree{
    typedef function<T(T,T)> F;
    int n;    //要素数
    F f;    //2項演算
    T e;    //単位元
    vector<T> dat;
    SegmentTree(int n_,F f,T e):f(f),e(e){
        init(n_);
        build();
    }
    SegmentTree(int n_,F f,T e,vector<T>& v):f(f),e(e){
        init(n_);
        build(n_,v);
    }
    void init(int n_){
        n=1;
        while(n<n_)n<<=1;
        dat.clear();
        dat.resize(n<<1, e);
    }
    void build(int n_,const vector<T>& v){
        for(int i=0;i<n_;++i)dat[n+i]=v[i];
        build();
    }
    void build(){
        for(int i=n-1;i>=1;--i){
            dat[i] = f(dat[i<<1],dat[i<<1|1]);
        }
    }
    void update(int k,const T& x){
        dat[k+=n]=x;
        while(k>>=1){
            dat[k] = f(dat[k<<1],dat[k<<1|1]);
        }
    }
    int query(int a,int b){
        T l=e,r=e;
        for(a+=n,b+=n;a<b;a>>=1,b>>=1){
            if(a&1)l=f(l,dat[a++]);
            if(b&1)r=f(dat[--b],r);
        }
        return f(l,r);
    }
};
