//Jarvis March Convex Hull for USACO 5.1 fc

double cross_prod(int pivot, int from, int to, double* pointsx, double* pointsy){
	return (pointsx[from]-pointsx[pivot])*(pointsy[to]-pointsy[pivot]) - (pointsx[to]-pointsx[pivot])*(pointsy[from]-pointsy[pivot]);
}
double dist(int from, int to, double* pointsx, double* pointsy){
	return sqrt((pointsx[from]-pointsx[to])*(pointsx[from]-pointsx[to])+(pointsy[from]-pointsy[to])*(pointsy[from]-pointsy[to]));
}
int jarvis(int leftmost, double* pointsx, double* pointsy, int size, int* hull){
	int pointOnHull = leftmost, endpoint = -1, hullsize;
	for(hullsize = 0; hullsize < size && endpoint != leftmost; hullsize++){
		hull[hullsize] = pointOnHull;
		endpoint = 0;
		for(int j = 1; j < size; j++){
			double cp = cross_prod(pointOnHull, endpoint, j, pointsx, pointsy);
			if(((endpoint == pointOnHull) || cp > 0 || (cp == 0 && dist(pointOnHull, endpoint, pointsx, pointsy) > dist(pointOnHull, j, pointsx, pointsy))) && (j != pointOnHull))
				endpoint = j;
		}
		pointOnHull = endpoint;
	}
	hull[hullsize++] = pointOnHull;
	return hullsize;
}
void solve(){
	freopen("fc.in", "r", stdin);
	freopen("fc.out", "w", stdout);
	int N, leftmost = 0;
	readInt(N);
	int hull[N+5];
	double pointsx[N+5], pointsy[N+5];
	for(int i = 0; i < N; i++){
		readDouble(pointsx[i]);
		readDouble(pointsy[i]);
		if(pointsx[i] < pointsx[leftmost])
			leftmost = i;
	}
	int hullSize = jarvis(leftmost, pointsx, pointsy, N, hull);
	double ans = 0;
	for(int i = 0; i < hullSize; i++){
		ans += dist(leftmost, hull[i], pointsx, pointsy);
		leftmost = hull[i];
	}
	printf("%.2lf\n", ans);
}