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
	T query(node* cur, int ql, int qr, int l, int r){
		if(ql == l && qr == r) return cur->val;
		int m = (l+r)>>1;
		T ans = defval;
		if(m >= ql) ans = queryfunc(query(cur->l, ql, qr < m ? qr : m, l, m), ans);
		if(m+1 <= qr) ans = queryfunc(ans, query(cur->r, ql > m+1 ? ql : m+1, qr, m+1, r));
		return ans;
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
	void update(int prev, int pos, const T& val){
		pst.push_back(update(pst[prev], pos, 0, N-1, val));
		states++;
	}
	T query(int state, int ql, int qr){
		if(ql > qr) return defval;
		return query(pst[state], ql, qr, 0, N-1);
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
	int N, Q, p, q, k, lo, hi, mid, ans = 0;
	readInt(N);
	pair<int, int> arr[N];
	for(int i = 0; i < N; i++){
		readInt(arr[i].first);
		arr[i].second = i+1;
	}
	sort(arr, arr+N, greater<pair<int, int> >());
	PST<int> pst(N+1);
	pst.init();
	for(int i = 0; i < N; i++)
		pst.update(i, arr[i].second, 1);
	readInt(Q);
	for(int i = 0; i < Q; i++){
		readInt(p);
		readInt(q);
		readInt(k);
		p ^= ans;
		q ^= ans;
		k ^= ans;
		lo = 0, hi = N-1;
		while(lo < hi){
			mid = (lo+hi)>>1;
			if(arr[mid].first > k)
				lo = mid+1;
			else
				hi = mid;
		}
		if(arr[lo].first > k) lo++;
		if(p > q)
			ans = 0;
		else{
			if(q > N)
				q = N;
			if(p < 1)
				p = 1;
			ans = pst.query(lo, p, q);
		}
		printf("%d\n", ans);
	}
}