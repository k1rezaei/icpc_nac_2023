vector<pair<pt, pt>> get_antipodals(poly &p)
{
	int n = p.size();
	sort(p.begin(), p.end(), byX);
	vector <pt> U, L;
	for (int i = 0; i < n; i++){
		while (U.size() > 1 && relpos(U[U.size()-2], U[U.size()-1], p[i]) != LEFT)
			U.pop_back();
		while (L.size() > 1 && relpos(L[L.size()-2], L[L.size()-1], p[i]) != RIGHT)
			L.pop_back();
		U.push_back(p[i]);
		L.push_back(p[i]);
	}
	vector <pair<pt, pt>> res;
	int i = 0, j = L.size()-1;
	while (i+1 < (int)U.size() || j > 0){
		res.push_back({U[i], L[j]});
		if (i+1 == (int)U.size())
			j--;
		else if (j == 0)
			i++;
		else if (cross(L[j]-L[j-1], U[i+1]-U[i]) >= 0) i++;
		else
			j--;
	}
	return res;
}
