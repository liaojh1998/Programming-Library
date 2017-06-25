#include <bits/stdc++.h>
using namespace std;

template<typename T> class KMP{
private:
	T *str, *search;
	int N, M;
	vector<size_t> shift;

public:
	KMP(T *st, int n, T *se, int m){
		str = st;
		N = n;
		search = se;
		M = m;
	}
	//Access valid shift
	vector<size_t>& getShift(){
		return shift;
	}
	//Longest proper suffix that is also a prefix of current suffix
	void computeLPS(int p[]){
		p[0] = 0;
		int len = 0;
		for(int i = 1; i < M; i++){
			//Search for all j < i-1 instances of arr[i-1] in previous proper suffixes such that arr[j+1] == arr[i]
			while(len && search[len] != search[i])
				len = p[len-1];
			if(search[len] == search[i]) len++;
			p[i] = len;
		}
	}
	void exec(){
		int lps[M], prefix = 0;
		computeLPS(lps); //The "internal rules" of the automaton
		for(int i = 0; i < N; i++){
			//Input a character into previous state for the automaton, automaton decides which state to go to
			while(prefix && search[prefix] != str[i])
				prefix = lps[prefix-1];
			if(search[prefix] == str[i]) prefix++;
			if(prefix == M){
				shift.push_back(i-M+1);
				prefix = lps[prefix-1];
			}
		}
	}
};

int main(){
	//Enter code here
	return 0;
}