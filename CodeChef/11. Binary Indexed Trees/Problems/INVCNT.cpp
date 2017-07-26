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
	//Solvable using Merge Sort, also solvable using BIT, but is it solvable using Shortest path?
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N;
	long long ans;
	cin >> T;
	while(T--){
		cin >> N;
		pair<int, int> arr[N+5];
		for(int i = 0; i < N; i++){
			cin >> arr[i].first;
			arr[i].second = i;
		}
		sort(arr, arr+N, greater<pair<int, int> >());
		int resort[N+5];
		for(int i = 0; i < N; i++)
			resort[arr[i].second] = i;
		FenTree<long long> fwt(N+1);
		ans = 0;
		for(int i = 0; i < N; i++){
			ans += fwt.query(resort[i]);
			fwt.update(resort[i], 1);
		}
		cout << ans << endl;
	}
	return 0;
}