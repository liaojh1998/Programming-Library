#include <bits/stdc++.h>
using namespace std;

template<typename T> class SegTree{
private:
	T* sgt;
	T* lazy;
	size_t N, height;
	
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	T upropfunc(const T& a, const T& b){
		return a + b;
	}
	T dpropfunc(const T& a, const T& b){
		return a + b;
	}

public:
	SegTree(size_t n){
		N = n;
		height = (size_t)ceil(log2(N));
		sgt = new T[1<<(height+1)]();
		lazy = new T[1<<height]();
	}
	~SegTree(){
		delete[] sgt;
		delete[] lazy;
	}
	T& operator[](size_t i){
		return sgt[i + (1<<height)];
	}
	void calc(size_t pos, size_t k){
		if(lazy[pos]) sgt[pos] = upropfunc(queryfunc(sgt[pos<<1], sgt[pos<<1|1]), lazy[pos]*k);
		else sgt[pos] = queryfunc(sgt[pos<<1], sgt[pos<<1|1]);
	}
	void propagate(size_t pos, const T& value, size_t k){
		sgt[pos] = upropfunc(sgt[pos], value*k);
		if(pos < (1<<height)) lazy[pos] = dpropfunc(lazy[pos], value);
	}
	void push(size_t l, size_t r){
		size_t p = height, k = 1 << (height-1);
		for(l += (1<<height), r += (1<<height)-1; p > 0; p--, k >>= 1)
			for(size_t i = l >> p; i <= r >> p; i++)
				if(lazy[i]){
					propagate(i<<1, lazy[i], k);
					propagate(i<<1|1, lazy[i], k);
					lazy[i] = 0;
				}
	}
	void update(size_t l, size_t r, const T& value){
		if(l == r || !value) return;
		push(l, l + 1);
		push(r - 1, r);
		bool appl = false, appr = false;
		size_t k = 1;
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1, k <<= 1){
			if(appl) calc(l - 1, k);
			if(appr) calc(r, k);
			if(l&1) propagate(l++, value, k), appl = true;
			if(r&1) propagate(--r, value, k), appr = true;
		}
		for(--l; r > 0; l >>= 1, r >>= 1, k <<= 1){
			if(appl) calc(l, k);
			if(appr && (!appl || l != r)) calc(r, k);
		}
	}
	T query(size_t l, size_t r){
		push(l, l + 1);
		push(r - 1, r);
		T res = 0;
		for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1){
			if(l&1) res = queryfunc(res, sgt[l++]);
			if(r&1) res = queryfunc(sgt[--r], res);
		}
		return res;
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
	int T, N, C, p, q, v;
	readInt(T);
	while(T--){
		readInt(N);
		readInt(C);
		SegTree<long long> sgt(N);
		while(C--){
			readInt(q);
			if(q){
				readInt(p);
				readInt(q);
				printf("%lld\n", sgt.query(p-1, q));
			}else{
				readInt(p);
				readInt(q);
				readInt(v);
				sgt.update(p-1, q, v);
			}
		}
	}
}