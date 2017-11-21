//Segment Tree Lazy Propagation template
//This template is modeled after Flipping Coins problem in CodeChef
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the segment tree
template<typename T> class SegTree{
private:
	//Set array to static if using C++11
	T* sgt;
	T* lazy;
	size_t N, height;
	//N is useful if possibility of querying out of range
	
	//Functions that relates child to parent in the segment tree
	//This example apply sum
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	//Queries for min
	/*
	T queryfunc(const T& a, const T& b){
		return a < b ? a : b;
	}
	*/
	//Lazy to unlazy
	//Flipping Coins had ^ relation which changed a + b to b - a when upward propagate
	T applyfunc(const T& a, const T& b){
		return b - a;
	}
	//Downward propagate relation
	//This replaces the applyfunc of the standard segment tree
	T propfunc(const T& a, const T& b){
		//Increment or assignment works
		//If increment, return a+1, can queries for maximum by queryfunc reverse of min
		//If assignment, return b, can queries for sum
		//If addition: return a + b
		return a ^ b;
	}

public:
	//Useful functions
	//Constructor, n - size of the array
	SegTree(size_t n){
		N = n;
		height = (size_t)ceil(log2(N));
		sgt = new T[1<<(height+1)]();
		lazy = new T[1<<height]();
		//Set correct initial values at each leaf when needed
		//For example, min require infinity for each leaf
	}
	//Destructor
	~SegTree(){
		delete[] sgt;
		delete[] lazy;
	}
	//Array access
	T& operator[](size_t i){
		return sgt[i + (1<<height)];
	}

	//Lazy propagation
	//Lazy calculate
	//Change k to 1 if length doesn't matter (case when assignment, not summed queries)
	void calc(size_t pos, size_t k){
		if(lazy[pos]) sgt[pos] = applyfunc(queryfunc(sgt[pos<<1], sgt[pos<<1|1]), lazy[pos]*k); //Change all applyfunc if sum
		else sgt[pos] = queryfunc(sgt[pos<<1], sgt[pos<<1|1]);
	}
	//Propagate function
	void propagate(size_t pos, const T& value, size_t k){
		sgt[pos] = applyfunc(sgt[pos], value*k);
		if(pos < (1<<height)) lazy[pos] = propfunc(lazy[pos], value);
	}
	//If read values directly into segment tree, then we may instantly build
	//O(N)
	void build(){
		for(size_t i = ((1<<height)-1); i > 0; i--)
			sgt[i] = queryfunc(sgt[i<<1], sgt[i<<1|1]);
	}
	//Propagating back upward in a range [l, r)
	void build(size_t l, size_t r){
		size_t k = 2; //If k doesn't matter, set k = 1 (k only matters when summing required)
		for(l = ((l+(1<<height))>>1), r = ((r+(1<<height)-1)>>1); l > 1; k <<= 1, l >>= 1, r >>= 1) //If k doesn't matter, delete k change
			for(size_t i = r; i >= l; i--) calc(i, k);
	}
	//Downward propagation in a range [l, r)
	void push(size_t l, size_t r){
		size_t p = height, k = 1 << (height-1); //Set k = 1 if k doesn't matter
		for(l += (1<<height), r += (1<<height)-1; p > 0; p--, k >>= 1) //Delete k change if k doesn't matter
			for(size_t i = l >> p; i <= r >> p; i++)
				if(lazy[i]){
					propagate(i<<1, lazy[i], k);
					propagate(i<<1|1, lazy[i], k);
					lazy[i] = 0;
				}
	}
	//Modify [l, r)
	void update(size_t l, size_t r, const T& value){
		if(l == r || !value) return;
		push(l, l + 1);
		push(r - 1, r);
		bool appl = false, appr = false;
		size_t k = 1;
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1, k <<= 1){ //Delete change to k if k doesn't matter
			if(appl) calc(l - 1, k);
			if(appr) calc(r, k);
			if(l&1) propagate(l++, value, k), appl = true;
			if(r&1) propagate(--r, value, k), appr = true;
		}
		for(--l; r > 0; l >>= 1, r >>= 1, k <<= 1){ //Leftover propagation if needed, delete k if it doesn't matter
			if(appl) calc(l, k);
			if(appr && (!appl || l != r)) calc(r, k);
		}
	}
	//Query [l, r)
	T query(size_t l, size_t r){
		push(l, l + 1);
		push(r - 1, r);
		T res = 0; //Set initial value
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1){
			if(l&1) res = queryfunc(res, sgt[l++]);
			if(r&1) res = queryfunc(sgt[--r], res);
		}
		return res;
	}
};

int main(){
	//Enter code here
	return 0;
}
