//Knapsack template
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//N - number of items, W - weight limit
template<int N, int W> struct knapsack{
	//Given N items, each with its own value N and weight W, calculate the max value we can carry on max weight
	struct item{
		int weight, value;
	}items[N];
	int len;
	//Constructor
	knapsack(){
		len = 0;
	}
	//Add method
	void add(int w, int v){
		items[len].weight = w;
		items[len++].value = v;
	}

	//0-1 Knapsack with top-down DP (faster than bottom-up DP)
	//Time complexity: O(N(S))
	//N is number of items, S is state required to go through (usually maxweight)
	//To make this a Bounded Knapsack, simply add limited copies to weight and value array
	//Make sure N is big enough to fit all copies; this may also be implemented with vectors
	//Recursion top-down, searches less state
	int dp[N][W];
	int rec(int id, int w){
		printf("%d %d\n", id, w);
		if(id == len || w < 0) return 0;
		if(items[id].weight > w) return dp[id][w] = rec(id + 1, w);
		if(dp[id][w] != -1) return dp[id][w];
		return dp[id][w] = max(rec(id + 1, w), items[id].value + rec(id + 1, w - items[id].weight));
	}
	//Maxweight is the weight to given
	int tdks(int maxweight){
		memset(dp, -1, sizeof(dp));
		return rec(0, maxweight);
	}

	//0-1 Knapsack with bottom-up DP (slower)
	//Time complexity: O(N(S))
	//Searches all state, the true DP
	//May be implemented with the space-saving trick (just store all states in 1 array)
	int buks(int maxweight){
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i < len; i++){
			for(int j = 0; j <= maxweight; j++){
				if(items[i].weight > j){
					if(i)
						dp[i][j] = dp[i-1][j];
				}else{
					if(i)
						dp[i][j] = max(dp[i-1][j], dp[i-1][j-items[i].weight] + items[i].value);
					else
						dp[i][j] = items[i].value;
				}
			}
		}
		return dp[len-1][maxweight];
	}

	//Unbounded Knapsack
	//Time complexity: O(N(S))
	//Where S is the maxweight
	//Searches all state
	int mdp[W];
	int ubks(int maxweight){
		memset(mdp, 0, sizeof(mdp));
		for(int i = 0; i < len; i++){
			for(int j = 0; j <= maxweight; j++){
				if(items[i].weight < j && mdp[j - items[i].weight] + items[i].value > mdp[j])
					mdp[j] = mdp[j - items[i].weight] + items[i].value;
			}
		}
		return mdp[maxweight];
	}

	//Fractional Knapsack
	//Time Complexity: O(NlogN)
	//This is a greedy algorithm, and as easy as it could ever be
	//Value comparison based on ratio of value to weight
	class cmp{
		public:
		bool operator()(const item &a, const item &b){
			double ar = (double)a.value / a.weight;
			double br = (double)b.value / b.weight;
			return ar > br;
		}
	}comparison;
	//Fractional Knapsack Execution
	double fks(int maxweight){
		double finalValue = 0.0;
		sort(items, items + len, comparison);
		for(int i = 0; i < len && maxweight; i++){
			if(maxweight < items[i].weight){
				finalValue += maxweight * ((double)items[i].value / items[i].weight);
				maxweight = 0;
			}else{
				finalValue += items[i].value;
				maxweight -= items[i].weight;
			}
		}
		return finalValue;
	}
};

int main(){
	//Enter code here
	return 0;
}