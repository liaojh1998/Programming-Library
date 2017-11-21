#include <bits/stdc++.h>
using namespace std;

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
		T resl = defval, resr = defval;
		resl = queryfunc(resl, query(node<<1, ql, m, l, min(r, m)));
		resr = queryfunc(query(node<<1|1, m+1, qr, max(l, m+1), r), resr);
		return queryfunc(resl, resr);
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
				printf("%lld\n", sgt.query(p-1, q-1));
			}else{
				readInt(p);
				readInt(q);
				readInt(v);
				sgt.update(p-1, q-1, v);
			}
		}
	}
}