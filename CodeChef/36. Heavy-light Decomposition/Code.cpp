#include <bits/stdc++.h>
using namespace std;

class HLD{
private:
	int root, V;
	vector<int>* edges;
	int *subtree, *parent, *heavy, *size, *depth, *head;

	void dfs(const int& u){
		subtree[u] = 1;
		int max = 0, v;
		for(int i = 0; i < size[u]; i++){
			v = edges[u][i];
			if(parent[u] != v){
				parent[v] = u;
				dfs(v);
				if(subtree[v] > max)
					max = subtree[v];
				subtree[u] += subtree[v];
			}
		}
		if(V-subtree[u] > max)
			max = V-subtree[u];
		if(max <= V/2)
			root = u;
	}
	void reverse_dfs(const int& u){
		if(parent[u] == -1)
			return;
		subtree[parent[u]] = V-subtree[u];
		reverse_dfs(parent[u]);
		parent[parent[u]] = u;
	}
	void hld_dfs(const int& u){
		int v;
		if(head[u] == -1)
			head[u] = u;
		else
			head[u] = head[parent[u]];
		heavy[u] = -1;
		for(int i = 0; i < size[u]; i++){
			v = edges[u][i];
			if(parent[u] != v){
				depth[v] = depth[u] + 1;
				if(heavy[u] == -1 || subtree[v] > subtree[heavy[u]])
					heavy[u] = v;
			}
		}
		if(heavy[u] != -1){
			hld_dfs(heavy[u]);
			for(int i = 0; i < size[u]; i++){
				v = edges[u][i];
				if(v != heavy[u] && v != parent[u]){
					head[v] = -1;
					hld_dfs(v);
				}
			}
		}
	}

public:
	//0-indexing
	HLD(const int& N){
		V = N; //Please make sure V is not 1
		edges = new vector<int>[V];
		subtree = new int[V];
		parent = new int[V];
		heavy = new int[V];
		size = new int[V]();
		depth = new int[V];
		head = new int[V];
	}
	~HLD(){
		delete[] edges;
		delete[] subtree;
		delete[] parent;
		delete[] heavy;
		delete[] size;
		delete[] depth;
		delete[] head;
	}
	//Add edges
	void add(const int& u, const int& v){
		edges[u].push_back(v);
		edges[v].push_back(u);
		size[u]++;
		size[v]++;
	}
	//Call this to run
	void exec(){
		parent[0] = -1;
		dfs(0); //Optimize by rooting at centroid, subtree size dfs
		reverse_dfs(root); //Reverse parent path of root
		parent[root] = -1;
		subtree[root] = V;
		depth[root] = 0;
		//Using information from previous dfs to generate HLD, also generate depth for LCA
		head[root] = -1;
		hld_dfs(root);
	}
	//LCA, O(log(N)) query
	int lca(int a, int b){
		while(head[a] != head[b])
			if(depth[head[a]] > depth[head[b]])
				a = parent[head[a]];
			else
				b = parent[head[b]];
		return depth[a] < depth[b] ? a : b;
	}
};

int main(){
	//Enter code here
	return 0;
}