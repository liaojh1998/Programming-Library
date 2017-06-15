//PSA Manacher's Algorithm Template
#include <bits/stdc++.h>
using namespace std;

//Builds a Palindromic Substring Array for LPS
template<typename T> class Manacher{
private:
	int N;
	int* psa;
	T* S;

public:
	//Useful functions
	//Constructors: s - string array, N - size of array
	Manacher(T* s, const int& n){
		N = n;
		S = s;
		psa = new int[N*2+1];
	}
	~Manacher(){
		delete[] psa;
	}

	//Access PSA
	int operator[](const int& i){
		return psa[i];
	}

	//Manacher's Algorithm
	void exec(){
		int center = 0, size = N*2+1, bound = -1, rad, loc;
		for(int i = 0; i < size; i++){
			rad = (i <= bound) ? min(psa[2*center-i], (bound-i)/2) : 0;
			loc = (i-1)/2;
			//Odd - on char; Even - between char
			if(i%2){
				while(loc+rad+1 < N && loc-rad-1 >= 0 && S[loc-rad-1] == S[loc+rad+1])
					rad++;
				if(i + rad*2 + 1 > bound){
					center = i;
					bound = i + rad*2 + 1;
				}
			}else{
				while(loc+rad+1 < N && loc-rad >= 0 && S[loc-rad] == S[loc+rad+1])
					rad++;
				if(i + rad*2 > bound){
					center = i;
					bound = i + rad*2;
				}
			}
			psa[i] = rad;
		}
		for(int i = 0; i < size; i++)
			psa[i] = ((i%2) ? 1 : 0) + 2*psa[i];
		//To get radius from psa, reverse operations:
		//rad[i] = (psa[i] - (i%2) ? 1 : 0)/2;
	}
};

int main(){
	//Enter code here
	return 0;
}