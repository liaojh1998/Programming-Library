//Segment Tree template
//http://codeforces.com/blog/entry/18051?
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the segment tree
template<typename T> class SegTree{
private:
	//Set array to static if using C++11
	T* sgt;
	size_t N, height;
	//N is useful if possibility of querying out of range

	//Functions that relates child to parent in the segment tree
	//Important order of procedence, such as multiple and division, will not work
	//Non-commutative functions do work, such as subtraction, addition, max, and min
	//This example apply sum
	T applyfunc(const T& a, const T& b){
		return a + b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}

public:
	//Useful functions
	//Constructor, n - size of the array
	//This is the non-space saving, no-recursion version
	SegTree(size_t n){
		N = n;
		height = (size_t)ceil(log2(N));
		sgt = new T[1<<(height+1)]();
		//Set correct initial values at each leaf when needed
		//For example, min require infinity for each leaf
	}
	//Destructor
	~SegTree(){
		delete[] sgt;
	}
	//Array access
	T& operator[](const size_t& i){
		return sgt[i + (1<<height)];
	}

	//If read values directly into segment tree, then we may instantly build
	//O(N)
	void build(){
		for(size_t i = ((1<<height)-1); i > 0; i--)
			sgt[i] = queryfunc(sgt[i<<1], sgt[i<<1|1]);
	}
	//Modification on an element, *interval access*
	//Update: O(logN)
	void update(size_t pos, const T& value){
		if(pos < 0 || pos >= N) return; //Not possible
		for(sgt[(pos + (1<<height))] = applyfunc(sgt[(pos += (1<<height))], value); pos > 1; pos >>= 1)
			sgt[pos>>1] = queryfunc(sgt[pos], sgt[pos^1]);
	}
	//Query [l, r)
	//Access: O(logN)
	T query(size_t l, size_t r){
		if(!((l+1)^r)) return (*this)[l];
		T resl = 0, resr = 0; //Set initial values
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1){
			if(l&1) resl = queryfunc(resl, sgt[l++]);
			if(r&1) resr = queryfunc(sgt[--r], resr);
		}
		return queryfunc(resl, resr);
	}
};

int main(){
	//Enter code here
	return 0;
}
