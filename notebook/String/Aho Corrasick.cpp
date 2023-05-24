int nxt[N][C];
int f[N], q[N], vcnt;
vector<int> adj[N];
 
int add(string s)
{
	int cur = 0;
	for(auto ch : s)
	{
		ch -= 'a';
		if(!nxt[cur][ch]) nxt[cur][ch] = ++vcnt;
		cur = nxt[cur][ch];
	}
	return cur;
}
 
void aho()
{
	int hi = 0, lo = 0;
	for(int i = 0; i < C; i++) if(nxt[0][i]) q[hi++] = nxt[0][i];
	while(hi != lo)
	{
		int x = q[lo++];
		adj[f[x]].pb(x);
		for(int i = 0; i < C; i++)
		{
			if(nxt[x][i])
			{
				q[hi++] = nxt[x][i];
				f[nxt[x][i]] = nxt[f[x]][i];
			}
			else nxt[x][i] = nxt[f[x]][i];
		}
	}
}
