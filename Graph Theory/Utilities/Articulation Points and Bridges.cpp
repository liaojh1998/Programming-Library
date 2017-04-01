//Articulation Points and Bridges template
#include <bits/stdc++.h>
using namespace std;

class APBSearch{
private:
	size_t V;
	size_t* dfs_least;
	int* dfs_state;
	int* parent;
	bool* ap;
	vector<size_t> articulation_points;
	vector<pair<size_t, size_t> > articulation_bridges;
	vector<size_t>* G;

public:
	//Constructor, n - number of vertices
	APBSearch(size_t n){
		V = n;
		dfs_least = new size_t[V]();
		dfs_state = new int[V];
		memset(dfs_state, -1, sizeof(int)*V);
		parent = new int[V];
		memset(parent, -1, sizeof(int)*V);
		ap = new bool[V]();
		G = new vector<size_t>[V];
	}
	//Destructor
	~APBSearch(){
		delete[] G;
		delete[] dfs_least;
		delete[] dfs_state;
		delete[] parent;
		delete[] ap;
	}

	//Add edges
	void add(size_t u, size_t v){
		G[u].push_back(v);
	}
	//Finding Articulation Points and Bridges
	//(Undirected Graph, Unweighted Graph)
	//Time Complexity: O(V + E)
	int rootChildren;
	void APBdfs(size_t u, size_t& dfsNumberCounter, size_t& dfsRoot, size_t& rootChildren){
		dfs_least[u] = dfs_state[u] = dfsNumberCounter++;
		size_t len = G[u].size();
		for(size_t i = 0; i < len; i++){
			size_t v = G[u][i];
			if(dfs_state[v] == -1){
				parent[v] = u;
				if(u == dfsRoot) rootChildren++;
				APBdfs(v, dfsNumberCounter, dfsRoot, rootChildren);
				if(dfs_least[v] >= dfs_state[u])
					ap[u] = true;
				if(dfs_least[v] > dfs_state[u])
					articulation_bridges.push_back(pair<size_t, size_t>(u, v));
				dfs_least[u] = min(dfs_least[u], dfs_least[v]);
			}else if(v != parent[u])
				dfs_least[u] = min(dfs_least[u], dfs_least[v]);
		}
	}
	//Articulation Points and Bridges Execution
	void exec(){
		size_t dfsNumberCounter = 0;
		for(size_t i = 0; i < V; i++)
			if(dfs_state[i] == -1){
				size_t dfsRoot = i, rootChildren = 0;
				APBdfs(i, dfsNumberCounter, dfsRoot, rootChildren);
				ap[i] = (rootChildren > 1);
			}
		for(size_t i = 0; i < V; i++)
			if(ap[i])
				articulation_points.push_back(i);
	}

	//Access Articulation Points and Bridges after execution
	vector<size_t>* getPoints(){
		return &articulation_points;
	}
	vector<pair<size_t, size_t> >* getBridges(){
		return &articulation_bridges;
	}
};

int main(){
	//Enter code here
	return 0;
}