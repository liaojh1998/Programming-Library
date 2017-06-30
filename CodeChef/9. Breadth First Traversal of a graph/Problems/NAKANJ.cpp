#include <iostream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main(){
	int x[8] = {1, 2, 2, 1, -1, -2, -2, -1};
	int y[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, arr[8][8];
	bool vis[8][8];
	cin >> T;
	while(T--){
		memset(arr, 0, sizeof(arr));
		memset(vis, 0, sizeof(vis));
		string a, b;
		cin >> a >> b;
		int x1, y1, x2, y2;
		x1 = a[0]-'a';
		y1 = a[1]-'1';
		x2 = b[0]-'a';
		y2 = b[1]-'1';
		int nextx, nexty;
		queue<pair<int, int> > q;
		vis[y1][x1] = true;
		q.push(pair<int, int>(y1, x1));
		while(!q.empty()){
			pair<int, int> cur = q.front(); q.pop();
			for(int i = 0; i < 8; i++){
				nexty = cur.first+y[i];
				nextx = cur.second+x[i];
				if(nexty >= 0 && nexty < 8 && nextx >= 0 && nextx < 8 && !vis[nexty][nextx]){
					arr[nexty][nextx] = arr[cur.first][cur.second]+1;
					vis[nexty][nextx] = true;
					q.push(pair<int, int>(nexty, nextx));
				}
			}
		}
		cout << arr[y2][x2] << endl;
	}
	return 0;
}