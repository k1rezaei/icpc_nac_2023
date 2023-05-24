struct pt{
	ld X,Y,Z;
	pt(ld x=0,ld y=0,ld z=0){X=x; Y=y; Z=z;}

	bool operator==(const pt& rhs) const {
		return (rhs.X==this->X && rhs.Y==this->Y && rhs.Z==this->Z);
	}
	bool operator<(const pt& rhs) const {
		return rhs.X > this->X || (rhs.X == this->X && rhs.Y > this->Y) || (rhs.X==this->X && rhs.Y==this->Y && rhs.Z>this->Z);
	}
};

pt operator -(pt p,pt q){return pt(p.X-q.X,p.Y-q.Y,p.Z-q.Z); }
ld cross2d(pt p,pt q){return p.X*q.Y-p.Y*q.X;}
pt _cross(pt u,pt v){return pt(u.Y*v.Z-u.Z*v.Y,u.Z*v.X-u.X*v.Z,u.X*v.Y-u.Y*v.X); }
pt cross(pt o,pt p,pt q){return _cross(p-o,q-o);}
ld dot(pt p,pt q){return p.X*q.X+p.Y*q.Y+p.Z*q.Z;}
pt shift(pt p) {return pt(p.Y,p.Z,p.X);}
pt norm(pt p)
{
	if(p.Y<p.X || p.Z<p.X) p=shift(p);
	if(p.Y<p.X) p=shift(p);
	return p;
}

const int MAX=1000;

int n;
pt P[MAX];
vector<pt>ans;
queue<pair<int,int> >Q;
set<pair<int,int> >mark;

int main()
{
	cin>>n;
	int mn=0;
	for(int i=0;i<n;i++)
	{
		cin>>P[i].X>>P[i].Y>>P[i].Z;
		if(P[i]<P[mn]) mn=i;
	}
	int nx=(mn==0);
	for(int i=0;i<n;i++)
		if(i!=mn && i!=nx && cross2d(P[nx]-P[mn],P[i]-P[mn])>0)
			nx=i;
	Q.push({mn,nx});
	while(!Q.empty())
	{
		int v=Q.front().first,u=Q.front().second;
		Q.pop();
		if(mark.count({v,u})) continue;
		mark.insert({v,u});
		int p=-1;
		for(int q=0;q<n;q++)
			if(q!=v && q!=u)
				if(p==-1 || dot(cross(P[v],P[u],P[p]),P[q]-P[v])<0)
					p=q;
		ans.push_back(norm(pt(v,u,p)));
		Q.push({p,u});
		Q.push({v,p});
	}
	sort(ans.begin(),ans.end());
	ans.resize(unique(ans.begin(),ans.end())-ans.begin());
	for(int i=0;i<ans.size();i++)
		cout<<ans[i].X<<" "<<ans[i].Y<<" "<<ans[i].Z<<endl;
}
