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
	//Longest prefix of suffix of string starting at i, different from KMP which uses LPS: longest suffix of ith prefix substring that's a prefix of the prefix substring
	void exec(){
		arr[0] = N;
		int L = 1, R = 1;
		for(int i = 1; i < N; i++)
			if(arr[i-L] < R-i)
				arr[i] = arr[i-L];
			else{
				L = i;
				if(R < i) R = i;
				while(R < N && str[R-i] == str[R]) R++;
				arr[i] = R-L;
			}
	}
	//String search, stores shifts in vector
	void search(T *s, const int& M, vector<int>& shifts){
		//Z algorithm first on the pattern
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
		//Z algorithm on the search string, but only looking for where R-L == M
		L = 0, R = -1;
		for(int i = 0; i < N; i++)
			if(i-L >= M || searchZ[i-L] >= R-i){
				L = i;
				if(R < i) R = i;
				while(R < N && R-i < M && s[R-i] == str[R]) R++;
				if(R-L == M)
					shifts.push_back(i);
			}
	}
};

int main(){
	//Enter code here
	return 0;
}