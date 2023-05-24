const int N = 505, MOD = 1e9 + 7;
typedef vector <ll> vec;

ll pw(ll a, ll b) {
	if(!b)
		return 1;
	ll x = pw(a, b/2);
	return x * x % MOD * (b % 2 ? a : 1) % MOD;
}
ll inv(ll x) { return pw(x, MOD - 2); }

//matrix * x = ans
vec solve(vector<vec> matrix, vec ans) {
	int n = matrix.size(), m = matrix[0].size();
	for (int i=0; i<n; i++)
		matrix[i].pb(ans[i]);

	vector <int> ptr;
	ptr.resize(n);

	int i = 0, j =0;
	while(i < n and j < m) {
		int ind = -1;
		for(int row = i; row < n; row++)
			if(matrix[row][j])
				ind = row;
		if(ind == -1) {
			j++;
			continue ;
		}

		matrix[i].swap(matrix[ind]);
		ll inverse = inv(matrix[i][j]);
		for(int row = i + 1; row < n; row++) {
			ll z = matrix[row][j] * inverse % MOD;
			for(int k = 0; k <= m;  k++)
				matrix[row][k] = (matrix[row][k] % MOD - matrix[i][k]*z % MOD + MOD) % MOD;
		}

		ptr[i] = j;
		i ++;
		j ++;
	}

	vector <ll> sol;

	if(i != n) {
		for (int row=i; row<n; row++)
			if(matrix[row][m] != 0) 
				return sol; //without answer;
	}
	sol.resize(m);
	for (int j=0; j<m; j++)
		sol[j] = 0;

	for (int row=i-1; row>=0; row--){
		int j = ptr[row];
		sol[j] = matrix[row][m] * inv(matrix[row][j]) % MOD;
		for (int c=row-1; c>=0; c--)
			matrix[c][m] += (MOD - sol[j] * matrix[c][j] % MOD), matrix[c][m] %= MOD;
	}
	return sol;
}

int main() {
	int n, m; cin >> n >> m;
	vector <vec> A;
	for (int i=0; i<n; i++)
	{
		vec B;
		for (int j=0; j<m; j++)
		{
			ll x; cin >> x;
			B.push_back(x);
		}
		A.push_back(B);
	}

	vec ans;
	for (int i=0; i<n; i++)
	{
		ll y; cin >> y;
		ans.pb(y);
	}

	vec sol = solve(A, ans);
	for (auto X : sol)
		cout << X << ' ';
	cout << endl;
}
