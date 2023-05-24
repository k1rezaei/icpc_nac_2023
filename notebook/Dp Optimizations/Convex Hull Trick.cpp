#define F first
#define S second
#define pii pair <int, int>
#define pb psh_back

typedef long long ll;

vector <pair <ll, ll> > cv;

ll barkhord(pair<ll, ll> p1, pair<ll, ll> p2) { //Make sure m1 > m2;
	return (p2.S - p1.S + p1.F - p2.F - 1) / (p1.F - p2.F);
}

ll get(ll t)
{
	int lo = -1, hi = cv.size() - 1;
	while(hi - lo > 1) 
	{
		int mid = (lo + hi)/2;
		if(barkhord(cv[mid + 1], cv[mid]) <= t) lo = mid;
		else hi = mid;
	}
	return t * cv[hi].F + cv[hi].S;
}

//{m, h} in points.
void build(vector <pair <ll, ll> > points) {

	sort(points.begin(), points.end(), cmp); //Make them increasing in m and decreasing in h.

	for (auto X : points)
	{
		while((cv.size() >= 1 and cv.back().F == X.F) or
				(cv.size() >= 2 and barkhord(X, cv.back()) <= barkhord(cv.back(), cv[cv.size() - 2])))
			cv.pop_back();
		cv.pb(X);
	}
	//cv is convex hull.
}
