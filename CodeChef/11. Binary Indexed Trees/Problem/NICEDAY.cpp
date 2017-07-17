#include <bits/stdc++.h>
using namespace std;

template<typename T> class FenTree{
private:
	T* fwt;
	size_t N;
	T applyfunc(const T& a, const T& b){
		return a > b ? a : b;
	}
	T queryfunc(const T& a, const T& b){
		return a > b ? a : b;
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T, N, a, b, c, ans;
	cin >> T;
	while(T--){
		cin >> N;
		pair<int, int> ranks[N];
		for(int i = 0; i < N; i++){
			cin >> a >> b >> c;
			ranks[a-1].first = b-1;
			ranks[a-1].second = N-c+1;
		}
		ans = 0;
		FenTree<int> fwt(N);
		for(int i = 0; i < N; i++)
			if(fwt.query(ranks[i].first) < ranks[i].second){
				ans++;
				fwt.update(ranks[i].first, ranks[i].second);
			}
		cout << ans << endl;
	}
	return 0;
}