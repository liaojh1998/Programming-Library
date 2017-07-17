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
	int T, N, cur;
	long long ans;
	cin >> T;
	while(T--){
		cin >> N;
		string data[N+5], str;
		unordered_map<string, int> order;
		FenTree<long long> fwt(N);
		for(int i = 0; i < N; i++)
			cin >> data[i];
		for(int i = N-1; i >= 0; i--){
			cin >> str;
			order[str] = i;
		}
		ans = 0;
		for(int i = 0; i < N; i++){
			cur = order[data[i]];
			ans += fwt.query(cur);
			fwt.update(cur, 1);
		}
		cout << ans << endl;
	}
	return 0;
}