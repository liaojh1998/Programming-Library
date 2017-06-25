//String Matching Rabin Karp Template
//Refer to CLRS for reference
#include <bits/stdc++.h>
using namespace std;

//Find pattern P in string S
template<typename T> class RabinKarp{
private:
	T* S;
	size_t N;
	vector<size_t> shift; //Valid shifts, note that shifts also equal valid starting indices

	//Fast modular exponentiation in non-recursive format, O(log b) runtime
	size_t pow(size_t b, size_t exp, const size_t q){
		size_t res = 1;
		b %= q;
		while(exp){
			if(exp&1) res = (res*b)%q;
			exp >>= 1;
			b = (b*b)%q;
		}
		return res;
	}

public:
	//Useful functions
	//Constructors: s - string array, N - size of array
	RabinKarp(T* s, size_t n){
		N = n;
		S = s;
	}
	//Access valid shifts
	vector<size_t>& getShift(){
		return shift;
	}

	//Rabin-Karp Algorithm
	//Naive algorithm runs well in random strings, runtime: O((n-m+1)m)
	//For Rabin-Karp
	//Preprocessing: O(m), m - length of P
	//Runtime: O((n-m+1)m), n - length of S, m - length of P
	//In average case runs faster than Naive
	//Uses a heuristic modulus test to rule out invalid shifts before checking valid shifts
	//P - String to be searched
	//size - size of P
	//d - radix, usually the size of the alphabet list, which is usually ASCII 256 characters
	//q - rolling hash modulus - may be modified to long long using 10^9 + 7 for less collisions
	//Good primes: linear exponentiation and 256 char: 8388593, fermat prime (unlikely collision): 65537, int and fast modular exponentiation (avoid overflow): 65521, long long: 1000000007
	void exec(T* P, size_t size, const size_t d = 256, const size_t q = 8388593){
		if(size > N) return; //Please don't give patterns that are bigger than the text
		//size_t h = pow(d, size-1, q); //If using fast modular exponentiation
		size_t h = 1;
		//O(m) exponentiation for removing first digit
		for(size_t i = 0; i < size-1; i++)
			h = (h*d)%q;
		//O(m) preprocessing for p and t0 value
		size_t p = 0;
		size_t t = 0;
		for(size_t i = 0; i < size; i++){
			p = (d*p + P[i])%q;
			t = (d*t + S[i])%q;
		}
		//O((n-m+1)m) search, where (n-m+1) is sped up by heuristic modular test, worst case scenario: everything in string matches with pattern
		size_t len = N-size+1;
		for(size_t i = 0; i < len; i++){
			if(p == t){
				bool possible = true;
				for(size_t j = 0; j < size && possible; j++)
					if(S[i+j] != P[j]) possible = false;
				if(possible) shift.push_back(i);
			}
			if(i < len-1)
				t = (d*(t-(S[i]*h)%q+q) + S[i+size])%q; //Remove first digit and add next digit % q
		}
	}
};

int main(){
	//Enter code here
	return 0;
}