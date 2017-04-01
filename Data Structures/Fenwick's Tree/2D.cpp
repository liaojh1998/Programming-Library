//2D Fenwick's Tree template
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the fenwick's tree
template<typename T> class FenTree{
private:
	//Set array to static if using C++11
	T* fwt;
	size_t N, M;
	//N, M is useful if possibility of querying out of range

	//Functions that relates child to parent in the segment tree
	//This example apply sum
	T applyfunc(const T& a, const T& b){
		return a + b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	T reversefunc(const T& a, const T& b){
		//For the access, reverse of queryfunc
		return a - b;
	}

public:
	//Useful functions
	//Constructor, n - row, m - columns
	FenTree(size_t n, size_t m){
		N = n + 1;
		M = m + 1;
		fwt = new T[N * M]();
	}
	//Destructor
	~FenTree(){
		delete[] fwt;
	}

	//All access, update, return functions begins at original index of 0, but fenwick tree index start at 1
	//Example calculates prefix sum from 0 to i

	//Read the actual number at position i row, j column
	//Runtime: O(c*logN*logM) where c < 1
	//Delete rows before column deletion
	//This is better than Query twice
	T access(size_t i, size_t j){
		T ans = fwt[(i+1)*M+j+1];
		for(size_t tempi = i, nexti = i & (i + 1); tempi > nexti; tempi &= (tempi - 1))
			ans = reversefunc(ans, fwt[tempi*M + j+1]);
		for(size_t nextj = j & (j + 1); j > nextj; j &= (j - 1)){
			//Since all rows have been removed, all we need to remove is the rows of each columns
			//and then remove the leftover column frequency
			T cur = fwt[(i+1)*M + j];
			for(size_t tempi = i, nexti = tempi & (tempi + 1); tempi > nexti; tempi &= (tempi - 1))
				cur = reversefunc(cur, fwt[tempi*M + j]);
			ans = reversefunc(ans, cur);
		}
		return ans;
	}
	//Update prefix sum of matrix from 0 to i row and 0 to j columns
	//Runtime: O(logN*logM)
	void update(size_t i, size_t j, T value){
		//value -= access(i, j); //If update is based on assignment
		for(i++; i < N; i += (i & -i))
			for(size_t tempj = j+1; tempj < M; tempj += (tempj & -tempj))
				fwt[i*M+tempj] = applyfunc(fwt[i*M+tempj], value);
	}
	//Query matrix sum of [0, i] rows and [0, j] columns
	//If specific matrix sum from [i, j] row and [k, l] column: query(j, l) - query(i-1, l) - query(k-1, j) + query(i-1, k-1);
	//Runtime: O(logN*logM)
	T query(size_t i, size_t j){
		T ans = 0;
		for(i++; i; i &= (i - 1))
			for(size_t tempj = j+1; tempj; tempj &= (tempj - 1))
				ans = queryfunc(ans, fwt[i*M+tempj]);
		return ans;
	}
};

int main(){
	//Enter code here
	return 0;
}