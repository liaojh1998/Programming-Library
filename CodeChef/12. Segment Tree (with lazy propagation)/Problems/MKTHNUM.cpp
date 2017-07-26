#include <bits/stdc++.h>
using namespace std;

template<typename T> class PST{
#define defval (0)
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
	int query(const size_t& u, const size_t& v, int l, int r, int k){
		if(l == r) return l;
		int m = (l+r)>>1, val = pst[lnode[v]] - pst[lnode[u]];
		if(val < k) return query(rnode[u], rnode[v], m+1, r, k-val);
		return query(lnode[u], lnode[v], l, m, k);
	}

public:
	PST(const size_t& n, const size_t& mul){
		N = n;
		size_t log = 0;
		while((1 << log) < N) log++;
		pst = new T[mul*log*N];
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
	void init(){
		pstroot.push_back(init_build(0, N-1));
		states++;
	}
	int update(int prev, int pos, const T& val){
		pstroot.push_back(update(pstroot[prev], pos, 0, N-1, val));
		return states++;
	}
	T query(const int& u, const int& v, int k){
		return query(pstroot[u], pstroot[v], 0, N-1, k);
	}
};

class FastIO{
private:
	int readInt(int &n){
		register int c;
		n = 0;
		bool neg = false;
		c = getchar();
		if(!(~c)) return -1;
		for(; ((c < 48 || c > 57)) && c != '-' && ~c; c = getchar());
		if(c == '-') neg = true, c = getchar();
		for(; c > 47 && c < 58 && ~c; c = getchar()){n = (n<<1)+(n<<3)+c-48;}
		if(neg) n = -n;
		return 1;
	}

public:
	FastIO(bool useFile = false){
		if(useFile){
			freopen("input.txt", "r", stdin);
			freopen("output.txt", "w", stdout);
		}
	}

	void solve();
};

int main(){
	FastIO fio;
	fio.solve();
	return 0;
}

void FastIO::solve(){
	//Binary search during queries reduce log^2(N) of Merge Sort Segment Tree to simply log(N) in Persistent Segment TRee
	int N, M;
	readInt(N);
	readInt(M);
	int arr[N], sorted[N], state[N+1];
	for(int i = 0; i < N; i++){
		readInt(arr[i]);
		sorted[i] = arr[i];
	}
	sort(sorted, sorted+N);
	unordered_map<int, int> compress;
	for(int i = 0; i < N; i++)
		compress[sorted[i]] = i;
	PST<int> pst(N, 2);
	pst.init();
	state[0] = 0;
	for(int i = 1; i <= N; i++)
		state[i] = pst.update(i-1, compress[arr[i-1]], 1);
	int u, v, k;
	for(int i = 0; i < M; i++){
		readInt(u);
		readInt(v);
		readInt(k);
		printf("%d\n", sorted[pst.query(state[u-1], state[v], k)]);
	}
}