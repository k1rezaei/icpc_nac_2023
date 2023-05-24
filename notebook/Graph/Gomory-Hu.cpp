bool mark[N];
int p[N], w[N];
void gfs(int u) {
	mark[u] = 1;
	for(int e = head[u]; e != -1; e = prv[e])
		if(!mark[to[e]] && cap[e])
			gfs(to[e]);
}
//edges is one-directed. Order: O(n * flow)
vector<pair<int, pii>> gomory_hu(int n, vector<pair<int, pii>> edges) {
	for(int i = 1; i <= n; i++) p[i] = 1;
	memset(w, 0, sizeof w);
	p[1] = 0;
	for(int i = 2; i <= n; i++) {
		memset(head, -1, sizeof head);
		ec = 0;
		for(auto u : edges) add_edge(u.S.F, u.S.S, u.F);
		w[i] = dinic(i, p[i]);
		memset(mark, 0, sizeof mark);
		gfs(i);
		for(int j = i + 1; j <= n; j++)
			if(mark[j] && p[j] == p[i])
				p[j] = i;
		if(p[p[i]] && mark[p[p[i]]]) {
			int pi = p[i];
			swap(w[i], w[pi]);
			p[i] = p[pi];
			p[pi] = i;
		}
	}
	vector<pair<int, pii>> tree;
	for(int i = 1; i <= n; i++) if(p[i]) tree.pb({w[i], {i, p[i]}});
	return tree;
}
