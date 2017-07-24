//(Strictly) Persistent Segment Tree template
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the persistent segment tree
template<typename T> class PST{
#define defval (0) //Default value for nodes
private:
	size_t N, states;
	static T queryfunc(const T& a, const T& b){
		return a + b;
	}
	static T applyfunc(const T& a, const T& b){
		return a + b;
	}
	//Nodes for the persistent segment tree
	struct node{
		node *l, *r;
		bool newl, newr;
		T val;

		node(const T& v): l(NULL), r(NULL), newl(false), newr(false){
			val = v;
		}
		node(const T& prev, const T& v): l(NULL), r(NULL), newl(false), newr(false){
			val = applyfunc(prev, v);
		}
		node(node *l, node *r, bool newl, bool newr): l(l), r(r), newl(newl), newr(newr), val(defval){
			val = queryfunc(l->val, r->val);
		}
		~node(){
			if(newl) delete l;
			if(newr) delete r;
		}
	};
	vector<node*> pst;
	node* build(T *arr, int l, int r){
		if(l == r) return new node(arr[l]);
		int m = (l+r)>>1;
		return new node(build(arr, l, m), build(arr, m+1, r), true, true);;
	}
	node* init_build(int l, int r){
		if(l == r) return new node(defval);
		int m = (l+r)>>1;
		return new node(init_build(l, m), init_build(m+1, r), true, true);
	}
	node* update(node* cur, const int& pos, int l, int r, const T& val){
		if(l == r) return new node(cur->val, val);
		int m = (l+r)>>1;
		return (pos <= m) ? new node(update(cur->l, pos, l, m, val), cur->r, true, false) : new node(cur->l, update(cur->r, pos, m+1, r, val), false, true);
	}
	T query(node* cur, int ql, int qr, int l, int r){
		if(ql == l && qr == r) return cur->val;
		int m = (l+r)>>1;
		T ans = defval;
		if(m >= ql) ans = queryfunc(query(cur->l, ql, qr < m ? qr : m, l, m), ans);
		if(m+1 <= qr) ans = queryfunc(ans, query(cur->r, ql > m+1 ? ql : m+1, qr, m+1, r));
		return ans;
	}
	node* revert(node* cur, node* prev, int ql, int qr, int l, int r){ //Needs check
		if(ql == l && qr == r) return new node(prev->l, prev->r, false, false);
		int m = (l+r)>>1;
		if(m > qr) return new node(revert(cur->l, prev->l, ql, qr, l, m), cur->r, true, false);
		if(m+1 < ql) return new node(cur->l, revert(cur->r, prev->r, ql, qr, m+1, r), false, true);
		return new node(revert(cur->l, prev->l, ql, m, l, m), revert(cur->r, prev->r, m+1, qr, m+1, r), true, true);
	}

public:
	//0-based indexing
	PST(const size_t& n){
		N = n;
		states = 0;
	}
	~PST(){
		for(int i = 0; i < states; i++)
			delete pst[i];
	}
	//Creates a completely new segment tree state using values from arr
	void build(T *arr){
		pst.push_back(build(arr, 0, N-1));
		states++;
	}
	//Create a completely new segment tree state with default values
	void init(){
		pst.push_back(init_build(0, N-1));
		states++;
	}
	//Get current number of states
	int numStates(){
		return states;
	}
	//Update, generates a new state from a previous state; make sure prev is accessible
	void update(int prev, int pos, const T& val){
		pst.push_back(update(pst[prev], pos, 0, N-1, val));
		states++;
	}
	//Query from a specific state, [ql, qr]
	T query(int state, int ql, int qr){
		if(ql > qr) return defval;
		return query(pst[state], ql, qr, 0, N-1);
	}
	//Crazy function below, prepare yourself!
	//Revert, generates a new state with a range of a state reverted into a range of a previous state (in log(N) time!)
	//Of course, can also generate a new state with a range of a state fastforwarded into a range of a future state
	//Please make sure l <= r
	void revert(int state, int prev, int l, int r){
		pst.push_back(revert(pst[state], pst[prev], l, r, 0, N-1));
		states++;
	}
};

int main(){
	//Enter code here
	return 0;
}