#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

void bfs(int* digit, int* parent, bool* vis, const int& N){
	queue<int> q;
	q.push(1);
	parent[1] = 0;
	digit[1] = 1;
	vis[1] = true;
	int cur, mod;
	while(!q.empty()){
		cur = q.front(); q.pop();
		if(cur == 0) break;
		mod = (cur*10)%N;
		if(!vis[mod]){
			vis[mod] = true;
			parent[mod] = cur;
			digit[mod] = 0;
			q.push(mod);
		}
		mod = (cur*10+1)%N;
		if(!vis[mod]){
			vis[mod] = true;
			parent[mod] = cur;
			digit[mod] = 1;
			q.push(mod);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N;
	cin >> T;
	while(T--){
		cin >> N;
		if(N == 1){
			cout << 1 << endl;
			continue;
		}
		int digit[N+5], parent[N+5];
		bool vis[N+5];
		memset(digit, 0, sizeof(digit));
		memset(vis, 0, sizeof(vis));
		bfs(digit, parent, vis, N);
		stack<int> ans;
		ans.push(digit[0]);
		int cur = parent[0];
		while(cur){
			ans.push(digit[cur]);
			cur = parent[cur];
		}
		while(!ans.empty()){
			cout << ans.top();
			ans.pop();
		}
		cout << endl;
	}
	return 0;
}