#include <bits/stdc++.h>
using namespace std;

template<typename T> class DST{
private:
	int N, height;
	long long P;
	T** st;

	T func(const T& a, const T& b){
		return (a * b)%P;
	}

public:
	DST(const int& n, const long long& p){
		N = n;
		P = p;
		height = static_cast<int>(ceil(log2(N)))+1;
		st = new T*[height];
		for(int i = 0; i < height; i++)
			st[i] = new T[N+5];
	}
	~DST(){
		for(int i = 0; i < height; i++)
			delete[] st[i];
		delete[] st;
	}
	void build(T *arr){
		for(int i = 0; i < N; i++)
			st[0][i] = arr[i];
		for(int i = 1; i < height; i++){
			int size = 1 << i;
			int half = size >> 1;
			for(int j = half; j < N; j += size){
				st[i][j-1] = arr[j-1];
				int jsize = j-half;
				for(int k = j-2; k >= jsize; k--)
					st[i][k] = func(arr[k], st[i][k+1]);
				st[i][j] = arr[j];
				jsize = min(j+half, N);
				for(int k = j+1; k < jsize; k++)
					st[i][k] = func(st[i][k-1], arr[k]);
			}
		}
	}
	T query(const int& a, const int& b){
		if(a == b)
			return st[0][a];
		int h = 32 - __builtin_clz(a^b);
		return func(st[h][a], st[h][b]);
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while(T--){
		long long N, P, Q;
		cin >> N >> P >> Q;
		long long arr[N+5];
		for(int i = 0; i < N; i++){
			cin >> arr[i];
			arr[i] %= P;
		}
		DST<long long> dst(static_cast<int>(N), P);
		dst.build(arr);
		long long B[Q/64+5];
		for(int i = 0; i < Q/64+2; i++)
			cin >> B[i];
		long long L, R, x = 0, t;
		for(int i = 0; i < Q; i++){
			if(i%64){
				L = (L + x)%N;
				R = (R + x)%N;
			}else{
				L = (B[i/64] + x)%N;
				R = (B[i/64+1] + x)%N;
			}
			if(R < L){
				t = L;
				L = R;
				R = t;
			}
			x = (dst.query(L, R)+1)%P;
		}
		cout << x << endl;
	}
	return 0;
}