//Floyd-Warshall's algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class FloydWarshall{
#define INF (1000000) //Change this if there's a bigger infinity, remember to avoid overflow
private:
	//Use if V <= 400, small graph
	size_t V;
	T* result;
	//size_t* parent;

public:
	//Constructor, n - number of vertices, 0-based please
	FloydWarshall(size_t n){
		V = n;
		result = new T[V*V+1];
		fill_n(result, V*V+1, INF);
		//parent = new size_t[V*V+1];
		//memset(parent, 0, sizeof(size_t)*(V*V+1));
	}
	//Destructor
	~FloydWarshall(){
		delete[] result;
		//delete[] parent;
	}

	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		result[from*V + to] = dist;
	}
	//Comparison objects
	bool check(const T& a, const T& b){
		//Change this if not shortest-path
		return a < b;
	}

	//Floyd-Warshall's Algorithm
	//No path reconstruction
	//(no negative cycles (can detect, however), undirected/directed graph)
	//Time complexity: O(|V|^3)
	void exec(){
		//Remove code below if self-paths have some specific condition
		for(size_t i = 0; i < V; i++)
			result[i*V + i] = 0;
		/* //For path reconstruction
		for(size_t i = 0; i < V; i++)
			for(size_t j = 0; j < V; j++)
				if(i == j || result[i*V + j] == INF) parent[i*V + j] = -1;
				else parent[i*V + j] = i;
		*/
		//Algorithm
		for(size_t k = 0; k < V; k++)
			for(size_t i = 0; i < V; i++)
				for(size_t j = 0; j < V; j++)
					if(check(result[i*V + k] + result[k*V + j], result[i*V + j])){
						//parent[i*V + j] = parent[k*V + j]; //only if you need the parent, which is rare
						result[i*V + j] = result[i*V + k] + result[k*V + j];
					}
	}
	/* //This algorithm allows the printing of a path between i and j, requires parent matrix, requires vector<size_t>
	void printPath(size_t i, size_t j, vector<size_t>* path){
		if(i != j)
			printPath(i, parent[i*V + j], path);
		path->push_back(j);
	}
	*/
	
	//Sample print matrix code, -1 means not unvisitable node
	void print(){
		for(size_t i = 0; i < V; i++)
			for(size_t j = 0; j < V; j++)
				printf("%lld%s", (result[i*V + j] < INF ? result[i*V + j] : -1), j == V - 1 ? "\n" : " ");
	}
};

int main(){
	//Enter code here
	return 0;
}