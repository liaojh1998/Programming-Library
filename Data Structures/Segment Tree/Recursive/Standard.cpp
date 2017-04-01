//Segment Tree template
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the segment tree
template<typename T> class SegTree{
#define defval (0) //May be changed for purposes such as maximum range query, currently used for sum
private:
	//Set array to static if using C++11
	T* sgt;
	T* arr;
	size_t N;
	//N is useful if possibility of querying out of range
	
	//Functions that relates child to parent in the segment tree
	//Important order of procedence, such as multiple and division, will not work
	//Non-commutative functions do work, such as subtraction, addition, max, and min
	//This example apply sum
	T applyfunc(const T& a, const T& b){
		return b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	
	//Building function
	T push(size_t node, size_t l, size_t r){
		return (l^r) ? (sgt[node] = queryfunc(push(node<<1, l, (l+r)/2), push(node<<1|1, (l+r)/2+1, r))) : sgt[node] = applyfunc(sgt[node], arr[l]);
	}
	//Update function
	void update(size_t node, size_t l, size_t r, size_t pos, const T& value){
		if(l^r){
			size_t m = (l+r)/2;
			if(pos > m)
				update(node<<1|1, m+1, r, pos, value);
			else
				update(node<<1, l, m, pos, value);
			sgt[node] = queryfunc(sgt[node<<1], sgt[node<<1|1]);
		}else
			sgt[node] = applyfunc(sgt[node], value);
	}
	//Query function
	T query(size_t node, size_t ql, size_t qr, size_t l, size_t r){
		if(ql > r || qr < l || r < l) return defval;
		size_t m = (l+r)/2;
		return ((ql^l) | (qr^r)) ? queryfunc(query(node<<1, ql, min(qr, m), l, m), query(node<<1|1, max(ql, m+1), qr, m+1, r)) : sgt[node];
	}

public:
	//Useful functions
	//Constructor, n - size of the array
	//This is the non-space saving, no-recursion version
	SegTree(size_t n){
		N = n;
		sgt = new T[(1<<(size_t)ceil(log2(N))) + N]();
		arr = new T[N]();
		//Set correct initial values at each leaf when needed
		//For example, min require infinity for each leaf
	}
	//Destructor
	~SegTree(){
		delete[] sgt;
		delete[] arr;
	}
	//Array access
	T& operator[](size_t i){
		return arr[i];
	}
	
	//If read values directly into segment tree, then we may instantly build
	//O(N)
	void build(){
		push(1, 0, N-1);
	}
	//Modification on an element, *interval access*
	//Update: O(logN)
	void update(size_t pos, const T& value){
		if(pos < 0 || pos >= N) return; //Not possible
		arr[pos] = applyfunc(arr[pos], value);
		update(1, 0, N-1, pos, value);
	}
	//Query [l, r]
	//Access: O(logN)
	T query(size_t l, size_t r){
		return query(1, l, r, 0, N-1);
	}
};

int main(){
	//Enter code here
	return 0;
}
