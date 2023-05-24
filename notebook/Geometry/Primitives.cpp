typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> poly;
#define x real()
#define y imag()

typedef pair<pt, pt> line;
// +, -, * scalar well defined
const ld EPS = 1e-12;
const ld PI = acos(-1);
const int ON = 0, LEFT = 1, RIGHT = -1, BACK = -2, FRONT = 2, IN = 3, OUT = -3;

inline bool Lss(ld a, ld b){ return a - b < -EPS; }
inline bool Grt(ld a, ld b){ return a - b > +EPS; }	
inline bool Leq(ld a, ld b){ return a - b < +EPS; }
inline bool Geq(ld a, ld b){ return a - b > -EPS; }
inline bool Equ(ld a, ld b){ return abs(a-b) < EPS; }

bool byX(const pt &a, const pt &b)
{
	if (Equ(a.x, b.x)) return Lss(a.y, b.y);
	return Lss(a.x, b.x);
}
bool byY(const pt &a, const pt &b){
	if (Equ(a.y, b.y)) return Lss(a.x, b.x);
	return Lss(a.y, b.y);
}
struct cmpXY{ inline bool operator ()(const pt &a, const pt &b)const { return byX(a, b); } };
struct cmpYX{ inline bool operator ()(const pt &a, const pt &b)const { return byY(a, b); } };
bool operator < (const pt &a, const pt &b){ return byX(a, b); }

istream& operator >> (istream& in, pt p){ld valx,valy; in>>valx>>valy; p={valx,valy}; return in;}
ostream& operator << (ostream& out, pt p){out<<p.x<<' '<<p.y; return out;}

ld dot(pt a, pt b){return (conj(a) * b).x;}
ld cross(pt a, pt b){return (conj(a) * b).y;}
ld disSQ(pt a, pt b){return norm(a - b);}
ld dis(pt a, pt b){return abs(a - b);}
ld angleX(pt a, pt b){return arg(b - a);}
ld slope(pt a, pt b){return tan(angleX(a,b));}
//polar(r,theta) -> cartesian
pt rotate(pt a, ld theta){return a * polar((ld)1, theta);}
pt rotatePiv(pt a, ld theta, pt piv){return (a - piv) * polar((ld)1, theta) + piv;}
ld angleABC(pt a, pt b, pt c){return abs(remainder(arg(a-b) - arg(c-b), 2.0 * PI));}
pt proj(pt p, pt v){return v * dot(p,v) / norm(v);}
pt projPtLine(pt a, line l){return proj(a - l.first,l.second-l.first)+l.first;}
ld disPtLine(pt p, line l){return dis(p-l.first, proj(p-l.first,l.second-l.first));}

int relpos(pt a, pt b, pt c) //c to a-b
{
	b = b-a, c= c-a;
	if (Grt(cross(b,c), 0)) return LEFT;
	if (Lss(cross(b,c), 0)) return RIGHT;
	if (Lss(dot(b,c), 0)) return BACK;
	if (Lss(dot(b,c), abs(b))) return FRONT;
	return ON;
}
int relpos(line l, pt b){return relpos(l.first, l.second, b);}

pair<pt,bool> intersection(line a, line b)
{
	ld c1 = cross(b.first - a.first, a.second - a.first);
	ld c2 = cross(b.second - a.first, a.second - a.first);
	if (Equ(c1,c2))
		return {{-1,-1},false};
	return {(c1 * b.second - c2 * b.first) / (c1 - c2), true}; 
}
bool intersect(line a, line b)
{
	pair<pt, bool> ret = intersection(a,b);
	if (!ret.second) return false;
	if (relpos(a, ret.first) == ON and relpos(b, ret.first) == ON)
		return true;
	return false;
}
bool isconvex(poly &pl)
{
	int n = pl.size();
	bool neg = false, pos = false;
	for (int i=0;i<n;i++)
	{
		int rpos = relpos(pl[i], pl[(i+1)%n], pl[(i+2)%n]);
		if (rpos == LEFT) pos = true;
		if (rpos == RIGHT) neg = true;
	}
	return !(neg&pos);
}
int crossingN(poly &pl, pt a)
{
	int n = pl.size();
	pt b = a;
	for (pt p:pl)
		b.real(max(b.x,p.y));
	int cn = 0;
	for (int i=0;i<n;i++)
	{
		pt p = pl[i], q=pl[(i+1)%n];
		if (intersect({a,b},{p,q}) && (relpos({p,q},a)!= RIGHT || relpos({p,q},b) != RIGHT))
			cn ++;
	}
	return cn;
}
int pointInPoly(poly &pl, pt p)
{
	int n = pl.size();
	for (int i=0;i<n;i++)
		if (relpos(pl[i], pl[(i+1)%n], p) == ON)
			return ON;
	return crossingN(pl,p)%2? IN : OUT;
}

