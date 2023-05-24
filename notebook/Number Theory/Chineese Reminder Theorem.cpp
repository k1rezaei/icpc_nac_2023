#define lcm LLLCCM

ll GCD(ll a, ll b) { return (b == 0) ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a / GCD(a, b) * b; }
inline ll normalize(ll x, ll mod) { x %= mod; if (x < 0) x += mod; return x; }

struct GCD_type { ll x, y, d; };
GCD_type ex_GCD(ll a, ll b){
	if (b == 0) return {1, 0, a};
	GCD_type pom = ex_GCD(b, a % b);
	return {pom.y, pom.x - a / b * pom.y, pom.d};
}

const int N = 2;
ll r[N], n[N], ans, lcm;
// t: number of equations,
// r: reminder array, n: mod array
// returns {reminder, lcm}

pair <ll, ll> CRT(ll* r, ll *n, int t) {
	for(int i = 0; i < t; i++)
		normalize(r[i], n[i]);
	ans = r[0];
	lcm = n[0];

	for(int i = 1; i < t; i++){
		auto pom = ex_GCD(lcm, n[i]);
		ll x1 = pom.x;
		ll d = pom.d;
		if((r[i] - ans) % d != 0) {
			return {-1, -1}; //No Solution
		}
		ans = normalize(ans + x1 * (r[i] - ans) / d % (n[i] / d) * lcm, lcm * n[i] / d);
		lcm = LCM(lcm, n[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d
	}
	return {ans, lcm};
}

