string s;
int rank[LOG][N], n, lg;
pair<pair<int, int>, int> sec[N];
int sa[N];
int lc[N];
 
int lcp(int a, int b)
{
	int _a = a;
	for(int w = lg - 1; ~w && max(a, b) < n; w--)
		if(max(a, b) + (1 << w) <= n && rank[w][a] == rank[w][b])
			a += 1 << w, b += 1 << w;
	return a - _a;
}
 
int cnt[N];
pair<pii, int> gec[N];
void srt()
{
	memset(cnt, 0, sizeof cnt);
	for(int i = 0; i < n; i++) cnt[sec[i].F.S+1]++;
	for(int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; i++) gec[--cnt[sec[i].F.S+1]] = sec[i];
	memset(cnt, 0, sizeof cnt);
	for(int i = 0; i < n; i++) cnt[gec[i].F.F+1]++;
	for(int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
	for(int i = n - 1; ~i; i--) sec[--cnt[gec[i].F.F+1]] = gec[i];
}
 
void build()
{
	n = s.size();
	{
		int cur = 1; lg = 0;
		while(cur < n)
		{
			lg++;
			cur <<= 1;
		}
		lg++;
	}
 
	for(int i = 0; i < n; i++) rank[0][i] = s[i];
	for(int w = 1; w < lg; w++)
	{
		for(int i = 0; i < n; i++)
			if(i + (1 << w - 1) >= n)
				sec[i] = {{rank[w-1][i], -1}, i};
			else
				sec[i] = {{rank[w-1][i], rank[w-1][i+(1<<w-1)]}, i};
		srt();
		rank[w][sec[0].S] = 0;
		for(int i = 1; i < n; i++)
			if(sec[i].F == sec[i - 1].F)
				rank[w][sec[i].S] = rank[w][sec[i-1].S];
			else 
				rank[w][sec[i].S] = i;
	}
 
	for(int i = 0; i < n; i++)
		sa[rank[lg-1][i]] = i;
	for(int i = 0; i + 1 < n; i++)
		lc[i] = lcp(sa[i], sa[i + 1]);
}
