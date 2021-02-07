//エラトステネスの篩

void Eratosthenes(){
	for(ll i = 2; i < n; i++){
		arr[i] = 1;
	}
	for(int i = 2; i < sqrt(n); i++){
		if(arr[i]){
			for(int j = 0; i * (j + 2) < n; j++){
				arr[i *(j + 2)] = 0;
			}
		}
	}

	for(int i = 2; i < n; i++){
		if(arr[i]){
			//cout << i << endl;
		}
	}
}
//////素数判定
bool is_prime(ll x) { for (ll i = 2; i * i <= x; i++) { if (x % i == 0)return false; } return true; }

//////約数列挙
vector<ll> res(0);
void yakusuu(ll n){
	for(ll i=1;i*i<=n;i++){
	    if(n%i==0){
            res.pb(i);
            if(i!=n/i) res.pb(n/i);
	    }
	}
	return ;
}

/////素因数分解

map<ll,ll> insuu;
void prime_factor(ll n){
    ll k=n;
	for(ll i=2;i*i<=n;i++){
	    while(k%i==0){
	        insuu[i]++;
	        k/=i;
	    }
	}
	if(k!=1) insuu[k]=1;
	return ;
}
