//BIT
template< typename T >
struct BIT {
  int N; int max_2beki;
 
  vector< T > data;
  // 初期化 1-indexedでデータを管理する 0で初期化
  BIT(int size){
      N = ++size;
      data.assign(N, 0);
      max_2beki = 1;
      while(max_2beki * 2 <= N) max_2beki *= 2;
  }
 
  // [0,k](閉区間)の総和 閉区間に注意！
  T sum(int k) {
    if(k < 0) return 0; // k<0のとき0を返す
    T ret = 0;
    for(++k; k > 0; k -= k & -k) ret += data[k];
    return (ret);
  }
 
  // [l,r](閉区間)の総和
  inline T sum(int l,int r){
    return sum(r) - sum(l-1);
  }
 
  // 一点取得 更新はできないことに注意
  inline T operator[](int k){
    return sum(k) - sum(k-1);
  }
 
  // data[k] += x;
  void add(int k, T x) {
    for(++k; k < N; k += k & -k) data[k] += x;
  }
 
  // imos法 [l,r]にxを加算
  void imos(int l,int r,T x){
    add(l , x); add(r + 1 , -x);
  }
 
  // lower_bound sum(i)がval以上となる最小のi
  int lower_bound(T w){
    if(w <= 0) return 0;
    int x = 0;
    for(int k = max_2beki; k > 0; k /= 2){
      if(x+k <= N - 1 && data[x + k] < w){
        w -= data[x + k];
        x += k;
      }
    }
    return x;
  }
 
  // upper_bound sum(i)がvalより大きくなる最小のi
  int upper_bound(T w){
    if(w < 0) return 0;
    int x = 0;
    for(int k = max_2beki; k > 0; k /= 2){
      if(x+k <= N - 1 && data[x + k] <= w){
        w -= data[x + k];
        x += k;
      }
    }
    return x;
  }
 
};
