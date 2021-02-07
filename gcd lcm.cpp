// gcd lcm
ll gcd(ll a, ll b) { return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b) { return a/gcd(a,b)*b;}
 
 
// gcd lcm
ll gcd(ll a, ll b) {
	if (a < b)swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}
 
ll lcm(ll a, ll b) {
	ll g = gcd(a, b);
	return a / g * b;
}