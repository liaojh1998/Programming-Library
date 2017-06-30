#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

void dfs(int u, int d, vector<int> *adjlist, bool *vis, int *dist){
	vis[u] = true;
	dist[u] = d;
	int size = adjlist[u].size();
	for(int i = 0; i < size; i++)
		if(!vis[adjlist[u][i]])
			dfs(adjlist[u][i], d+1, adjlist, vis, dist);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//Tree, acyclic, undirected, connected
	int N, u, v;
	cin >> N;
	vector<int> adjlist[N+5];
	for(int i = 0; i < N-1; i++){
		cin >> u >> v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
	}
	bool vis[N+5];
	int dist[N+5];
	memset(vis, 0, sizeof(vis));
	memset(dist, 0, sizeof(dist));
	dfs(1, 0, adjlist, vis, dist);
	int farthest_node = 0;
	for(int i = 1; i <= N; i++)
		if(dist[i] > dist[farthest_node])
			farthest_node = i;
	memset(vis, 0, sizeof(vis));
	memset(dist, 0, sizeof(dist));
	dfs(farthest_node, 0, adjlist, vis, dist);
	int maxdist = 0;
	for(int i = 1; i <= N; i++)
		if(dist[i] > maxdist)
			maxdist = dist[i];
	printf("%d\n", maxdist);
}