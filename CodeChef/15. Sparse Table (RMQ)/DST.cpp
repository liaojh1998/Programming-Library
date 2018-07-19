//Disjoint Sparse Table template
//https://discuss.codechef.com/questions/117696/tutorial-disjoint-sparse-table
//https://discuss.codechef.com/questions/116821/segprod-editorial
//https://en.wikipedia.org/wiki/Find_first_set - for clz (count leading zeros) function
#include <bits/stdc++.h>
using namespace std;

template<typename T> class DST{
private:
	int N, height;
	T** st;

	T func(const T& a, const T& b){
		return a * b;
	}

public:
	DST(const int& n){
		//Key things to know:
		//- The data must be immutable, in other words, there must be no changes to the data. (Same as sparse table)
		//- The function must be associative. Let O represent the function symbol, then, (a O b) O c = a O (b O c). (Same as sparse table)
		//Someday, maybe, explore the possibility of converting the processing such that function do not need to be associative (can apply order).
		//Key idea: For a segment [a, b) where it has size 2^k for some integer k, let M = (a + b)/2, st[k][i] for a <= i < M has suffixes of
		//continuous function calculation from i up to M. st[k][i] for M <= i < b has prefixes of continuous function calculation from M up to i.
		N = n;
		height = static_cast<int>(ceil(log2(N)))+1;
		st = new T*[height];
		for(int i = 0; i < height; i++)
			st[i] = new T[N+5];
	}
	~DST(){
		for(int i = 0; i < height; i++)
			delete[] st[i];
		delete[] st;
	}
	//Unlike the other sparse table and trees, this one is built from the bottom to the top.
	//In other words, we no longer use a concept called 'depth', rather, we use 'height'.
	//Example: segments of size 1 are at height 0, size 2 are at height 1, size 2^k are at height k.
	//Processing: O(N*log(N))
	void build(T *arr){
		//Size 1 case
		for(int i = 0; i < N; i++)
			st[0][i] = arr[i];
		//Size >1 cases
		for(int i = 1; i < height; i++){
			int size = 1 << i;
			int half = size >> 1;
			for(int j = half; j < N; j += size){ //Do not worry about missing cases of j + size >= N. It'll be accessed on the next higher height.
				//Suffixes
				st[i][j-1] = arr[j-1];
				int jsize = j-half;
				for(int k = j-2; k >= jsize; k--)
					st[i][k] = func(arr[k], st[i][k+1]);
				//Prefixes
				st[i][j] = arr[j];
				jsize = min(j+half, N);
				for(int k = j+1; k < jsize; k++)
					st[i][k] = func(st[i][k-1], arr[k]);
			}
		}
	}
	//Query: O(1)
	//On the interval [a, b], 0-based indexing
	T query(const int& a, const int& b){
		if(a == b)
			return st[0][a];
		int h = 32 - __builtin_clz(a^b); //Word size, or number of bits in int - count of leading zeros of a^b (Not 31 but 32 because I designated height 0 to length 1 intervals)
		return func(st[h][a], st[h][b]);
	}
	/*
	Theorem: All possible intervals are covered by the sparse table.
	Proof: See this sparse table from the top to the bottom.
	At the highest height, there exist a M = 2^k such that 0 < M < N. Then, for all possible a that 0 <= a < M and for all possible b that M <= b < N
	we can combine the suffixes and prefixes to create the interval [a, b).
	The problem arises when we have 0 <= b < M or M <= a < N, that's when there are no suffix or prefix to combine into the interval [a, b).
	This is where we move to the suffixes and prefixes below it, which must have an M_2 = 2^(k-1) such that 0 <= M_2 < M by the algorithm construction.
	Then, for 0 <= a, b < M and 0 <= a < M_2 and M_2 <= b < M, we can comine the suffixes and prefixes to create the interval [a, b).
	We can construct the similar idea on the cases where M <= a < N, because there can exist an M_3 = 2^(k-1) + 2^k.
	Otherwise, that case is skipped because we do not need an M_3 when M_3 >= N, which means interval at that segment must be smaller than M <= a, b < M_3.
	For those smaller cases, we will refer them to the sparse tables below the current height.
	Because the algorithm continuously propagate the same idea down the height until prefixes and suffixes of size 1, and there are no intervals with size less than 1,
	all possible intervals are covered by the sparse table.

	Theorem: The location of the first set bit of a^b is the height at which there must exist a unique M such that a <= M < b.
	Proof: I don't know for now, this remains to be verified.
	*/
};

int main(){
	//Enter code here
	return 0;
}