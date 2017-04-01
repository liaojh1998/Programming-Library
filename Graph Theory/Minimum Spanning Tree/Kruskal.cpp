//Kruskal's algorithm template
#include <bits/stdc++.h>
using namespace std;

//Provides a numbered structure to find and union disjoint sets
//Applications for: Kruskal's algorithm
//Improved by ranking (forming a tree) and path compression (directly change parent when called find so repeated queries have reduced runtime)
class UFDS{
private:
	//Set array to static if using C++11
	size_t* parent;
	size_t* rank;
	size_t N, disjointSetNum;

public:
	//Makes disjoint set i
	void makeSet(size_t i){
		parent[i] = i;
		rank[i] = 0;
	}

	//Useful functions
	//Constructors, n - size of array
	UFDS(size_t n){
		N = disjointSetNum = n;
		parent = new size_t[N];
		rank = new size_t[N];
		for(size_t i = 0; i < N; i++)
			makeSet(i);
	}
	//Destructors
	~UFDS(){
		delete[] parent;
		delete[] rank;
	}

	//Determine which set representative element i is in
	//Improved with path compression
	size_t findSet(size_t i){
		return parent[i] != i ? (parent[i] = findSet(parent[i])) : i;
	}
	//Merge 2 sets i, j together
	void unionSets(size_t i, size_t j){
		size_t parenti = findSet(i), parentj = findSet(j);
		//In same set
		if(parenti == parentj)
			return;
		//Not in same set
		if(rank[parenti] < rank[parentj])
			parent[parenti] = parentj;
		else{
			parent[parentj] = parenti;
			if(rank[parenti] == rank[parentj])
				rank[parenti]++;
		}
		disjointSetNum--;
	}
	//If 2 sets are in the same set
	bool isSameSet(size_t i, size_t j){
		return findSet(i) == findSet(j);
	}
	//Get number of disjoint Sets
	size_t getDisjointSetNum(){
		return disjointSetNum;
	}
};

template<typename T> class Kruskal{
#define INF (1<<28) //Change this if there's a bigger infinity, remember to avoid overflow
private:
	size_t V;
	T mstCost;
	vector<pair<T, pair<size_t, size_t> > > G;
	UFDS* sets;

public:
	//Constructor, n - number of vertices, 0-based please
	//Note: UFDS began on 0-based indexing, so if 1-based indexing, then getDisjointSetNum should be 2 if valid
	Kruskal(size_t n){
		V = n;
		sets = new UFDS(V);
	}
	~Kruskal(){
		delete sets;
	}
	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		G.push_back(pair<T, pair<size_t, size_t> >(dist, pair<size_t, size_t>(from, to)));
	}
	//Comparison object
	//Comparison objects
	class cmp{
		public:
		bool operator()(const pair<T, pair<size_t, size_t> > &a, const pair<T, pair<size_t, size_t> > &b){
			//Change this if not minimum-spanning tree
			return a.first < b.first;
		}
	}mstcomparison;

	//Kruskal's algorithm Execution
	//Given a connected, undirected, and weighted graph
	//Time Complexity: O(ElogV)
	void exec(){
		//Reordering of all Edges based on weights
		sort(G.begin(), G.end(), mstcomparison);
		mstCost = 0;
		size_t len = G.size();
		for(size_t i = 0; i < len && sets->getDisjointSetNum() > 1; i++){
			pair<T, pair<size_t, size_t> > cur = G[i];
			if(!sets->isSameSet(cur.second.first, cur.second.second)){
				mstCost += cur.first;
				sets->unionSets(cur.second.first, cur.second.second);
			}
		}
	}

	//Access minimum weight required, returns -1 if MST is invalid
	//If more than 1 disjoint sets, then the MST is invalid
	T getMSTCost(){
		return sets->getDisjointSetNum() == 1 ? mstCost : -1;
	}
};

int main(){
	//Enter code here
	return 0;
}