//Shortest Path Faster algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class SPFA{
private:
	T* result;
	//size_t* prev; /Useful for path reconstruction
	bool* checked;
	size_t V;
	vector<pair<size_t, T> >* G;

public:
	//Constructor, n = number of vertices
	SPFA(size_t n){
		V = n;
		result = new T[V]();
		//prev = new size_t[V]();
		G = new vector<pair<size_t, T> >[V];
		checked = new bool[V]();
	}
	//Destructor
	~SPFA(){
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
	bool check(const T& a, const T& b){
		//Change this opposite to the above if not shortest-path
		return a < b;
	}

	//SPFA Execution
	//(no negative cycles (cannot detect), undirected/directed graph)
	//Time complexity: O(|V||E|) on dense graphs, average case time complexity O(|E|)
	//This runs about same as Dijkstra with priority queue on average case, but slower on worst case, and definitely faster than original Dijkstra and Bellman-Ford
	//Optimized with Small Label First technique
	void exec(size_t s){
		size_t u, v;
		T w;
		bool queued[V];
		memset(queued, 0, sizeof(queued));
		//Unless you want previous, this is not needed
		//fill_n(prev, V, -1);
		deque<size_t> q;
		result[s] = 0;
		q.push_front(s);
		checked[s] = true;
		while(!q.empty()){
			u = q.front(); q.pop_front();
			queued[u] = false;
			size_t len = G[u].size();
			for(size_t i = 0; i < len; i++){
				v = G[u][i].first;
				w = G[u][i].second;
				if(!checked[v] || check(result[u] + w, result[v])){
					//prev[v] = u;
					checked[v] = true;
					result[v] = result[u] + w;
					if(!queued[v]){
						queued[v] = true;
						if(!q.empty() && result[v] < result[q.front()])
							q.push_front(v);
						else
							q.push_back(v);
					}
				}
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