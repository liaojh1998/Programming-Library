//(Strictly) Persistent Segment Tree template
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the persistent segment tree
template<typename T> class PST{
#define defval (0) //Default values for segment tree
private:
	size_t N, states, *lnode, *rnode, nodes;
	T *pst;
	vector<size_t> pstroot;
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	T applyfunc(const T& a, const T& b){
		return a + b;
	}
	size_t build(T *arr, int l, int r){
		if(l == r)
			pst[nodes] = arr[l];
		else{
			int m = (l+r)>>1;
			size_t left = build(arr, l, m), right = build(arr, m+1, r);
			lnode[nodes] = left;
			rnode[nodes] = right;
			pst[nodes] = queryfunc(pst[lnode[nodes]], pst[rnode[nodes]]);
		}
		return nodes++;
	}
	size_t init_build(int l, int r){
		if(l == r)
			pst[nodes] = defval;
		else{
			int m = (l+r)>>1;
			size_t left = init_build(l, m), right = init_build(m+1, r);
			lnode[nodes] = left;
			rnode[nodes] = right;
			pst[nodes] = queryfunc(pst[lnode[nodes]], pst[rnode[nodes]]);
		}
		return nodes++;
	}
	size_t update(const size_t& node, const int& pos, int l, int r, const T& val){
		if(l == r)
			pst[nodes] = applyfunc(pst[node], val);
		else{
			int m = (l+r)>>1;
			if(pos <= m){
				size_t t = update(lnode[node], pos, l, m, val);
				lnode[nodes] = t;
				rnode[nodes] = rnode[node];
			}else{
				size_t t = update(rnode[node], pos, m+1, r, val);
				rnode[nodes] = t;
				lnode[nodes] = lnode[node];
			}
			pst[nodes] = queryfunc(pst[lnode[nodes]], pst[rnode[nodes]]);
		}
		return nodes++;
	}
	T query(const size_t& node, int ql, int qr, int l, int r){
		if(ql == l && qr == r) return pst[node];
		int m = (l+r)>>1;
		T ans = defval;
		if(m >= ql) ans = queryfunc(query(lnode[node], ql, qr < m ? qr : m, l, m), ans);
		if(m+1 <= qr) ans = queryfunc(ans, query(rnode[node], ql > m+1 ? ql : m+1, qr, m+1, r));
		return ans;
	}
	size_t revert(const size_t& node, const size_t& prev, int ql, int qr, int l, int r){
		if(ql == l && qr == r) return prev;
		int m = (l+r)>>1;
		if(m >= qr){
			size_t t = revert(lnode[node], lnode[prev], ql, qr, l, m);
			lnode[nodes] = t;
			rnode[nodes] = rnode[prev];
		}else if(m+1 <= ql){
			size_t t = revert(rnode[node], rnode[prev], ql, qr, m+1, r);
			rnode[nodes] = t;
			lnode[nodes] = lnode[prev];
		}else{
			size_t tl = revert(lnode[node], lnode[prev], ql, m, l, m), tr = revert(rnode[node], rnode[prev], m+1, qr, m+1, r);
			lnode[nodes] = tl;
			rnode[nodes] = tr;
		}
		pst[nodes] = queryfunc(pst[lnode[nodes]], pst[rnode[nodes]]);
		return nodes++;
	}

public:
	//0-based indexing
	PST(const size_t& n, const size_t& mul){
		N = n;
		//Call either build or init, because none of these values are correctly initialized
		//Usually faster than the nodes version due to the lessor amount of memory it uses and already initialized memory
		size_t log = 0;
		while((1 << log) < N) log++;
		pst = new T[mul*log*N]; //mul is the memory multiplier, 2 usually suffice if query only uses query, 4 if query has updates, super safe would be 8 (but don't go overboard with running out of RAM)
		lnode = new size_t[mul*log*N];
		rnode = new size_t[mul*log*N];
		states = 0;
		nodes = 0;
	}
	~PST(){
		delete[] pst;
		delete[] lnode;
		delete[] rnode;
	}
	//Creates a completely new segment tree state using values from arr
	void build(T *arr){
		pstroot.push_back(build(arr, 0, N-1));
		states++;
	}
	//Create a completely new segment tree state with default values
	void init(){
		pstroot.push_back(init_build(0, N-1));
		states++;
	}
	//Get current number of states
	int numStates(){
		return states;
	}
	//Get current number of nodes used
	int numNodes(){
		return nodes;
	}
	//Update, generates a new state from a previous state; make sure prev is accessible
	void update(int prev, int pos, const T& val){
		pstroot.push_back(update(pstroot[prev], pos, 0, N-1, val));
		states++;
	}
	//Query from a specific state, [ql, qr]
	T query(int state, int ql, int qr){
		if(ql > qr) return defval;
		return query(pstroot[state], ql, qr, 0, N-1);
	}
	//Revert, generates a new state with a range of a state reverted into a range of a previous state
	//Of course, can also generate a new state with a range of a state fastforwarded into a range of a future state
	//Please make sure l <= r
	void revert(int state, int prev, int l, int r){
		pstroot.push_back(revert(pstroot[state], pstroot[prev], l, r, 0, N-1));
		states++;
	}
};

int main(){
	//Enter code here
	return 0;
}