#include <bits/stdc++.h>
using namespace std;

template<typename T> class FenTree{
private:
	T* fwt;
	size_t N;
	T applyfunc(const T& a, const T& b){
		return a + b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}

public:
	FenTree(size_t n){
		N = n + 1;
		fwt = new T[N]();
	}
	~FenTree(){
		delete[] fwt;
	}
	void update(size_t i, T value){
		for(i++; i < N; i += (i & -i))
			fwt[i] = applyfunc(fwt[i], value);
	}
	T query(size_t i){
		T ans = 0;
		for(i++; i; i &= (i - 1))
			ans = queryfunc(ans, fwt[i]);
		return ans;
	}
};

int main(){
	//Range update, single query: exact value at k
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, Q, l, r, val;
	cin >> T;
	while(T--){
		cin >> N >> Q;
		FenTree<int> fwt(N+1);
		while(Q--){
			cin >> l >> r >> val;
			fwt.update(l, val);
			fwt.update(r+1, -val);
		}
		cin >> Q;
		while(Q--){
			cin >> l;
			cout << fwt.query(l) << endl;
		}
	}
	return 0;
}