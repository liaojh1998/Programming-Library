//Segment Tree Reversed functions template
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
	T& operator[](size_t i){
		return sgt[i + (1<<height)];
	}
	
	//Modification on an interval, *single element access*
	//Update: O(logN)
	void update(size_t l, size_t r, const T& value){
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1){
			if(l&1) sgt[l] = applyfunc(sgt[l++], value);
			if(r&1) sgt[--r] = applyfunc(sgt[r], value);
		}
	}
	//Query [p]
	//Access: O(logN)
	T query(size_t pos){
		T res = 0; //Set initial value
		for(pos += (1<<height); pos > 1; pos >>= 1)
			res = queryfunc(sgt[pos], res);
		return res;
	}
	//If we need to push all modifications to the bottom to inspect every single element
	//We can do this in O(N) time
	void push(){
		size_t len = 1<<height;
		for(size_t i = 1; i < len; i++){
			sgt[i<<1] = applyfunc(sgt[i<<1], sgt[i]);
			sgt[i<<1|1] = applyfunc(sgt[i<<1|1], sgt[i]);
			sgt[i] = 0; //Remove modification
		}
	}
};

int main(){
	//Enter code here
	return 0;
}
