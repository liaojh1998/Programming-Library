#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool dfs(int u, int color, vector<int> *adjlist, bool *vis, bool *state){
	vis[u] = true;
	state[u] = color;
	bool suspicious = false;
	int size = adjlist[u].size();
	for(int i = 0; i < size && !suspicious; i++)
		if(vis[adjlist[u][i]]){
			if(state[adjlist[u][i]] == color)
				suspicious = true;
		}else
			suspicious = dfs(adjlist[u][i], !color, adjlist, vis, state);
	return suspicious;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, V, E, u, v;
	cin >> T;
	for(int i = 1; i <= T; i++){
		cin >> V >> E;
		bool adjmat[V+5][V+5];
		memset(adjmat, 0, sizeof(adjmat));
		vector<int> adjlist[V+5];
		for(int i = 0; i < E; i++){
			cin >> u >> v;
			if(!adjmat[u][v]){
				adjmat[u][v] = adjmat[v][u] = true;
				adjlist[u].push_back(v);
				adjlist[v].push_back(u);
			}
		}
		bool vis[V+5], state[V+5], suspicious = false;
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= V && !suspicious; i++)
			if(!vis[i])
				suspicious = dfs(i, 0, adjlist, vis, state);
		cout << "Scenario #" << i << ":" << endl;
		if(suspicious)
			cout << "Suspicious bugs found!" << endl;
		else
			cout << "No suspicious bugs found!" << endl;
	}
}