//Bipartite Graph check/coloring template
#include <bits/stdc++.h>
using namespace std;

class BGCheck{
private:
	size_t V;
	int* color;
	vector<size_t>* G;

public:
	//Constructor, n - number of vertices
	BGCheck(size_t n){
		V = n;
		color = new int[V];
		memset(color, -1, sizeof(int)*V);
		G = new vector<size_t>[V];
	}
	//Destructor
	~BGCheck(){
		delete[] G;
		delete[] color;
	}

	//Add edges
	void add(size_t u, size_t v){
		G[u].push_back(v);
	}
	//Bipartite Graph Check
	//Time Complexity: O(V + E)
	//returns true if bipartite, returns false if not
	//Start check from source s
	//Color fill in 0 and 1
	//Bipartite cycles have no odd cycles
	bool exec(size_t s){
		queue<size_t> q; q.push(s);
		color[s] = 0; //Change if not fill 0, 1
		bool isBipartite = true;
		while(!q.empty() && isBipartite){
			size_t u = q.front(); q.pop(); size_t len = G[u].size();
			for(size_t i = 0; i < len && isBipartite; i++){
				size_t v = G[u][i];
				if(color[v] == -1){
					color[v] = 1 - color[u];
					q.push(v);
				}else if(color[u] == color[v])
					isBipartite = false;
			}
		}
		return isBipartite;
	}
};

int main(){
	//Enter code here
	return 0;
}