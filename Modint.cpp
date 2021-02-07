template<int64 mod>
struct ModInt{
  int64 x;
  constexpr ModInt(int64 y = 0):x((y%mod+mod)%mod){}
  constexpr ModInt& operator+=(const ModInt& a){
    if((x += a.x) >= mod) x -= mod;
    return *this;
  }
  constexpr ModInt& operator-=(const ModInt& a){
    if((x -= a.x) < 0)x += mod;
    return *this;
  }
  constexpr ModInt& operator*=(const ModInt& a){
    x = x * a.x % mod;
    return *this;
  }
  constexpr ModInt& operator/=(const ModInt& a){
    *this *= a.inv();
    return *this;
  }
  constexpr ModInt operator-() const {
    return ModInt(-x);
  }
  constexpr ModInt operator+(const ModInt& a) const {
    return ModInt(*this) += a;
  }
  constexpr ModInt operator-(const ModInt& a) const {
    return ModInt(*this) -= a;
  }
  constexpr ModInt operator*(const ModInt& a) const {
    return ModInt(*this) *= a;
  }
  constexpr ModInt operator/(const ModInt& a) const {
    return ModInt(*this) /= a;
  }
  constexpr ModInt operator++(){
    *this += ModInt(1);
    return *this;
  }
  constexpr ModInt operator++(int){
    ModInt old = *this;
    ++*this;
    return old;
  }
  constexpr ModInt operator--(){
    *this -= ModInt(1);
    return *this;
  }
  constexpr ModInt operator--(int){
    ModInt old = *this;
    --*this;
    return old;
  }
  constexpr bool operator==(const ModInt& a) const {
    return x == a.x;
  }
  constexpr bool operator!=(const ModInt& a) const {
    return x != a.x;
  }
  constexpr ModInt pow(int64 r) const {
    if(!r)return 1;
    ModInt res = pow(r>>1);
    res *= res;
    if(r & 1) res *= *this;
    return res;
  }
  constexpr ModInt inv() const {
    return pow(mod-2);
  }
  friend istream& operator>>(istream& is, ModInt& a){
    int64 t;
    is >> t;
    a = ModInt(t);
    return is;
  }
  friend ostream& operator<<(ostream& os, const ModInt& a){
    return os << a.x;
  }
};
using mint = ModInt<MOD>;
