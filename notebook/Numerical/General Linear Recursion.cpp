const int maxL = 20; // IF YOU WANT TO CONVOLVE TWO ARRAYS OF LENGTH N AND M CHOOSE LG IN SUCH A WAY THAT 2ˆLG > n + m
const int maxN = 1 << maxL, MOD = 998244353;

#define M_PI acos(-1)

int root[maxL + 2] = {0,998244352,86583718,372528824,
	69212480,87557064,15053575,57475946,15032460,
	4097924,1762757,752127,299814,730033,227806,
	42058,44759,8996,2192,1847,646,42};

int bpow(int a, int b){
	int ans = 1;
	while (b){
		if (b & 1)
			ans = 1LL * ans * a % MOD;
		b >>= 1;
		a = 1LL * a * a % MOD;
	}
	return ans;
}

void ntt(vector<int> &a, bool inv){
	int LG = 0, z = 1, MAX = a.size();
	while(z != MAX) z *= 2, LG ++;
	int ROOT = root[LG];

	for (int mask = 0; mask < MAX; mask++){
		int rev = 0;
		for (int i = 0; i < LG; i++)
			if ((1 << i) & mask)
				rev |= (1 << (LG - 1 - i));
		if (mask < rev)
			swap(a[mask], a[rev]);
	}
	for (int len = 2; len <= MAX; len *= 2){
		int wn = bpow(ROOT, MAX / len);
		if (inv)
			wn = bpow(wn, MOD - 2);
		for (int i = 0; i < MAX; i += len){
			int w = 1;
			for (int j = 0; j < len / 2; j++){
				int l = a[i + j];
				int r = 1LL * w * a[i + j + len / 2] %
					MOD;
				a[i + j] = (l + r);
				a[i + j + len / 2] = l - r + MOD;
				if (a[i + j] >= MOD)
					a[i + j] -= MOD;
				if (a[i + j + len / 2] >= MOD)
					a[i + j + len / 2] -= MOD;
				w = 1LL * w * wn % MOD;
			}
		}
	}
	if (inv){
		int x = bpow(MAX, MOD - 2);
		for (int i = 0; i < MAX; i++)
			a[i] = 1LL * a[i] * x % MOD;
	}
}


int ans[maxN], bb[maxN];

//ans[i] = sum_j=1^i b_j * ans[i - j], ans[0] = 1;
void solve(int l, int r) {
	if(r - l == 1) return ;
	int mid = (l + r)/2;

	solve(l, mid);

	vector <int> a, b;
	for (int i=l; i<r; i++) {
		if(i < mid) a.pb(ans[i]);
		else a.pb(0);

		b.pb(bb[i-l+1]);
	}

	for (int i=l; i<r; i++) {
		a.pb(0);
		b.pb(0);
	}

	ntt(a, false);
	ntt(b, false);

	vector <int> c;
	c.resize(a.size());

	for (int i=0; i<2*r-2*l; i++)
		c[i] = 1LL * a[i] * b[i] % MOD;

	ntt(c, true);
	for (int i=0; i<r-mid; i++) 
		ans[mid + i] += c[mid - l - 1 + i], ans[mid + i] %= MOD;

	solve(mid, r);
}

int main() {
	int n, m; cin >> n >> m;
	for (int i=1; i<=m; i++)
		cin >> bb[i];
	int k = 1;
	while(k < n) k = 2 * k;

	ans[0] = 1;
	solve(0, k);
	for (int i=0; i<n; i++)
		cout << ans[i] << ' ';
	cout << endl;
}
