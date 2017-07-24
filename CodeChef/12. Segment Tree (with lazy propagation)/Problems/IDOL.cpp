#include <bits/stdc++.h>
using namespace std;

template<typename T> class SegTree{
private:
	T* sgt;
	size_t N, height;

	void applyfunc(T& a, const int& b){
		a.first = b;
	}
	T queryfunc(const T& a, const T& b){
		pair<int, int> temp;
		if(a.first == b.first){
			temp.first = a.first;
			temp.second = a.second+b.second;
		}else if(a.first > b.first){
			temp.first = a.first;
			temp.second = a.second;
		}else{
			temp.first = b.first;
			temp.second = b.second;
		}
		return temp;
	}

public:
	SegTree(size_t n){
		N = n;
		height = (size_t)ceil(log2(N));
		sgt = new T[1<<(height+1)]();
	}
	~SegTree(){
		delete[] sgt;
	}
	T& operator[](const size_t& i){
		return sgt[i + (1<<height)];
	}
	void build(){
		for(size_t i = ((1<<height)-1); i > 0; i--)
			sgt[i] = queryfunc(sgt[i<<1], sgt[i<<1|1]);
	}
	void update(size_t pos, int value){
		if(pos < 0 || pos >= N) return;
		for(applyfunc(sgt[(pos += (1<<height))], value); pos > 1; pos >>= 1)
			sgt[pos>>1] = queryfunc(sgt[pos], sgt[pos^1]);
	}
	//Query [l, r)
	T query(size_t l, size_t r){
		if(l+1 == r) return (*this)[l];
		T resl, resr;
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1){
			if(l&1) resl = queryfunc(resl, sgt[l++]);
			if(r&1) resr = queryfunc(sgt[--r], resr);
		}
		return queryfunc(resl, resr);
	}
};

template<typename T> class HLD{
private:
	int root, V;
	vector<int>* edges;
	int *subtree, *parent, *heavy, *size, *depth, *head, *id;
	SegTree<T>* sgt;

	T queryfunc(const T& a, const T& b){
		pair<int, int> temp;
		if(a.first == b.first){
			temp.first = a.first;
			temp.second = a.second+b.second;
		}else if(a.first> b.first){
			temp.first = a.first;
			temp.second = a.second;
		}else{
			temp.first = b.first;
			temp.second = b.second;
		}
		return temp;
	}
	void dfs(const int& u){
		subtree[u] = 1;
		int v;
		for(int i = 0; i < size[u]; i++){
			v = edges[u][i];
			if(parent[u] != v){
				parent[v] = u;
				dfs(v);
				subtree[u] += subtree[v];
			}
		}
	}
	void hld_dfs(const int& u, int& cur){
		int v;
		if(head[u] == -1)
			head[u] = u;
		else
			head[u] = head[parent[u]];
		heavy[u] = -1;
		id[u] = cur++;
		for(int i = 0; i < size[u]; i++){
			v = edges[u][i];
			if(parent[u] != v){
				depth[v] = depth[u] + 1;
				if(heavy[u] == -1 || subtree[v] > subtree[heavy[u]])
					heavy[u] = v;
			}
		}
		if(heavy[u] != -1){
			hld_dfs(heavy[u], cur);
			for(int i = 0; i < size[u]; i++){
				v = edges[u][i];
				if(v != heavy[u] && v != parent[u]){
					head[v] = -1;
					hld_dfs(v, cur);
				}
			}
		}
	}

public:
	HLD(const int& N){
		V = N+1;
		edges = new vector<int>[V];
		subtree = new int[V];
		parent = new int[V];
		heavy = new int[V];
		size = new int[V]();
		depth = new int[V];
		head = new int[V];
		id = new int[V];
		sgt = new SegTree<T>(V);
	}
	~HLD(){
		delete[] edges;
		delete[] subtree;
		delete[] parent;
		delete[] heavy;
		delete[] size;
		delete[] depth;
		delete[] head;
		delete[] id;
		delete sgt;
	}
	void add(const int& u, const int& v){
		edges[u].push_back(v);
		edges[v].push_back(u);
		size[u]++;
		size[v]++;
	}
	void exec(){
		root = 1; //Declared by problem statement
		parent[root] = -1;
		dfs(root);
		depth[root] = 0;
		int cur = 0;
		head[root] = -1;
		hld_dfs(root, cur);
	}
	void init(int* A){
		for(int i = 1; i < V; i++){
			(*sgt)[id[i]].first = A[i]-depth[i];
			(*sgt)[id[i]].second = 1;
		}
		sgt->build();
	}
	//Update, O(log(N))
	void update(const int& v, int w){
		sgt->update(id[v], w-depth[v]);
	}
	//Query, O(log^2(N))
	T query(int q){
		T max;
		int d = depth[q];
		while(q != -1){
			max = queryfunc(max, sgt->query(id[head[q]], id[q]+1));
			q = parent[head[q]];
		}
		max.first += d;
		return max;
	}
};

class FastIO{
//#define getchar() (getchar_unlocked()) //For hackerrank
private:
	//inline if read speed is needed, huge compilation time required though
	//safe no fread implementation
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
	int readLL(long long &n){
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
	int readDouble(double &n){
		register int c;
		n = 0;
		bool neg = false;
		c = getchar();
		if(!(~c)) return -1;
		for(; ((c < 48 || c > 57)) && c != '-' && ~c; c = getchar());
		if(c == '-') neg = true, c = getchar();
		for(; c > 47 && c < 58 && ~c; c = getchar()){n = n*10+c-48;}
		if(c != '.'){
			if(neg) n = -n;
			return 1;
		}
		double div = 1;
		for(c = getchar(); c > 47 && c < 58 && ~c; c = getchar()){div *= 10, n = n*10+c-48;}
		n /= div;
		if(neg) n = -n;
		return 1;
	}
	int readStr(char *str){
		register char c = getchar();
		register int len = 0;
		if(!(~c)) return -1;
		while(c < 33 && ~c) c = getchar(); //32 if space should be included
		//32 if stop at space, 10 if stop at next line
		while(c != 10 && c != 32 && ~c){
			str[len] = c;
			c = getchar();
			len++;
		}
		str[len] = '\0';
		//Just in case if needs to return arriving at end of line
		//if(c == 10) return 10;
		return 1;
	}
	int readStr(char *str, int len){
		//Reading string of size len
		for(int i = 0; i < len; i++){
			str[i] = getchar();
			if(!(~str[i])){
				str[i] = '\0';
				return -1;
			}
			//Remove this if str can't go to next line
			/*if(str[i] == 10){
				str[i] = '\0';
				return 10;
			}*/
		}
		str[len] = '\0';
		return 1;
	}

public:
	//Constructor, true if using file input/output, defaulted false
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
	int N, Q, P, q, p, a;
	readInt(N);
	readInt(Q);
	int arr[N+1];
	HLD<pair<int, int> > hld(N);
	for(int i = 1; i <= N; i++)
		readInt(arr[i]);
	for(int i = 2; i <= N; i++){
		readInt(P);
		hld.add(i, P);
	}
	hld.exec();
	hld.init(arr);
	for(int i = 0; i < Q; i++){
		readInt(q);
		if(q){
			readInt(p);
			pair<int, int> temp = hld.query(p);
			printf("%d %d\n", temp.first, temp.second);
		}else{
			readInt(p);
			readInt(a);
			hld.update(p, a);
		}
	}
}