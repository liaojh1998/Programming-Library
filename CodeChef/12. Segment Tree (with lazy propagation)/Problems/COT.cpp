#include <bits/stdc++.h>
using namespace std;

template<typename T> class PST{
#define defval (0)
private:
	size_t N, states;
	static T queryfunc(const T& a, const T& b){
		return a + b;
	}
	static T applyfunc(const T& a, const T& b){
		return a + b;
	}
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
	T query(node *u, node *v, node *lca, node *plca, int l, int r, int k){
		if(l == r) return l;
		int cur = u->l->val + v->l->val - lca->l->val - plca->l->val, m = (l+r)>>1;
		if(cur < k) return query(u->r, v->r, lca->r, plca->r, m+1, r, k-cur);
		return query(u->l, v->l, lca->l, plca->l, l, m, k);
	}

public:
	PST(const size_t& n){
		N = n;
		states = 0;
	}
	~PST(){
		for(int i = 0; i < states; i++)
			delete pst[i];
	}
	void init(){
		pst.push_back(init_build(0, N-1));
		states++;
	}
	int numStates(){
		return states;
	}
	int update(int prev, int pos, const T& val){
		pst.push_back(update(pst[prev], pos, 0, N-1, val));
		states++;
		return states-1;
	}
	T query(int u, int v, int lca, int plca, int k){
		return query(pst[u], pst[v], pst[lca], pst[plca], 0, N-1, k);
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

void dfs(const int& u, int *depth, int *num, unordered_map<int, int> &m, vector<int> *edges, int *rootnum, int *parent, PST<int> &pst){
	rootnum[u] = pst.update(rootnum[parent[u]], m[num[u]], 1);
	int size = edges[u].size(), v;
	for(int i = 0; i < size; i++){
		v = edges[u][i];
		if(v != parent[u]){
			parent[v] = u;
			depth[v] = depth[u]+1;
			dfs(v, depth, num, m, edges, rootnum, parent, pst);
		}
	}
}
void FastIO::solve(){
	//This problem can really be solved with HLD with Segment Tree with Merge Sort I think (honestly that's probably TLE), but to solve it using Persistent Segment Tree alone like in Anudeep's blog is real interesting
	//Here, the depth is used to give LCA, and the query helps to count which number is the kth number under coordinate compression from root to node
	int N, M, t, u, v, k, a, b, log, LCA;
	readInt(N);
	readInt(M);
	int arr[N], num[N+1];
	for(int i = 0; i < N; i++){
		readInt(arr[i]);
		num[i+1] = arr[i];
	}
	//N*log(N)
	sort(arr, arr+N);
	unordered_map<int, int> m;
	for(int i = 0; i < N; i++)
		m[arr[i]] = i;
	PST<int> pst(N);
	pst.init();
	vector<int> edges[N+1];
	for(int i = 0; i < N-1; i++){
		readInt(u);
		readInt(v);
		edges[u].push_back(v);
		edges[v].push_back(u);
	}
	int depth[N+1], rootnum[N+1], parent[N+1];
	depth[1] = 0;
	parent[1] = 0;
	rootnum[0] = 0;
	//Gotta be the biggest kind of dfs I've ever seen, arbitrary 1 as root
	//N*log(N)
	dfs(1, depth, num, m, edges, rootnum, parent, pst);
	//LCA dp
	int d = 0;
	while((1 << d) <= N) d++;
	int dp[N+1][d];
	dp[0][0] = 0;
	for(int i = 1; i <= N; i++)
		dp[i][0] = parent[i];
	//N*log(N)
	for(int i = 1; (1 << i) < N; i++)
		for(int j = 0; j <= N; j++)
			dp[j][i] = dp[dp[j][i-1]][i-1];
	//M*(log(N)+log(N))
	for(int i = 0; i < M; i++){
		readInt(u);
		readInt(v);
		readInt(k);
		log = 0;
		if(depth[u] > depth[v]){
			b = u;
			a = v;
		}else{
			a = u;
			b = v;
		}
		while((1 << (log+1)) <= depth[b]) log++;
		for(int i = log; i >= 0; i--)
			if(depth[b] - (1 << i) >= depth[a])
				b = dp[b][i];
		if(a == b)
			LCA = a;
		else{
			for(int i = log; i >= 0; i--)
				if(dp[a][i] != 0 && dp[a][i] != dp[b][i]){
					a = dp[a][i];
					b = dp[b][i];
				}
			LCA = parent[a];
		}
		printf("%d\n", arr[pst.query(rootnum[u], rootnum[v], rootnum[LCA], rootnum[parent[LCA]], k)]);
	}
	//Truly (N+M)*log(N), 2.54 seconds runtime
}