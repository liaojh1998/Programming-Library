#include <bits/stdc++.h>
using namespace std;

template<typename T> class Z{
private:
	T *str;
	int N, *arr;

public:
	Z(T *st, const int& n){
		str = st;
		N = n;
		arr = new int[N+5]();
	}
	~Z(){
		delete[] arr;
	}
	const int& operator[](int i){
		return arr[i];
	}
	void search(T *s, const int& M){
		int searchZ[M+5];
		searchZ[0] = M;
		int L = 1, R = 1;
		for(int i = 1; i < M; i++)
			if(searchZ[i-L] < R-i)
				searchZ[i] = searchZ[i-L];
			else{
				L = i;
				if(R < i) R = i;
				while(R < M && s[R-i] == s[R]) R++;
				searchZ[i] = R-L;
			}
		L = 0, R = -1;
		for(int i = 0; i < N; i++)
			if(i-L >= M || searchZ[i-L] >= R-i){
				L = i;
				if(R < i) R = i;
				while(R < N && R-i < M && s[R-i] == str[R]) R++;
				arr[i] = R-L;
			}else
				arr[i] = searchZ[i-L];
	}
};

int main(){
	int N;
	scanf("%d", &N);
	char str[2*N+5], search[N+5];
	scanf("%s", &search);
	scanf("%s", &str);
	int size = strlen(str);
	memcpy(str+size, str, size); //char uses only 1 byte waow
	Z<char> z(str, 2*size);
	z.search(search, strlen(search));
	int maxlen = 0, index = 0;
	for(int i = 0; i < size; i++)
		if(z[i] > maxlen){
			maxlen = z[i];
			index = i;
		}
	printf("%d\n", index);
	return 0;
}