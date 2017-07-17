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
	T reversefunc(const T& a, const T& b){
		return a - b;
	}

public:
	FenTree(size_t n){
		N = n + 1;
		fwt = new T[N]();
	}
	~FenTree(){
		delete[] fwt;
	}
	T operator[](size_t i){
		T ans = fwt[i+1];
		for(size_t next = i & (i + 1); i > next; i &= (i - 1))
			ans = reversefunc(ans, fwt[i]);
		return ans;
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, last = 0, next, lo, hi, mid, arr[20000];
	cin >> T;
	while(T--){
		cin >> N;
		FenTree<int> fwt(N);
		for(int i = 1; i <= N; i++){
			next = (last+i)%(N-i+1);
			lo = 0;
			hi = N-1;
			while(lo < hi){
				mid = (lo+hi)/2;
				if(mid-fwt.query(mid) < next)
					lo = mid+1;
				else
					hi = mid;
			}
			arr[lo] = i;
			fwt.update(lo, 1);
			last = next;
		}
		for(int i = 0; i < N; i++)
			cout << arr[i] << (i == N-1 ? "\n" : " ");
	}
	return 0;
}