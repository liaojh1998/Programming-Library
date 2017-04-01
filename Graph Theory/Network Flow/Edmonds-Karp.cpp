//Edmonds-Karp's algorithm template
//Refer to USACO 4.2 for extensions
//Refer to USACO 4.2.1 Drainage Ditch for space saving non-flow matrix method.
#include <bits/stdc++.h>
using namespace std;

template<typename T> class EdmondsKarp{
private:
	size_t V;
	T* C; //C - residual capacity
	T* F; //F - legal flow matrix
	size_t* P; //P - parent table
	size_t* M; //M - capacity of path found
	bool* checkedM;
	vector<size_t>* G; //Edge List

public:
	//Constructor, n - number of vertices
	EdmondsKarp(size_t n){
		V = n;
		C = new T[V*V+1]();
		F = new T[V*V+1]();
		P = new size_t[V]();
		M = new size_t[V]();
		checkedM = new bool[V]();
		G = new vector<size_t>[V];
	}
	//Destructor
	~EdmondsKarp(){
		delete[] C;
		delete[] F;
		delete[] P;
		delete[] M;
		delete[] checkedM;
		delete[] G;
	}

	//Add capacity
	void add(size_t from, size_t to, const T& capacity){
		G[from].push_back(to);
		C[from*V + to] += capacity; //Capacity is added in this case scenario, change if assignment
		F[from*V + to] = 0;
		//Reverse edge
		G[to].push_back(from);
		//C[to*V + from] += capacity; //Include if bidirectional
		F[to*V + from] = 0;
		//Unless there's anything special about residual capacity
		//If there really is, then:
		//Make new parameter for function: const T& flowed
		//F[from*V + to] = flowed;
		//F[to*V + from] = -flowed;
	}

	//Edmonds Karp Algorithm
	T bfs(size_t s, size_t t){
		memset(P, -1, sizeof(size_t)*V);
		memset(checkedM, 0, sizeof(bool)*V); //Capacity of found path to sink
		P[s] = -2; //Do not rediscover source
		queue<size_t> q;
		q.push(s);
		while(!q.empty()){
			size_t u = q.front(); q.pop();
			size_t len = G[u].size();
			for(size_t i = 0; i < len; i++){
				size_t v = G[u][i];
				//If there is available capacity, and v is not seen before in search
				if(C[u*V + v] - F[u*V + v] > 0 && P[v] == -1){
					P[v] = u;
					//min(parent flow, current flow) - minimum weight
					M[v] = checkedM[u] ? C[u*V + v] - F[u*V + v] < M[u] ? C[u*V + v] - F[u*V + v] : M[u] : C[u*V + v] - F[u*V + v];
					checkedM[v] = true;
					//if v isn't the sink
					if(v != t)
						q.push(v);
					else{
						return M[t];
					}
				}
			}
		}
		return 0;
	}
	//Edmonds-Karp's Algorithm Execution
	//Time Complexity: O((V)(E^2))
	//Ford Fulkerson's method but with a defined backtrack search
	//Calculates the maximum flow/minimum cut (not cost!) in the directed graph
	//For multi-source/multi-sink problems, create a supersource node and a supersink node and connect all source to supersource with inf capacity, same for all sink to supersink
	//For problems that have capacity on vertex, use vertex splitting technique: other nodes -> vin -> capacity -> vout -> other nodes, run edmondsKarp as normal
	//s - source, t - sink
	T exec(size_t s, size_t t){
		T f = 0, m;
		while(m = bfs(s, t)){
			f = f + m;
			size_t v = t; //Backtrack search
			while(v != s){
				size_t u = P[v];
				//Ford Fulkerson's method
				F[u*V + v] += m; //Forward add capacity so when check available capacity = 0
				F[v*V + u] -= m; //Backward subtract capacity to right conditions where first filled capacity is wrong
				v = u; //Backtrack
			}
		}
		return f;
	}
};

int main(){
	//Enter code here
	return 0;
}