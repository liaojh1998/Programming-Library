#include <bits/stdc++.h>
using namespace std;

template<typename T> class SPFA{
private:
	T* result;
	bool* checked;
	size_t V;
	vector<pair<size_t, T> >* G;

public:
	SPFA(size_t n){
		V = n;
		result = new T[V*V+1]();
		G = new vector<pair<size_t, T> >[V];
		checked = new bool[V]();
	}
	~SPFA(){
		delete[] result;
		delete[] G;
		delete[] checked;
	}
	void add(size_t from, size_t to, const T& dist){
		G[from].push_back(pair<size_t, T>(to, dist));
	}
	bool check(const T& a, const T& b){
		return a < b;
	}
	void exec(){
		size_t u, v;
		T w, cur;
		bool queued[V];
		for(int s = 0; s < V; s++){
			memset(checked, 0, sizeof(bool)*V);
			memset(queued, 0, sizeof(queued));
			deque<size_t> q;
			result[s*V + s] = 0;
			q.push_front(s);
			checked[s] = true;
			while(!q.empty()){
				u = q.front(); q.pop_front();
				queued[u] = false;
				size_t len = G[u].size();
				for(size_t i = 0; i < len; i++){
					v = G[u][i].first;
					w = G[u][i].second;
					if(!checked[v] || check(result[s*V + u] + w, result[s*V + v])){
						checked[v] = true;
						result[s*V + v] = result[s*V + u] + w;
						if(!queued[v]){
							queued[v] = true;
							if(!q.empty() && check(result[s*V + v], result[s*V + q.front()]))
								q.push_front(v);
							else
								q.push_back(v);
						}
					}
				}
			}
		}
	}
	T getDist(size_t u, size_t v){
		return result[u*V + v]; 
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
		SPFA<int> spfa(N+2*M);
		for(int i = 1; i <= N-1; i++){
			spfa.add(i-1, i, 1);
			spfa.add(i, i-1, 1);
		}
		spfa.add(0, N-1, 1);
		spfa.add(N-1, 0, 1);
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
			spfa.add(u, v, t);
			spfa.add(v, u, t);
		}
		for(int i = 1; i <= N; i++){
			size = vertices[i].size();
			for(int j = 0; j < size-1; j++){
				spfa.add(vertices[i][j].second, vertices[i][j+1].second, vertices[i][j+1].first-vertices[i][j].first);
				spfa.add(vertices[i][j+1].second, vertices[i][j].second, vertices[i][j+1].first-vertices[i][j].first);
			}
		}
		spfa.exec();
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
			dist = 1000000000;
			loc2 = lower_bound(vertices[t2].begin(), vertices[t2].end(), pair<int, int>(f2,std::numeric_limits<int>::min())) - vertices[t2].begin();
			if(loc2 != vertices[t2].size() && vertices[t2][loc2].first != f2){
				for(int i = 0; i < size; i++){
					if(dist > spfa.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first))
						dist = spfa.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first);
					if(dist > spfa.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2))
						dist = spfa.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2);
				}
			}else{
				if(loc2 == vertices[t2].size()){
					for(int i = 0; i < size; i++)
						if(dist > spfa.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first))
							dist = spfa.getDist(usable[i].first, vertices[t2][loc2-1].second)+usable[i].second+(f2-vertices[t2][loc2-1].first);
				}else{
					for(int i = 0; i < size; i++)
						if(dist > spfa.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2))
							dist = spfa.getDist(usable[i].first, vertices[t2][loc2].second)+usable[i].second+(vertices[t2][loc2].first-f2);
				}
			}
			if(t1 == t2)
				if(abs(f1-f2) < dist)
					dist = abs(f1-f2);
			printf("%d\n", dist);
		}
	}
}