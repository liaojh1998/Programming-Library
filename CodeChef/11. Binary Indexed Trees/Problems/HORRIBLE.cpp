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
	//Range update, range query
	//Follow up from the idea of range update, single query: add val to [l, r] and query the exact val at k, not the prefix sum at till k
	//UPDATEIT uses Fenwick's tree to solve it with which exact val at k = prefix sum till k
	//Here query val*(k - l + 1) = val*k - val*(l-1), so keep 2 BITs, one to find val and the other to keep val*(l-1), BIT1(k)*k - BIT2(k) = val*k - val*(l-1)
	//If k > r, from UPDATEIT r+1 has val at r removed, and we need val*(r-l+1) in our answer
	//Because val*(r-l+1) = val*r - val*(l-1), and we already have val*(l-1) in the 2nd BIT, and because we subtract second BIT, make val*r negative so we can add it to answer
	//BIT1(k)*k - BIT2(k) = val2*k - val2*(l-1) + for all val(val*r - val*(l-1)) = val2*(k-l+1) + for all val(val*(r-l+1))
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, Q, q, p;
	long long v;
	cin >> T;
	while(T--){
		cin >> N >> Q;
		FenTree<long long> fwt1(N+1), fwt2(N+1);
		while(Q--){
			cin >> q;
			if(q){
				cin >> p >> q;
				//Range query
				cout << fwt1.query(q)*q-fwt2.query(q)-fwt1.query(p-1)*(p-1)+fwt2.query(p-1) << endl;
			}else{
				cin >> p >> q >> v;
				//Range update
				fwt1.update(p, v);
				fwt1.update(q+1, -v);
				fwt2.update(p, v*(p-1));
				fwt2.update(q+1, -v*q);
			}
		}
	}
	return 0;
}