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

struct s{
	int index;
	long long a, b;
};

bool cmp1(const s& a, const s& b){
	return a.b < b.b;
}

bool cmp2(const s& a, const s& b){
	return a.a < b.a;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, size;
	cin >> N;
	s data[N+5];
	string str;
	for(int i = 0; i < N; i++){
		cin >> str;
		data[i].index = i;
		size = str.size();
		data[i].a = 0;
		for(int j = 0; j < size; j++)
			data[i].a = data[i].a*27+str[j]-'a'+1;
		for(int j = size; j < 10; j++) data[i].a *= 27;
		data[i].b = 0;
		for(int j = size-1; j >= 0; j--)
			data[i].b = data[i].b*27+str[j]-'a'+1;
		for(int j = size; j < 10; j++) data[i].b *= 27;
	}
	sort(data, data+N, cmp1);
	int rank[N];
	for(int i = 0; i < N; i++)
		rank[data[i].index] = N-i-1;
	sort(data, data+N, cmp2);
	FenTree<long long> fwt(N);
	long long ans = 0;
	for(int i = 0; i < N; i++){
		ans += fwt.query(rank[data[i].index]);
		fwt.update(rank[data[i].index], 1);
	}
	cout << ans << endl;
	return 0;
}