poly getHull(poly &pl, bool lower)
{
	sort(pl.begin(), pl.end(), byX);
	poly res;
	int n = res.size();
	for (auto p : pl)
	{
		while (n >= 2 && relpos(res[n-2], res[n-1], p) == (lower? RIGHT : LEFT))
			res.pop_back(), n--;
		res.push_back(p), n++;
	}
	return res;
}

pair<pt, pt> nearestPair(poly &pl)
{
	int n = pl.size();
	sort(pl.begin(), pl.end(), byX);
	multiset<pt, cmpYX> s;
	ld rad = abs(pl[1] - pl[0]);
	pair<pt, pt> res = {pl[0], pl[1]};
	int l = 0, r = 0;
	for (int i=0;i<n;i++)
	{
		while (l<r && Geq(pl[i].x - pl[l].x, rad))
			s.erase(pl[l++]);
		while (r<l && Leq(pl[r].x, pl[i].x))
			s.insert(pl[r++]);
		for (auto it = s.lower_bound(pt(pl[i].x, pl[i].y-rad)); it != s.end(); it++)
		{
			if (Grt(it->y, pl[i].y+rad))
				break;
			ld cur = abs(pl[i] - (*it));
			if (Lss(cur, rad))
				rad = cur, res = {*it, pl[i]};
		}	
	}
	return res;
}

typedef struct circle{
	pt c;
	ld r;
} cir;

//number of common tangent lines
int tangentCnt(cir c1, cir c2)
{
	ld d= abs(c1.c-c2.c);
	if (Grt(d, c1.r+c2.r)) return 4; //outside
	if (Equ(d, c1.r+c2.r)) return 3; //tangent outside
	if (Lss(d, c1.r+c2.r) && Grt(d, abs(c1.r-c2.r))) return 2; //interfere
	if (Equ(d, abs(c1.r-c2.r))) return 1; //tangent inside
	return 0;//inside
}

line intersection(line l, cir c)
{
	ld dis = disPtLine(c.c, l);
	ld d = sqrt(c.r*c.r - dis*dis);
	pt p = projPtLine(c.c, l);
	pt vec = (l.second-l.first)/abs(l.second - l.first);
	return {p + d * vec, p - d * vec};
}

/*
   0 = other is inside this, zero point
   1 = other is tangent inisde of this, one point
   2 = other is intersect with this, two point
   3 = other is tangent outside of this, one point
   4 = other is outside of this, zero point
 */
pair<int, vector<pt> > intersect(cir c, cir other) {
	ld r = c.r;
	pt o = c.c;
	vector<pt> v;
	ld sumr = other.r + r;
	ld rr = r - other.r;
	ld d = dis(o, other.c);
	ld a = (r*r - other.r*other.r + d*d)/(2*d);
	ld h = sqrt(r*r-a*a);
	pt p2 = a * (other.c - o) / d;
	if(Equ(sumr - d, 0)) {
		v.push_back(p2);
		return make_pair(3, v);
	}
	if(Equ(rr - d, 0)) {
		v.push_back(p2);
		return make_pair(1, v);
	}
	if(d <= rr)
		return make_pair(0, v);
	if(d >= sumr)
		return make_pair(4, v);
	pt p3(p2.x + h*(other.c.y - o.y)/d, p2.y - h*(other.c.x - o.x)/d);
	pt p4(p2.x - h*(other.c.y - o.y)/d, p2.y + h*(other.c.x - o.x)/d);
	v.push_back(p3);
	v.push_back(p4);
	return make_pair(2, v);
}
ld arcarea(ld l, ld r, ld R){//circle with radius(r) intersect with circle with radius (R) and distance between centers equal to (d)
	ld cosa = (l*l + r*r - R*R)/(2.0*r*l);
	ld a = acos(cosa);
	return r*r*(a - sin(2*a)/2);
}
