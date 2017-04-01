//2D Segment Tree template
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the segment tree
template<typename T> class SegTree{
private:
	//Set array to static if using C++11
	T* sgt;
	size_t N, M, Nheight, Mheight;
	//N, M is useful if possibility of querying out of range
	
	//Functions that relates child to parent in the segment tree
	//Important order of procedence, such as multiple and division, will not work
	//Non-commutative functions do work, such as subtraction, addition, max, and min
	//This example apply sum
	T applyfunc(const T& a, const T& b){
		//If assignment just return b
		return a + b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}

public:
	//Useful functions
	//Constructor, 2D version, n rows and m columns, or rows = y, columns = x
	//This is the non-space saving, non-recursion version
	SegTree(size_t n, size_t m){
		N = n;
		M = m;
		Nheight = (size_t)ceil(log2(N));
		Mheight = (size_t)ceil(log2(M));
		sgt = new T[1<<(Nheight+Mheight+2)]();
		//Set correct initial values at each leaf when needed
		//For example, min require infinity for each leaf
	}
	//Destructor
	~SegTree(){
		delete[] sgt;
	}
	//Array access
	T& access(size_t i, size_t j){
		return sgt[(i + (1<<Nheight))*(1<<(Mheight+1)) + (j+(1<<Mheight))];
	}

	//If read values directly into segment tree, then we may instantly build
	//The idea of 2D segment tree is designed as Quad Tree
	//Build rows before we build columns
	//O(N*M)
	void build(){
		size_t Msize = 1<<(Mheight+1), minM = 1<<Mheight;
		for(size_t j = Msize-1; j >= minM; j--)
			for(size_t i = minM-1; i > 0; i--)
				sgt[i*Msize + j] = queryfunc(sgt[(i<<1)*Msize + j], sgt[(i<<1|1)*Msize + j]);
		for(size_t i = ((1<<(Nheight+1))-1); i > 0; i--)
			for(size_t j = minM-1; j > 0; j--)
				sgt[i*Msize + j] = queryfunc(sgt[i*Msize + (j<<1)], sgt[i*Msize + (j<<1|1)]);
	}
	//Build initial row before upward rows
	//Update: O(logNlogM)
	void update(size_t r, size_t c, const T& value){
		if(r < 0 || r >= N || c < 0 || c >= M) return; //Not possible
		size_t Msize = 1<<(Mheight+1), minM = 1<<Mheight;
		r += 1<<(Nheight);
		sgt[r*Msize + c + minM] = applyfunc(sgt[r*Msize + c + minM], value);
		for(size_t tempc = (c + minM)>>1; tempc > 0; tempc >>= 1)
			sgt[r*Msize + tempc] = queryfunc(sgt[r*Msize + (tempc<<1)], sgt[r*Msize + (tempc<<1|1)]);
		for(r >>= 1; r > 0; r >>= 1){
			sgt[r*Msize + c + minM] = queryfunc(sgt[(r<<1)*Msize + c + minM], sgt[(r<<1|1)*Msize + c + minM]);
			for(size_t tempc = (c + minM)>>1; tempc > 0; tempc >>= 1)
				sgt[r*Msize + tempc] = queryfunc(sgt[r*Msize + (tempc<<1)], sgt[r*Msize + (tempc<<1|1)]);
		}
	}
	//Query ([rowl, rowr), [columnl, columnr))
	//Break apart rows and calculate columns left right first before calculate rows up down
	//Access: O(logNlogM)
	T query(size_t rl, size_t rr, size_t cl, size_t cr){
		if(!((rl+1)^rr) && !((cl+1)^cr)) return access(rl, cl);
		size_t Msize = 1<<(Mheight+1);
		T resl = 0, resr = 0; //Set initial values
		for(rl += (1<<Nheight), rr += (1<<Nheight); rl < rr; rl >>= 1, rr >>= 1){
			T resll = 0, reslr = 0, resrl = 0, resrr = 0;
			if(rl&1){
				for(size_t templ = cl + (1<<Mheight), tempr = cr + (1<<Mheight); templ < tempr; templ >>= 1, tempr >>= 1){
					if(templ&1) resll = queryfunc(resll, sgt[rl*Msize + templ++]);
					if(tempr&1) reslr = queryfunc(sgt[rl*Msize + --tempr], reslr);
				}
				resl = queryfunc(resl, queryfunc(resll, reslr));
				rl++;
			}
			if(rr&1){
				--rr;
				for(size_t templ = cl + (1<<Mheight), tempr = cr + (1<<Mheight); templ < tempr; templ >>= 1, tempr >>= 1){
					if(templ&1) resrl = queryfunc(resrl, sgt[rr*Msize + templ++]);
					if(tempr&1) resrr = queryfunc(sgt[rr*Msize + --tempr], resrr);
				}
				resr = queryfunc(queryfunc(resrl, resrr), resr);
			}
		}
		return queryfunc(resl, resr);
	}
};

int main(){
	//Enter code here
	return 0;
}
