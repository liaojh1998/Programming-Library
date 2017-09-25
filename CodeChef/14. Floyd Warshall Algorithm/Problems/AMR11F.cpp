#include <bits/stdc++.h>
using namespace std;

template<typename T> class FloydWarshall{
#define INF (1000000000)
private:
	size_t V;
	T* result;

public:
	FloydWarshall(size_t n){
		V = n;
		result = new T[V*V+1];
		fill_n(result, V*V+1, INF);
	}
	~FloydWarshall(){
		delete[] result;
	}
	bool check(const T& a, const T& b){
		return a < b;
	}
	void add(size_t from, size_t to, const T& dist){
		if(check(dist, result[from*V + to])) result[from*V + to] = dist;
	}
	void exec(){
		for(size_t i = 0; i < V; i++)
			result[i*V + i] = 0;
		for(size_t k = 0; k < V; k++)
			for(size_t i = 0; i < V; i++)
				for(size_t j = 0; j < V; j++)
					if(check(result[i*V + k] + result[k*V + j], result[i*V + j]))
						result[i*V + j] = result[i*V + k] + result[k*V + j];
	}
	T getDist(size_t from, size_t to){
		return result[from*V + to];
	}
};

class FastIO{
private:
	int readInt(int &n){
		register int c;
		n = 0;
		bool neg = false;
		c = getchar();
		if(!(~c)) return -1;
		for(; ((c < 48 || c > 57)) && c != '-' && ~c; c = getchar());
		if(c == '-') neg = true, c = getchar();
		for(; c > 47 && c < 58 && ~c; c = getchar()){n = (n<<1)+(n<<3)+c-48;}
		if(neg) n = -n;
		return 1;
	}
	
public:
	FastIO(bool useFile = false){
		if(useFile){
			freopen("input.txt", "r", stdin);
			freopen("output.txt", "w", stdout);
		}
	}

	void solve();
};

int main(){
	FastIO fio;
	fio.solve();
	return 0;
}

void FastIO::solve(){
	int T, N, F, M, Q, t1, t2, f1, f2, t, loc1, loc2, u, v, size, dist;
	pair<int, int> usable[2];
	readInt(T);
	while(T--){
		readInt(N);
		readInt(F);
		readInt(M);
		int V = N;
		vector<pair<int, int>> vertices[N+5];
		FloydWarshall<int> fw(N+2*M);
		for(int i = 1; i <= N-1; i++){
			fw.add(i-1, i, 1);
			fw.add(i, i-1, 1);
		}
		fw.add(0, N-1, 1);
		fw.add(N-1, 0, 1);
		for(int i = 1; i <= N; i++)
			vertices[i].push_back(pair<int, int>(1, i-1));
		for(int i = 0; i < M; i++){
			readInt(t1);
			readInt(f1);
			readInt(t2);
			readInt(f2);
			readInt(t);
			loc1 = lower_bound(vertices[t1].begin(), vertices[t1].end(), pair<int, int>(f1,std::numeric_limits<int>::min())) - vertices[t1].begin();
			loc2 = lower_bound(vertices[t2].begin(), vertices[t2].end(), pair<int, int>(f2,std::numeric_limits<int>::min())) - vertices[t2].begin();
			if(loc1 == vertices[t1].size() || vertices[t1][loc1].first != f1){
				vertices[t1].insert(vertices[t1].begin()+loc1, pair<int, int>(f1, V));
				u = V++;
			}else
				u = vertices[t1][loc1].second;
			if(loc2 == vertices[t2].size() || vertices[t2][loc2].first != f2){
				vertices[t2].insert(vertices[t2].begin()+loc2, pair<int, int>(f2, V));
				v = V++;
			}else
				v = vertices[t2][loc2].second;
			fw.add(u, v, t);
			fw.add(v, u, t);
		}
		for(int i = 1; i <= N; i++){
			size = vertices[i].size();
			for(int j = 0; j < size-1; j++){
				fw.add(vertices[i][j].second, vertices[i][j+1].second, vertices[i][j+1].first-vertices[i][j].first);
				fw.add(vertices[i][j+1].second, vertices[i][j].second, vertices[i][j+1].first-vertices[i][j].first);
			}
		}
		fw.exec();
		readInt(Q);
		while(Q--){
			readInt(t1);
			readInt(f1);
			readInt(t2);
			readInt(f2);
			size = 0;
			loc1 = lower_bound(vertices[t1].begin(), vertices[t1].end(), pair<int, int>(f1,std::numeric_limits<int>::min())) - vertices[t1].begin();
			if(loc1 != vertices[t1].size() && vertices[t1][loc1].first != f1){
				usable[size].first = vertices[t1][loc1-1].second;
				usable[size++].second = f1-vertices[t1][loc1-1].first;
				usable[size].first = vertices[t1][loc1].second;
				usable[size++].second = vertices[t1][loc1].first-f1;
			}else{
				if(loc1 == vertices[t1].size()){
					usable[size].first = vertices[t1][loc1-1].second;
					usable[size++].second = f1-vertices[t1][loc1-1].first;
				}else{
					usable[size].first = vertices[t1][loc1].second;
					usable[size++].second = vertices[t1][loc1].first-f1;
				}
			}
			dist = INF;
			loc2 = lower_bound(vertices[t2].begin(), vertices[t2].end(), pair<int, int>(f2,std::numeric_limits<int>::min())) - vertices[t2].begin();
			if(loc2 != vertices[t2].size() && vertices[t2][loc2].first != f2){
				for(int i = 0; i < size; i++){
					if(dist > fw.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first))
						dist = fw.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first);
					if(dist > fw.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2))
						dist = fw.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2);
				}
			}else{
				if(loc2 == vertices[t2].size()){
					for(int i = 0; i < size; i++)
						if(dist > fw.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first))
							dist = fw.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first);
				}else{
					for(int i = 0; i < size; i++)
						if(dist > fw.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2))
							dist = fw.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2);
				}
			}
			if(t1 == t2)
				if(abs(f1-f2) < dist)
					dist = abs(f1-f2);
			printf("%d\n", dist);
		}
	}
}