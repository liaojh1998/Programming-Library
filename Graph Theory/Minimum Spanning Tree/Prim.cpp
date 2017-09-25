//Prim's algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class Prim{
#define INF (1<<28) //Change this if there's a bigger infinity, remember to avoid overflow
private:
	size_t V;
	T mstCost;
	bool* taken;
	vector<pair<size_t, T> >* G;

public:
	//Constructor, n - number of vertices
	Prim(size_t n){
		V = n;
		G = new vector<pair<size_t, T> >[V];
		taken = new bool[V]();
	}
	~Prim(){
		delete[] G;
		delete[] taken;
	}
	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		G[from].push_back(pair<size_t, T>(to, dist));
	}
	//Comparison objects
	class cmp{
		public:
		bool operator()(const pair<size_t, T> a, const pair<size_t, T> b){
			//Change this if not minimum-spanning tree
			if(a.second == b.second)
				return a.first > b.first;
			return a.second > b.second;
		}
	};

	//Prim's Algorithm Execution
	//Time Complexity: O(ElogV)
	//Uses binary heap
	//Start from arbitrary source s, notice that limit is not needed since graph is limited by AdjList
	void exec(size_t s){
		priority_queue<pair<size_t, size_t>, vector<pair<size_t, size_t> >, cmp> q;
		taken[s] = true;
		size_t len = G[s].size();
		for(size_t i = 0; i < len; i++){
			if(!taken[G[s][i].first])
				q.push(G[s][i]);
		}
		mstCost = 0;
		while(!q.empty()){
			pair<size_t, T> cur = q.top(); q.pop();
			if(!taken[cur.first]){
				mstCost += cur.second;
				taken[cur.first] = true;
				len = G[cur.first].size();
				for(size_t i = 0; i < len; i++){
					if(!taken[G[cur.first][i].first])
						q.push(G[cur.first][i]);
				}
			}
		}
	}

	//Access minimum weight required
	T getMSTCost(){
		return mstCost;
	}
};

int main(){
	//Enter code here
	return 0;
}