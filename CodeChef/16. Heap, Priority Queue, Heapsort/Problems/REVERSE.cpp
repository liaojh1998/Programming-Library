#include <bits/stdc++.h>
using namespace std;

template <class T>
class heap{
private:
	int N, s;
	T* arr;

	bool cmp(const T& a, const T& b){
		return a.second < b.second;
	}
	int prioritize(const int& a, const int& b){
		if(b > s)
			return a;
		return cmp(arr[a], arr[b]) ? a : b;
	}
	void swap(const int& a, const int& b){
		T tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
	}
	void up(int index){
		while(index > 1 && cmp(arr[index], arr[index>>1])){
			swap(index, index>>1);
			index >>= 1;
		}
	}
	void down(int index){
		int p;
		while(index<<1 <= s && cmp(arr[(p = prioritize(index<<1, index<<1|1))], arr[index])){
			swap(index, p);
			index = p;
		}
	}

public:
	heap(int n){
		N = n;
		arr = new T[N+5];
		s = 0;
	}
	~heap(){
		delete[] arr;
	}
	int size(){
		return s+1;
	}
	bool empty(){
		return !s;
	}
	void push(const T& E){
		arr[++s] = E;
		up(s);
	}
	T top(){
		return arr[1];
	}
	void pop(){
		arr[1] = arr[s--];
		down(1);
	}
};

int solve(vector<pair<int, int>> *edges, int N){
	heap<pair<int, int>> q(1000000);
	q.push(pair<int, int>(1, 0));
	bool vis[N+5];
	int dist[N+5];
	memset(vis, 0, sizeof(vis));
	memset(dist, -1, sizeof(dist));
	dist[1] = 0;
	while(!q.empty()){
		pair<int, int> cur = q.top(); q.pop();
		int u = cur.first, d = cur.second;
		if(u == N)
			return dist[N];
		if(vis[u])
			continue;
		vis[u] = true;
		int size = edges[u].size();
		for(int i = 0; i < size; i++){
			int v = edges[u][i].first, w = edges[u][i].second;
			if(!vis[v] && (dist[v] == -1 || dist[v] > d+w)){
				dist[v] = d+w;
				q.push(pair<int, int>(v, dist[v]));
			}
		}
	}
	return dist[N];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, M, u, v;
	cin >> N >> M;
	vector<pair<int, int>> edges[N+5];
	for(int i = 0; i < M; i++){
		cin >> u >> v;
		edges[u].push_back(pair<int, int>(v, 0));
		edges[v].push_back(pair<int, int>(u, 1));
	}
	printf("%d\n", solve(edges, N));
	return 0;
}