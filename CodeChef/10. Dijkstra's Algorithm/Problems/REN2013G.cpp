#include <iostream>
#include <algorithm>
#include <cstring>
#define INF (2000005)
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    N++;
    int x[N+1], y[N+1];
    for(int i = 1; i <= N; i++)
        cin >> x[i] >> y[i];
    int dist[N+1];
    fill_n(dist, N+1, INF);
    dist[0] = 0;
    x[0] = y[0] = 0;
    bool vis[N+1];
    memset(vis, 0, sizeof(vis));
    int min, index;
    for(int i = 0; i < N; i++){
        index = -1;
        min = INF;
        for(int i = 0; i <= N; i++)
            if(!vis[i] && dist[i] < min){
                index = i;
                min = dist[i];
            }
        if(index == N) break;
        vis[index] = true;
        for(int i = 0; i <= N; i++)
            if(!vis[i] && min+(x[index]-x[i])*(x[index]-x[i])+(y[index]-y[i])*(y[index]-y[i]) < dist[i])
                dist[i] = min + (x[index]-x[i])*(x[index]-x[i]) + (y[index]-y[i])*(y[index]-y[i]);
    }
    cout << dist[N] << endl;
}