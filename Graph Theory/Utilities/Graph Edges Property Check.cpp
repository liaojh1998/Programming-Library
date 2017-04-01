//Graph Edges Property Check template
#include <bits/stdc++.h>
using namespace std;

class GEPCheck{
private:
	size_t V;
	int* dfs_state;
	int* parent;
	vector<size_t>* G;
	vector<pair<size_t, int> >* property;

public:
	//Constructor, n - number of vertices
	GEPCheck(size_t n){
		V = n;
		dfs_state = new int[V];
		memset(dfs_state, -1, sizeof(int)*V);
		parent = new int[V];
		memset(parent, -1, sizeof(int)*V);
		property = new vector<pair<size_t, int> >[V];
		G = new vector<size_t>[V];
	}
	//Destructor
	~GEPCheck(){
		delete[] G;
		delete[] parent;
		delete[] dfs_state;
		delete[] property;
	}

	//Add edges
	void add(size_t u, size_t v){
		G[u].push_back(v);
	}
	//Graph Edges Property Check (DFS)
	//Property: 0 - Directed, 1 - Bidirected, 2 - Cycle (directed to explored node), 3 - Extra (directed to visited node)
	void add_property(size_t u, size_t v, const int& p){
		size_t len = property[u].size();
		for(size_t i = 0; i < len; i++)
			if(property[u][i].first == v){
				property[u][i].second = p;
				return;
			}
		property[u].push_back(pair<size_t, int>(v, p));
	}
	void GEPdfs(size_t u){
		dfs_state[u] = 0; //0 means explored node
		size_t len = G[u].size();
		for(size_t i = 0; i < len; i++){
			size_t v = G[u][i];
			if(dfs_state[v] == -1){
				parent[v] = u;
				property[u].push_back(pair<size_t, int>(v, 0));
				GEPdfs(v);
			}else if(dfs_state[v] == 0)
				if(parent[u] == v){
					add_property(u, v, 1);
					add_property(v, u, 1);
				}else
					add_property(u, v, 2); //The edge that causes a cycle
			else if(dfs_state[v] == 1) //1 means visited node
				add_property(u, v, 3); //May be cycle, may also be bidirectional, but definitely is an edge that visits an already visited node
			dfs_state[u] = 1;
		}
	}
	//Graph Edges Property Execution
	void exec(){
		for(int i = 0; i < V; i++)
			if(dfs_state[i] == -1)
				GEPdfs(i);
		for(int i = 0; i < V; i++)
			sort(property[i].begin(), property[i].end());
	}

	//Access Graph Edges Properties
	int getEdgeProperty(size_t u, size_t v){
		size_t lo = 0, hi = property[u].size();
		while(lo < hi){
			size_t mid = (lo + hi)/2;
			if(v <= property[u][mid].first)
				hi = mid;
			else
				lo = mid+1;
		}
		return lo == property[u].size() ? -1 : property[u][lo].second; //Return -1 if no such edge exists
	}
};

int main(){
	//Enter code here
	return 0;
}