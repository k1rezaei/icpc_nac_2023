const int N = 810, E = N * N, INF = 1e9;
 
int n, ed = 0, from[E], to[E], cap[E], head[N], nex[E], par[N];
ld dis[N], cost[E];

void add_edge(int u, int v, int c, ld co)
{
	from[ed] = u, to[ed] = v, cap[ed] = c, cost[ed] = co , nex[ed] = head[u], head[u] = ed ++;
	from[ed] = v, to[ed] = u, cap[ed] = 0, cost[ed] = -co, nex[ed] = head[v], head[v] = ed ++;
}

pair<int, ld> spfa(int sink, int source)
{
	for(int i=0; i<N; i++)dis[i] = INF;
	memset(mark, 0, sizeof mark);
	memset(par, -1, sizeof par);

	queue<int> q;
	dis[source] = 0, mark[source] = true;
	q.push(source);

	while(q.size())
	{
		int v = q.front(); q.pop();
		mark[v] = false;

		for(int e = head[v]; e != -1; e = nex[e])
		{
			if(cap[e] && dis[to[e]] > dis[v] + cost[e])
			{
				dis[to[e]] = dis[v] + cost[e];
				par[to[e]] = e;
				if(!mark[to[e]])q.push(to[e]), mark[to[e]] = true;
			}
		}
	}

	int curr = sink;
	if(dis[curr] == INF)return make_pair(0, 0);

	ld res = 0;

	int flow = INF;

	while(curr != source)
	{
		flow = min(flow, cap[par[curr]]);
		curr = from[par[curr]];
	}

	curr = sink;
	while(curr != source)
	{
		res += cost[par[curr]];
		cap[par[curr]] -= flow;
		cap[par[curr] ^ 1] += flow;
		curr = from[par[curr]];
	}

	return make_pair(flow,  res);
}

pair<int, ld> MinCostMaxFlow(int sink, int source)
{
	int flow = 0;
	pair<int, ld> f = {INF, 0};
	ld Cost = 0;

	while(f.F)
	{
		f = spfa(sink, source);
		flow += f.F;
		Cost += f.F * f.S;
	}

	return make_pair(flow, Cost);
}
