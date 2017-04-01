//Strongly Connected Components template
#include <bits/stdc++.h>
using namespace std;

class SCCSearch{
private:
	size_t V;
	size_t* dfs_least;
	int* dfs_state;
	bool* visited;
	stack<size_t> s;
	vector<size_t>* SCC;
	vector<vector<size_t> > totalSCC;
	vector<size_t>* G;

public:
	//Constructor, n - number of vertices
	SCCSearch(size_t n){
		V = n;
		dfs_least = new size_t[V]();
		dfs_state = new int[V];
		memset(dfs_state, -1, sizeof(int)*V);
		visited = new bool[V]();
		SCC = new vector<size_t>[V];
		G = new vector<size_t>[V];
	}
	//Destructor
	~SCCSearch(){
		delete[] G;
		delete[] SCC;
		delete[] visited;
		delete[] dfs_state;
		delete[] dfs_least;
	}

	//Add edges
	void add(size_t u, size_t v){
		G[u].push_back(v);
	}
	//Strongly Connected Components (Directed Graph)
	//Uses Tarjan's Algorithm
	//Time Complexity: O(V + E)
	void tarjan(size_t u, size_t& dfsNumberCounter){
		dfs_least[u] = dfs_state[u] = dfsNumberCounter++;
		s.push(u);
		visited[u] = true;
		size_t len = G[u].size();
		for(size_t i = 0; i < len; i++){
			size_t v = G[u][i];
			if(dfs_state[v] == -1)
				tarjan(v, dfsNumberCounter);
			if(visited[v])
				dfs_least[u] = min(dfs_least[u], dfs_least[v]);
		}
		if(dfs_state[u] == dfs_least[u]){
			size_t v = V;
			while(u != v){
				v = s.top(); s.pop(); visited[v] = false;
				SCC[u].push_back(v);
			}
		}
	}
	//Strongly Connected Components Execution
	void exec(){
		size_t dfsNumberCounter = 0;
		for(size_t i = 0; i < V; i++){ //May be changed if 1-based indexing
			if(dfs_state[i] == -1)
				tarjan(i, dfsNumberCounter);
			if(size_t size = SCC[i].size()){
				vector<size_t> temp;
				temp.push_back(i);
				for(size_t j = 0; j < size; j++)
					temp.push_back(SCC[i][j]);
				totalSCC.push_back(temp);
			}
		}
	}

	//Access Strongly Connected Components
	vector<vector<size_t> >* getSCC(){
		return &totalSCC;
	}
};

int main(){
	//Enter code here
	return 0;
}