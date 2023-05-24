const int maxL = 61;

struct Base{
	ll a[maxL] = {};
	ll eliminate(ll x){
		for(int i=maxL-1; i>=0; --i) if(x >> i & 1) x ^= a[i];
		return x;
	}
	void add(ll x){
		x = eliminate(x);
		if(x == 0) return ;
		for(int i=maxL-1; i>=0; --i) if(x >> i & 1) {
			a[i] = x;
			return ;
		}
	}
	int size(){
		int cnt = 0;
		for(int i=0; i<maxL; ++i) if(a[i]) ++cnt;
		return cnt;
	}
	ll get_mx() {
		ll x = 0;
		for (int i=maxL-1; i>=0; i--) {
			if(x & (1LL << i)) continue ;
			else x ^= a[i];
		}
		return x;
	}
};

