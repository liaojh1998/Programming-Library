//Segment Tree Lazy Propagation template
//Made during the 2017 ICPC Southern Central America Regionals, now modified for just the sum example
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the segment tree
template<typename T> class SegTree{
#define defval (0)
private:
	T* sgt;
	T* arr;
	T* lazy;
	size_t N;
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
	
	//Lazy propagation functions below
	//Propagation function, lazy to lazy
	T propfunc(const T& a, const T& b){
		return a + b;
	}
	//Propagate downward in the lazy array
	void propagate(size_t node, size_t l, size_t r){
		if(l^r){
			lazy[node<<1] = propfunc(lazy[node<<1], lazy[node]);
			lazy[node<<1|1] = propfunc(lazy[node<<1|1], lazy[node]);
		}
		lazy[node] = 0;
	}
	//Make a node from lazy to not lazy
	void unlazy(size_t node, size_t l, size_t r){
		if(lazy[node]){
			sgt[node] = applyfunc(sgt[node], lazy[node]*(r-l+1));
			propagate(node, l, r);
		}
	}
	
	//Building function
	void build(size_t node, size_t l, size_t r){
		if(l^r){
			build(node<<1, l, (l+r)/2);
			build(node<<1|1, (l+r)/2+1, r);
			sgt[node] = queryfunc(sgt[node<<1], sgt[node<<1|1]);
		}else
			sgt[node] = applyfunc(sgt[node], arr[l]);
	}
	//Update function
	void update(size_t node, size_t ul, size_t ur, size_t l, size_t r, const T& value){
		if((l <= ul && r >= ur) || r < ul || l > ur){
			if(l <= ul && r >= ur)
				lazy[node] = propfunc(lazy[node], value);
			unlazy(node, ul, ur);
		}else{
			if(lazy[node])
				propagate(node, ul, ur);
			size_t m = (ul+ur)/2;
			update(node<<1, ul, m, l, r, value);
			update(node<<1|1, m+1, ur, l, r, value);
			sgt[node] = queryfunc(sgt[node<<1], sgt[node<<1|1]);
		}
	}
	//Query function
	T query(size_t node, size_t ql, size_t qr, size_t l, size_t r){
		if(l > qr || r < ql || r < l)
			return defval;
		unlazy(node, ql, qr);
		if(!((ql^l) | (qr^r)))
			return sgt[node];
		size_t m = (ql+qr)/2;
		return queryfunc(query(node<<1, ql, m, l, min(r, m)), query(node<<1|1, m+1, qr, max(l, m+1), r));
	}

public:
	//Useful functions
	//Constructor, n - size of the array
	//This is the recursive version
	//Range 0 - N-1
	SegTree(size_t n){
		N = n;
		sgt = new T[(1<<((size_t)ceil(log2(N))+1))+5]();
		lazy = new T[(1<<((size_t)ceil(log2(N))+1))+5]();
		//Set correct initial values at each leaf when needed
		//For example, min require infinity for each leaf
		//fill_n(sgt, (1<<(size_t)ceil(log2(N))) + N, defval);
		arr = new T[N+5]();
	}
	//Destructor
	~SegTree(){
		delete[] sgt;
		delete[] arr;
		delete[] lazy;
	}
	//Array access, THIS DOES NOT PROVIDE O(1) CALCULATION OF A LEAF, only used for initial build
	T& operator[](size_t i){
		return arr[i];
	}
	
	//If read values directly into segment tree, then we may instantly build
	//O(N)
	void build(){
		build(1, 0, N-1);
	}
	//Modification on a range, [l, r]
	//Update: O(logN)
	void update(size_t l, size_t r, const T& value){
		if(l > r || l < 0 || r > N-1) return; //Avoiding dangerous cases
		update(1, 0, N-1, l, r, value); //Range 0 - N-1 may be modified if needed
	}
	//Query [l, r]
	//Access: O(logN)
	T query(size_t l, size_t r){
		if(r < l) return defval; //Avoiding dangerous cases
		return query(1, 0, N-1, l, r); //Range 0 - N-1 may be modified if needed
	}
};

int main(){
	//Enter code here
	return 0;
}
