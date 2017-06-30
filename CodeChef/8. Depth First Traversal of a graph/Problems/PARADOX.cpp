#include <iostream>
#include <cstring>
#include <string>
using namespace std;

bool dfs(int p, bool c, bool *vis, bool *state, int *next, bool *base){
	if(vis[p] && state[p] != c) return true;
	else if(vis[p]) return false;
	vis[p] = true;
	state[p] = c;
	return dfs(next[p], c ? base[p] : !base[p], vis, state, next, base);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, t;
	string s;
	int next[105];
	bool base[105], vis[105], state[105], paradox;
	while(cin >> N && N){
		paradox = false;
		memset(next, 0, sizeof(next));
		memset(base, 0, sizeof(base));
		for(int i = 0; i < N; i++){
			cin >> t >> s;
			next[i] = t-1;
			base[i] = s == "true" ? true : false;
		}
		for(int i = 0; i < N && !paradox; i++){
			memset(vis, 0, sizeof(vis));
			memset(state, 0, sizeof(state));
			paradox = dfs(i, true, vis, state, next, base);
		}
		if(paradox)
			printf("PARADOX\n");
		else
			printf("NOT PARADOX\n");
	}
}