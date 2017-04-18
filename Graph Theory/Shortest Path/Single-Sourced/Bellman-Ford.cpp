//Bellman-Ford's Shortest Path algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class BellmanFord{
private:
	T* result;
	//size_t* prev; //Useful for path reconstruction
	bool* checked;
	size_t V;
	vector<pair<size_t, T> >* G;

public:
	//Constructor, n = number of vertices
	BellmanFord(size_t n){
		V = n;
		result = new T[V]();
		//prev = new size_t[V]();
		G = new vector<pair<size_t, T> >[V];
		checked = new bool[V]();
	}
	//Destructor
	~BellmanFord(){
		delete[] result;
		//delete[] prev;
		delete[] G;
		delete[] checked;
	}
	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		G[from].push_back(pair<size_t, T>(to, dist));
	}
	//Comparison objects
	bool check(const T& a, const T& b){
		//Change this if not shortest-path
		return a < b;
	}

	//Bellman-Ford's algorithm Execution
	//V*E <= 10,000,000, okay on weighted graph with negative weights
	//Terminates at N (limit to save time)
	//(no negative cycles (can detect), undirected/directed graph)
	//Time complexity: O(|V||E|)
	void exec(size_t s){
		size_t v;
		T w;
		//Unless you want previous, this is not needed
		//fill_n(prev, V, -1);
		result[s] = 0;
		checked[s] = true;
		for(size_t i = 0; i < V; i++){
			for(size_t j = 0; j < V; j++){
				size_t len = G[j].size();
				for(size_t k = 0; k < len; k++){
					v = G[j][k].first;
					w = G[j][k].second;
					if(checked[j] && (!checked[v] || check(result[j] + w, result[v]))){
						checked[v] = true;
						result[v] = result[j] + w;
						//prev[v] = j;
					}
				}
			}
		}
		//This is used to check if there is negative-weight cycles
		/*
		for(size_t i = 0; i < V; i++){
			size_t len = G[i].size();
			for(size_t j = 0; j < len; j++)
				if(result[i] + G[i][j].second < result[G[i][j].first]){
					printf("Graph has a negative-weight cycle\n");
					return;
				}
		}
		*/
	}
	
	//Access shortest path, -1 if not accessible
	T operator[](size_t i){
		return checked[i] ? result[i] : -1; 
	}
};

int main(){
	//Enter code here
	return 0;
}