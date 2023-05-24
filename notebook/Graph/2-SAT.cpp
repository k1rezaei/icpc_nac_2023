vector<int> adj[2 * N], jda[2 * N], top;
bool mark[2 * N];
int c[2 * N];
void add_clause(int x, int y) {
	adj[x ^ 1].pb(y);
	adj[y ^ 1].pb(x);
	jda[y].pb(x ^ 1);
	jda[x].pb(y ^ 1);
}
void dfs(int u) {
	mark[u] = 1;
	for(auto v : adj[u]) if(!mark[v]) dfs(v);
	top.pb(u);
}

void sfd(int u, int col) {
	c[u] = col;
	for(auto v : jda[u]) if(!c[v]) sfd(v, col);
}

vector<int> two_sat(int n) {
	memset(mark, 0, sizeof mark);
	memset(c, 0, sizeof c);
	top.clear();
	for(int i = 2; i < 2 * n + 2; i++) if(!mark[i]) dfs(i);
	int cnt = 1;
	while(top.size()) {
		int x = top.back(); top.pop_back();
		if(!c[x]) sfd(x, cnt++);
	}
	vector<int> ans, ans1;
	ans1.pb(-1);
	for(int i = 1; i <= n; i++) {
		if(c[2 * i] == c[2 * i + 1]) return ans1;
		if(c[2 * i] > c[2 * i + 1]) ans.pb(i);
	}
	return ans;
}
