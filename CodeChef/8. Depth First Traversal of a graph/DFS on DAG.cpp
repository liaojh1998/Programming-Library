//Depth First Search Shortest Path algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class DFS{
private:
	T* result;
	//size_t* prev; //Useful for path reconstruction
	bool* checked;
	size_t V;
	vector<pair<size_t, T> >* G;

public:
	//Constructor, n = number of vertices
	DFS(size_t n){
		V = n;
		result = new T[V]();
		//prev = new size_t[V]();
		G = new vector<pair<size_t, T> >[V];
		checked = new bool[V]();
	}
	//Destructor
	~DFS(){
		delete[] result;
		//delete[] prev;
		delete[] G;
		delete[] checked;
	}
	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		G[from].push_back(pair<size_t, T>(to, dist));
	}
	bool check(const T& a, const T& b){
		//Change this opposite to the above if not shortest-path
		return a < b;
	}

	//DFS
	//Directed acyclic graph only
	//This takes the idea of topological sort
	//Time complexity: O(|V| + |E|)
	void dfs(size_t u){
		size_t v;
		T w;
		size_t len = G[u].size();
		for(size_t i = 0; i < len; i++){
			v = G[u][i].first;
			w = G[u][i].second;
			if(!checked[v] || check(result[u] + w, result[v])){
				result[v] = result[u] + w;
				checked[v] = true;
				dfs(v);
			}
		}
	}
	//Execution
	void exec(size_t s){
		fill_n(checked, V, 0);
		checked[s] = true;
		dfs(s);
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