//Traveling Salesman Problem template
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template<int N> struct TSP{
	#define INF (1<<28)
	int dist[N][N], mindist, dp[N][1<<N];
	//Constructor
	TSP(){
		memset(dist, -1, sizeof(dist));
		for(int i = 0; i < N; i++)
			dist[i][i] = 0;
		memset(dp, -1, sizeof(dp));
	}
	//Add function
	void add(int u, int v, int d){
		dist[u][v] = d;
		dist[v][u] = d;
	}
	//TSP problem top-down DP (using bitmask for subset of visited cities)
	//Time complexity: O(N^2 * 2^N)
	//Feasible for N = 16
	//bits may be changed to long long to bitmask more than 16
	//-1 means disconnected nodes
	int tsp(int pos, int bits){
		if(bits == (1<<N)-1) return dp[pos][0] = dist[pos][0] == -1 ? INF : dist[pos][0]; //Unreachable if INF
		if(dp[pos][bits] != -1) return dp[pos][bits];
		int d = INF;
		for(int i = 0; i < N; i++)
			if(i != pos && !(bits & (1 << i)) && dist[pos][i] != -1)
				d = min(d, dist[pos][i] + tsp(i, bits | (1 << i)));
		return dp[pos][bits] = d;
	}
	//DP Execution
	void exec(){
		mindist = tsp(0, 1);
	}
};

int main(){
	//Enter code here
	return 0;
}