//Dijstra's Shortest Path algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class Dijkstra{
private:
	T* result;
	//size_t* prev; //Useful for path reconstruction
	bool* checked;
	size_t V;
	vector<pair<size_t, T> >* G;

public:
	//Constructor, n = number of vertices
	Dijkstra(size_t n){
		V = n;
		result = new T[V]();
		//prev = new size_t[V]();
		G = new vector<pair<size_t, T> >[V];
		checked = new bool[V]();
	}
	//Destructor
	~Dijkstra(){
		delete[] result;
		//delete[] prev;
		delete[] G;
		delete[] checked;
	}
	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		G[from].push_back(pair<size_t, T>(to, dist));
	}
	//Comparison objects
	class cmp{
		public:
		bool operator()(const pair<size_t, T>& a, const pair<size_t, T>& b){
			//Change this if not shortest-path
			return a.second > b.second;
		}
	};
	bool check(const T& a, const T& b){
		//Change this opposite to the above if not shortest-path
		return a < b;
	}

	//Dijkstra's Shortest Path algorithm execution
	//V, E <= 300,000, best on weighted graph, overkill on small graph
	//(no negative cycle (cannot detect), undirected/directed graph)
	//Time complexity: O((|E| + |V|)log|V|)
	void exec(size_t s){
		//Unless you want previous, this is not needed
		//fill_n(prev, V, -1);
		priority_queue<pair<size_t, T>, vector<pair<size_t, T> >, cmp> q;
		q.push(pair<size_t, T>(s, 0));
		result[s] = 0;
		checked[s] = true;
		while(!q.empty()){
			pair<size_t, T> p = q.top(); q.pop();
			if(check(result[p.first], p.second)) continue;
			size_t len = G[p.first].size();
			for(size_t i = 0; i < len; i++)
				if(!checked[G[p.first][i].first] || check(p.second + G[p.first][i].second, result[G[p.first][i].first])){
					//prev[G[p.first][i].first] = p.first;
					checked[G[p.first][i].first] = true;
					result[G[p.first][i].first] = p.second + G[p.first][i].second;
					q.push(pair<size_t, T>(G[p.first][i].first, result[G[p.first][i].first]));
				}
		}
	}
	
	//Access shortest path, -1 if not accessible
	T operator[](size_t i){
		return checked[i] ? result[i] : -1; 
	}
};

int main(){
	//Enter code here
	return 0;
}