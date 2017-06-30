#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int main(){
	//freopen("input.txt", "r", stdin);
	int str[100005], len = 0;
	vector<int> adjlist[10];
	for(char c = getchar(); c >= '0' && c <= '9'; c = getchar(), len++){
		str[len] = c - '0';
		adjlist[str[len]].push_back(len);
	}
	int dist[100005], cur, size, v;
	memset(dist, 1, sizeof(dist));
	queue<int> q;
	dist[0] = 0;
	q.push(0);
	while(!q.empty()){
		cur = q.front(); q.pop();
		if(cur+1 < len && dist[cur]+1 < dist[cur+1]){
			dist[cur+1] = dist[cur]+1;
			q.push(cur+1);
		}
		if(cur-1 >= 0 && dist[cur]+1 < dist[cur-1]){
			dist[cur-1] = dist[cur]+1;
			q.push(cur-1);
		}
		size = adjlist[str[cur]].size();
		for(int i = 0; i < size; i++){
			v = adjlist[str[cur]][i];
			if(dist[cur]+1 < dist[v]){
				dist[v] = dist[cur]+1;
				q.push(v);
			}
		}
		adjlist[str[cur]].clear(); //Need not visit a digit more than twice, first visit to a digit always has the smallest dist
	}
	printf("%d\n", dist[len-1]);
	return 0;
}