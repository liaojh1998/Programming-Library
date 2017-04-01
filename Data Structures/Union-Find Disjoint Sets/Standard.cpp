//Union-Find Disjosize_t-Sets
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

int main(){
	//Enter code here
	return 0;
}